////////////////////////////////////////////////////////////////////////////////
// $Id: AVUtils.h 8150 2024-05-21 13:43:03Z mellinger $
// Author: juergen.mellinger@uni-tuebingen.de
// Description: Helper classes for interfacing with LibAV.
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
////////////////////////////////////////////////////////////////////////////////
#ifndef AV_UTILS_H
#define AV_UTILS_H

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#include "AVDecoder.h"
#include "ClockTick.h"
#include "GUI.h"
#include "Lockable.h"
#include "Numeric.h"
#include "Rate.h"
#include "Uncopyable.h"
#include "SynchronizedObject.h"

namespace AVUtils
{

void Init();

class Log
{
  public:
    Log(int = AV_LOG_VERBOSE);
    ~Log();
    static const char *Current();

  private:
    struct Data;
    Data *d;
};

struct Frame
{
  private:
    Frame(const Frame &);
    Frame &operator=(const Frame &);

  public:
    Frame();
    ~Frame();
    AVFrame *p;
    ClockTick pos;
};

struct FracTick
{
    int64_t intpart;
    float fracpart;
};

struct DataOwner
{
    virtual ~DataOwner()
    {
    }
    virtual int LockData(int frames, void *&, void *&) = 0; // mark data as in use
    virtual void ReleaseData(void *, void *) = 0;           // unmark "in use" data
};

class FrameProcessor : public DataOwner, Uncopyable
{
  protected:
    template <class T> FrameProcessor(T *, size_t);

  public:
    virtual ~FrameProcessor();
    // Configure to input frame format, presentation frame rate, frame dimensions, and quality
    // returns < 0 in case of error, 1 if configuration was changed, 0 if no change in parameters
    int Configure(const Frame *, Ratio &, const int *, size_t, AVDecoder::Quality = AVDecoder::QualityFast);
    // Process input frame to data buffers
    // returns < 0 in case of error, 1 if frame was consumed, 0 otherwise
    int FillBuffers(const Frame *);
    // Process input frame (or 0) to a single data buffer
    // returns < 0 in case of error, number of buffered frames otherwise
    int Process(const Frame *);
    // File/stream offset tick.
    int64_t HeadTick() const;
    void AssignHeadTick(int64_t);
    int AdvanceByTicks(int);
    int AdvanceByFrames(int);
    int AdvanceByBuffers(int);

    void FlushBuffers();
    int BuffersFree() const;
    int BuffersUsed() const;
    int FramesBuffered() const;
    virtual int BytesPerFrame() const = 0;

    // DataOwner interface
    int LockData(int frames, void *&, void *&);
    void ReleaseData(void *, void *);

  protected:
    struct Buffer;

  private:
    Ratio GuessTicksInBuffer(const Buffer &) const;

  protected:
    virtual int OnConfigure(const Frame *, Ratio &, const int *, size_t, AVDecoder::Quality) = 0;
    virtual int OnProcess(const Frame *, size_t) = 0;
    virtual void OnFlushBuffers() = 0;

    struct DataObject
    {
        virtual void Clear() = 0;
        virtual void *Data() = 0;
        virtual int Frames() const = 0;

      protected:
        virtual ~DataObject()
        {
        }
    };
    struct Buffer
    {
        Buffer()
        : pRead(nullptr), pEnd(nullptr),
        pBufferObject(nullptr),
        refCount(0)
        {}
        Buffer(const Buffer& other)
        : pRead(other.pRead), pEnd(other.pEnd),
            pBufferObject(other.pBufferObject),
            refCount(other.refCount.load()),
            tick(other.tick)
        {}
        uint8_t *pRead, *pEnd;
        DataObject *pBufferObject;
        std::atomic<int> refCount;
        FracTick tick;
    };

    std::vector<Buffer> mBuffers;
    std::atomic<int> mWriteBufferIdx, mReadBufferIdx, mBuffersUsed;
    Ratio mResamplingRatio;
    Lockable<std::recursive_mutex> mAccess;
};

class AudioResampler : public FrameProcessor
{
  public:
    AudioResampler();
    ~AudioResampler();

  protected:
    int OnConfigure(const Frame *, Ratio &, const int *, size_t, AVDecoder::Quality) override;
    int OnProcess(const Frame *, size_t) override;
    void OnFlushBuffers() override;
    int BytesPerFrame() const override;

  private:
    void Destroy();
    int ConvertFrame(SwrContext*, AVFrame*, const AVFrame*);
    struct Params
    {
        int srcSamplingRate, samplingRate;
        AVChannelLayout srcLayout, layout;
        AVSampleFormat srcFormat, format;
    } mParams;
    SynchronizedObject<SwrContext *> mpContext;
    struct AudioBuffer : DataObject
    {
        AVFrame *pObject;
        AudioBuffer();
        ~AudioBuffer();
        void Clear();
        void *Data();
        int Frames() const;
    } mBufferObjects[5];
};

class VideoScaler : public FrameProcessor
{
  public:
    VideoScaler();
    ~VideoScaler();

  protected:
    int OnConfigure(const Frame *, Ratio &, const int *, size_t, AVDecoder::Quality) override;
    int OnProcess(const Frame *, size_t) override;
    void OnFlushBuffers() override;
    int BytesPerFrame() const override;

  private:
    struct Params
    {
        int srcWidth, width, srcHeight, height;
        AVPixelFormat srcFormat, format;
    } mParams;
    SwsContext *mpContext;
    struct PictureBuffer : DataObject
    {
        AVFrame* pFrame;
        PictureBuffer();
        ~PictureBuffer();
        void Clear();
        void *Data();
        int Frames() const;
    } mBufferObjects[3];
};

} // namespace AVUtils

#endif // AV_UTILS_H
