//////////////////////////////////////////////////////////////////////
// $Id: AVEncoder.cpp 8331 2024-08-29 17:04:46Z mellinger $
// Authors: mellinger@neurotechcenter.org
// Description: A class that encapsulates writing of images into a 
//   video file.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
///////////////////////////////////////////////////////////////////////
#include "AVEncoder.h"

#include "AVError.h"
#include "AVLog.h"
#include "Debugging.h"

// Some codecs insist on configuring thread properties
// in a way that is incompatible with other codecs
// (COM initialization). We use a worker thread to solve this.
// This problem is probably restricted
// to Windows, so we don't use a worker thread on other platforms.
#if _WIN32
# include "ReusableThread.h"
# include "Runnable.h"
# define USE_WORKER_THREAD 1
#endif

#include <sstream>
#include <vector>
#include <mutex>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/error.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


static const char* h264_mf_presetNames[] = {
    "auto", "baseline", "main", "high"
};
static const char* libx264_presetNames[] = {
    "medium", "fast", "medium", "slow"
};
static const int numPresetNames = 4;

static const char* PresetName(const AVCodec* pCodec, int preset)
{
    if (preset >= numPresetNames)
        preset = numPresetNames - 1;
    if (preset < 0)
        preset = 0;
    if (pCodec->id == AV_CODEC_ID_H264) {
        if (!::stricmp(pCodec->name, "h264_mf")) { // Windows Media Foundation
            return h264_mf_presetNames[preset];
        }
        if (!::stricmp(pCodec->name, "libx264")) {
            return libx264_presetNames[preset];
        }
        return nullptr;
    }
    return nullptr;
}

struct AVEncoder::Private
{
    AVPacket* mpPacket = nullptr;
    AVFormatContext* mpFormatContext = nullptr;

    struct VideoStream {
        const AVCodec* mpCodec = nullptr;
        AVCodecContext* mpCodecContext = nullptr;
        AVFrame* mpFrame = nullptr;
        SwsContext* mpScaleContext = nullptr;
        AVStream* mpVideoStream = nullptr;
        int64_t mNominalFrameDuration = 0;
        int64_t mFrameCount = 0;
    };
    std::vector<VideoStream> mStreams;

    std::string mFileName;
    std::ostringstream mError;
    std::mutex mMutex;
#if USE_WORKER_THREAD
    WorkerThread mWorkerThread;
#endif

    ~Private()
    {
        CloseFile();
    }

    void OpenFile(const std::string& filename)
    {
        CloseFile();
        mFileName = filename;
        int result = ::avformat_alloc_output_context2(&mpFormatContext, nullptr, nullptr, mFileName.c_str());
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not allocate output context: " << AVError(result).Message() << std::endl;
        }
        mpPacket = ::av_packet_alloc();
    }

    void CloseFile()
    {
        ::av_packet_free(&mpPacket);
        if (mpFormatContext && TotalFrameCount() > 0)
        {
            int result = ::av_write_trailer(mpFormatContext);
            if (result < 0) {
                std::lock_guard<std::mutex> lock(mMutex);
                mError << "Could not write trailer: " << AVError(result).Message() << std::endl;
            }
        }
        if (mpFormatContext)
        {
            ::avio_closep(&mpFormatContext->pb);
            ::avformat_free_context(mpFormatContext);
            mpFormatContext = nullptr;
        }
        for (auto& stream : mStreams)
            CloseStream(stream);
        mStreams.clear();
    }

    void BeginWriting()
    {
        for (const auto& stream : mStreams)
            if (!stream.mpCodecContext) {
                std::lock_guard<std::mutex> lock(mMutex);
                mError << "BeginWriting() called with uninitialized streams";
                return;
            }

        if (mpFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
            for (auto& stream : mStreams)
                stream.mpCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

        int result = ::avio_open(&mpFormatContext->pb, mFileName.c_str(), AVIO_FLAG_WRITE);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not open file: " << AVError(result).Message() << std::endl;
            return;
        }

        result = ::avformat_write_header(mpFormatContext, nullptr);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not write header: " << AVError(result).Message() << std::endl;
            return;
        }
    }

    void AddVideoStream(int* outStreamId, int /*codec*/)
    {
        VideoStream stream;
        stream.mpCodec = ::avcodec_find_encoder(AV_CODEC_ID_H264);
        if (!stream.mpCodec) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Cannot find H.264 encoder" << std::endl;
            return;
        }
        *outStreamId = mStreams.size();
        mStreams.push_back(stream);
    }

    void CloseStream(VideoStream& stream)
    {
        ::sws_freeContext(stream.mpScaleContext);
        stream.mpScaleContext = nullptr;
        if (stream.mpCodecContext)
        {
            ::avcodec_close(stream.mpCodecContext);
            ::avcodec_free_context(&stream.mpCodecContext);
        }
        ::av_frame_free(&stream.mpFrame);
    }

    VideoStream& GetStream(int idx)
    {
        if (idx < 0 || idx >= mStreams.size())
            throw std_runtime_error << "Invalid stream index: " << idx;
        return mStreams[idx];
    }

    void InitializeStream(int idx, int width, int height, Rate fps, int preset, int compressionFactor)
    {
        VideoStream& stream = GetStream(idx);
        AVCodecContext* pCtx = ::avcodec_alloc_context3(stream.mpCodec);
        stream.mpCodecContext = pCtx;
        pCtx->thread_count = 1;
        pCtx->active_thread_type = 0;
        pCtx->gop_size = 10;
        pCtx->max_b_frames = 1;
        Ratio r = (fps * Time::OneSecond()).Simplified(1e-6);
        int n = r.Numerator(), d = r.Denominator();
        pCtx->framerate = AVRational{ n, d };
        pCtx->time_base = AVRational{ d, n };
        stream.mNominalFrameDuration = TimeIntervalToPts(stream, fps.Period());

        // Determine maximum bit rate
        pCtx->bit_rate = width * height * 2 /* YUV420 */ * sizeof(uint8_t) * r.To<double>();
        // Divide by compression factor
        pCtx->bit_rate /= compressionFactor;
        // Allow actual bit rate to be between 0 and twice the estimated compressed bit rate
        pCtx->bit_rate_tolerance = pCtx->bit_rate;

        pCtx->pix_fmt = AV_PIX_FMT_YUV420P;

        pCtx->codec_id = AV_CODEC_ID_H264;
        pCtx->codec_type = AVMEDIA_TYPE_VIDEO;
        pCtx->width = width;
        pCtx->height = height;

        const char* pPreset = PresetName(stream.mpCodec, preset);
        if (pPreset)
            ::av_opt_set(pCtx->priv_data, "preset", pPreset, 0);

        int result = ::avcodec_open2(pCtx, stream.mpCodec, nullptr);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not open codec: " << AVError(result).Message();
            return;
        }

        stream.mpFrame = ::av_frame_alloc();
        stream.mpFrame->format = pCtx->pix_fmt;
        stream.mpFrame->width = pCtx->width;
        stream.mpFrame->height = pCtx->height;
        result = ::av_frame_get_buffer(stream.mpFrame, 0);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not get buffer: " << AVError(result).Message();
            return;
        }

        stream.mpVideoStream = ::avformat_new_stream(mpFormatContext, stream.mpCodec);
        if (!stream.mpVideoStream) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not create video stream";
            return;
        }
        stream.mpVideoStream->id = mpFormatContext->nb_streams - 1;
        stream.mpVideoStream->time_base = pCtx->time_base;

        result = ::avcodec_parameters_from_context(stream.mpVideoStream->codecpar, pCtx);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "Could not copy parameters from context: " << AVError(result).Message();
            return;
        }

        stream.mpScaleContext = ::sws_getContext(
            width, height, AV_PIX_FMT_BGR0,
            width, height, AV_PIX_FMT_YUV420P,
            0, nullptr, nullptr, nullptr
        );

        stream.mFrameCount = 0;
    }

    void WriteFrame(int streamIndex, const void* pData, Time::Interval timestamp)
    {
        auto& stream = GetStream(streamIndex);
        SetFrame(stream, static_cast<const uint32_t*>(pData));
        SaveFrame(stream, timestamp);
    }

    int64_t TimeIntervalToPts(VideoStream& stream, Time::Interval interval)
    {
        AVRational tb = stream.mpCodecContext->time_base;
        Ratio r(tb.num, tb.den);
        return ((interval / Time::OneSecond()) / r).Round();
    }

    void SetFrame(VideoStream& stream, const uint32_t* pRGBData)
    {
        int rgblinesize = sizeof(*pRGBData) * stream.mpFrame->width;
        union { const uint32_t* p3; const uint8_t* p8; } rgbdata = { pRGBData };
        ::sws_scale(stream.mpScaleContext,
            &rgbdata.p8, &rgblinesize, 0, stream.mpFrame->height,
            stream.mpFrame->data, stream.mpFrame->linesize
        );
    }

    void SaveFrame(VideoStream& stream, Time::Interval timestamp)
    {
        stream.mpFrame->pts = TimeIntervalToPts(stream, timestamp);
        int result = ::avcodec_send_frame(stream.mpCodecContext, stream.mpFrame);
        if (result < 0) {
            std::lock_guard<std::mutex> lock(mMutex);
            mError << "avcodec_send_frame() failed: " << AVError(result).Message() << std::endl;
            return;
        }
        ++stream.mFrameCount;

        while (result >= 0)
        {
            result = ::avcodec_receive_packet(stream.mpCodecContext, mpPacket);
            if (result < 0 && result != AVERROR(EAGAIN)) {
                std::lock_guard<std::mutex> lock(mMutex);
                mError << "avcodec_receive_packet() failed: " << AVError(result).Message() << std::endl;
                return;
            }
            if (result >= 0)
            {
                ::av_packet_rescale_ts(mpPacket, stream.mpCodecContext->time_base, stream.mpVideoStream->time_base);
                mpPacket->stream_index = stream.mpVideoStream->index;
                result = ::av_interleaved_write_frame(mpFormatContext, mpPacket);
                if (result < 0) {
                    std::lock_guard<std::mutex> lock(mMutex);
                    mError << "av_interleaved_write_frame() failed: " << AVError(result).Message() << std::endl;
                    return;
                }
            }
        }
    }
    void FinalizeStream(int idx)
    {
        auto& stream = GetStream(idx);
        if (stream.mpCodecContext && mpFormatContext && stream.mpFrame)
        {
            // Send last frame again with updated time stamp.
            // Otherwise, libav is not able to seek to the last frame..
            stream.mpFrame->pts += stream.mNominalFrameDuration;
            int result = ::avcodec_send_frame(stream.mpCodecContext, stream.mpFrame);
            if (result < 0) {
                std::lock_guard<std::mutex> lock(mMutex);
                mError << "avcodec_send_frame() failed: " << AVError(result).Message() << std::endl;
                return;
            }
            // Send a null frame to indicate End-Of-Stream.
            result = ::avcodec_send_frame(stream.mpCodecContext, nullptr);
            if (result < 0) {
                std::lock_guard<std::mutex> lock(mMutex);
                mError << "avcodec_send_frame() failed: " << AVError(result).Message() << std::endl;
                return;
            }
            while (result >= 0)
            {
                result = ::avcodec_receive_packet(stream.mpCodecContext, mpPacket);
                if (result < 0 && result != AVERROR(EAGAIN) && result != AVERROR_EOF) {
                    std::lock_guard<std::mutex> lock(mMutex);
                    mError << "avcodec_receive_packet() failed: " << AVError(result).Message() << std::endl;
                    return;
                }
                Assert(result != AVERROR(EAGAIN));
                if (result >= 0)
                {
                    ::av_packet_rescale_ts(mpPacket, stream.mpCodecContext->time_base, stream.mpVideoStream->time_base);
                    mpPacket->stream_index = stream.mpVideoStream->index;
                    result = ::av_interleaved_write_frame(mpFormatContext, mpPacket);
                    if (result < 0) {
                        std::lock_guard<std::mutex> lock(mMutex);
                        mError << "av_interleaved_write_frame() failed: " << AVError(result).Message() << std::endl;
                        return;
                    }
                }
            }
        }
    }

    int64_t TotalFrameCount() const
    {
        int64_t total = 0;
        for (const auto& stream : mStreams)
            total += stream.mFrameCount;
        return total;
    }
};

AVEncoder::AVEncoder()
: p(new Private)
{
    AVLog::AddClient();
}

AVEncoder::~AVEncoder()
{
    AVLog::RemoveClient();
    delete p;
}

AVEncoder& AVEncoder::OpenFile(const std::string& file)
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*, const std::string&)> call(&Private::OpenFile, p, file);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->OpenFile(file);
#endif
    return *this;
}

AVEncoder& AVEncoder::AddVideoStream(int* pStreamIndex, int codec)
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*, int*, int)> call(&Private::AddVideoStream, p, pStreamIndex, codec);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->AddVideoStream(pStreamIndex, codec);
#endif
    return *this;
}

AVEncoder& AVEncoder::InitializeVideoStream(int streamIndex, int width, int height, const Rate& fps, int preset, int compressionFactor)
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*, int, int, int, Rate, int, int)> 
        call(&Private::InitializeStream, p, streamIndex, width, height, fps, preset, compressionFactor);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->InitializeStream(streamIndex, width, height, fps, preset, compressionFactor);
#endif
    return *this;
}

AVEncoder& AVEncoder::AddAudioStream(int* pStreamIndex, int codec)
{
    *pStreamIndex = INT_MAX;
    return *this;
}

AVEncoder& AVEncoder::InitializeAudioStream(int streamIndex, int channels, int bitspersample, const Rate& sps)
{
    if (streamIndex != INT_MAX)
        p->mError << "not an audio stream index: " << streamIndex;
    return *this;
}

AVEncoder& AVEncoder::BeginWriting()
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*)> call(&Private::BeginWriting, p);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->BeginWriting();
#endif
    return *this;
}

AVEncoder& AVEncoder::WriteFrame(int streamIndex, const void* pData, int bytes, Time::Interval timestamp)
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*, int, const void*, Time::Interval)> 
        call(&Private::WriteFrame, p, streamIndex, pData, timestamp);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->WriteFrame(streamIndex, pData, timestamp);
#endif
    return *this;
}

AVEncoder& AVEncoder::FinalizeStream(int streamIndex)
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*, int)> call(&Private::FinalizeStream, p, streamIndex);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->FinalizeStream(streamIndex);
#endif
    return *this;
}

AVEncoder& AVEncoder::CloseFile()
{
#if USE_WORKER_THREAD
    MemberCall<void(Private*)> call(&Private::CloseFile, p);
    p->mWorkerThread.RunSynchronously(call);
#else
    p->CloseFile();
#endif
    return *this;
}

std::string AVEncoder::Error() const
{
    std::lock_guard<std::mutex> lock(p->mMutex);
    return p->mError.str();
}
