////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: mellinger@neurotechcenter.org
// Description: An AVSource implementation for Windows Media Foundation devices.
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
#include "AVSourceMF.h"

#include "VideoMediaType.h"
#include "AudioMediaType.h"

#include <mutex>
#include <condition_variable>

#include "ComPtr.h"
#include "ComStrings.h"
#include "Errors.h"
#include "MFInit.h"
#include "WebcamPipeline.h"
#include "GrabberTransform.h"

#include "Debugging.h"

struct AVSourceMF::Private
{
    struct AVSource::Properties mProperties;

    MFInit mInit;
    com::Ptr<WebcamPipeline> mpWebcamPipeline;
    struct Tee : GrabberTransform
    {
        HRESULT OnProcess(DWORD, com::Ptr<IMFSample>) override;
        Private* mpPrivate = nullptr;
    };
    Tee* mpTee;
    com::Ptr<IMFTransform> mpTeeTransform;
    com::Ptr<IMFSample> mpSample;
    std::mutex mSampleMutex;
    std::condition_variable mSampleCondition;
    bool mSampleTrigger = false;

    Private();
    ~Private();
    HRESULT SetupCamera(IMFMediaSource*);
};

AVSourceMF::Private::Private()
{
    mpWebcamPipeline = new WebcamPipeline;

    mpTee = new Tee;
    mpTee->mpPrivate = this;
    mpTeeTransform = mpTee;

    mpWebcamPipeline->SetTransform(mpTeeTransform);
}

AVSourceMF::Private::~Private()
{
}

HRESULT AVSourceMF::Private::SetupCamera(IMFMediaSource* pCamera)
{
    HRESULT hr = S_OK;
#if 0 // Set exposure to medium
    com::Ptr<IAMCameraControl> pCameraControl;
    pCamera->QueryInterface(IID_IAMCameraControl, pCameraControl.Assignee());
    if (pCameraControl) {
        long min, max, step, def, control;
        hr = pCameraControl->GetRange(CameraControl_Exposure, &min, &max, &step, &def, &control);
        if (step < 1)
            step = 1;
        long value = min + (((max - min) / step) / 2) * step;
        if (SUCCEEDED(hr))
            hr = pCameraControl->Set(CameraControl_Exposure, value, CameraControl_Flags_Manual);
    }
    if (FAILED(hr))
        return hr;
#endif
#if 0 // Set white balance to auto
    com::Ptr<IAMVideoProcAmp> pVideo;
    pCamera->QueryInterface(IID_IAMVideoProcAmp, pVideo.Assignee());
    if (pVideo)
        hr = pVideo->Set(VideoProcAmp_WhiteBalance, 0, VideoProcAmp_Flags_Auto);
#endif
    return hr;
}

HRESULT
AVSourceMF::Private::Tee::OnProcess(DWORD inStreamID, com::Ptr<IMFSample> inpSample)
{
    if (inStreamID != 0)
        return S_OK;

    std::unique_lock<std::mutex> lock(mpPrivate->mSampleMutex);
    mpPrivate->mpSample = inpSample;
    mpPrivate->mSampleTrigger = true;
    lock.unlock();
    mpPrivate->mSampleCondition.notify_one();
    return S_OK;
}

AVSourceMF::AVSourceMF()
    : p(new Private)
{
}

AVSourceMF::~AVSourceMF()
{
    p->mpWebcamPipeline->Stop();
    p->mpWebcamPipeline->Close();
    p->mpWebcamPipeline->Shutdown();
    delete p;
}

bool AVSourceMF::Init(com::Ptr<IMFMediaSource> pMediaSource, const std::string& cameraName, const VideoMediaType& desiredType)
{
    HRSucceedOrThrow hr = p->SetupCamera(pMediaSource);
    p->mpWebcamPipeline->SetCameraMediaSource(pMediaSource, cameraName);
    p->mpWebcamPipeline->SetDesiredVideoMediaType(desiredType);
    p->mpWebcamPipeline->CreateTopology();
    MFVideoMediaType actualType = p->mpWebcamPipeline->ActualVideoMediaType();

    auto pRGBType = actualType.Strip();
    hr = pRGBType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32);
    p->mpTee->AddInputAvailableType(0, pRGBType);

    p->mpWebcamPipeline->ResolveTopology();

    p->mProperties.width = actualType.width;
    p->mProperties.height = actualType.height;
    p->mProperties.fps = Rate(actualType.framerateN, actualType.framerateD * Time::OneSecond());
    if (actualType.interlaceType != VideoMediaType::none && actualType.interlaceType != VideoMediaType::progressive)
        p->mProperties.fps = p->mProperties.fps * Ratio(1, 2);

    p->mpWebcamPipeline->Start();

    return true;
}

const struct AVSource::Properties& AVSourceMF::Properties() const
{
    return p->mProperties;
}


bool AVSourceMF::WaitForData(std::vector<uint8_t>& outFrameData)
{
    std::unique_lock<std::mutex> lock(p->mSampleMutex);
    p->mSampleCondition.wait(lock, [this]{return p->mSampleTrigger;});
    if (!p->mpSample) // wait aborted
        return false;

    DWORD count = 0;
    HRSucceedOrThrow hr = p->mpSample->GetBufferCount(&count);
    if (count != 1) {
        ErrorStream() << "Unexpected buffer count: " << count;
        return false;
    }

    com::Ptr<IMFMediaBuffer> pBuffer;
    hr = p->mpSample->GetBufferByIndex(0, pBuffer.Assignee());
    DWORD currentLength = 0;
    hr = pBuffer->GetCurrentLength(&currentLength);
    if (currentLength != outFrameData.size()) {
        ErrorStream() << "Unexpected buffer size: " << outFrameData.size() << ", expected " << currentLength;
        return false;
    }

    BYTE* bufferData = nullptr;
    DWORD maxLength = 0;
    hr = pBuffer->Lock(&bufferData, &maxLength, &currentLength);
    ::memcpy(outFrameData.data(), bufferData, outFrameData.size());
    hr = pBuffer->Unlock();

    p->mpSample = nullptr;
    p->mSampleTrigger = false;

    return true;
}

void AVSourceMF::AbortWaiting()
{
    std::unique_lock<std::mutex> lock(p->mSampleMutex);
    p->mpSample = nullptr;
    p->mSampleTrigger = true;
    lock.unlock();
    p->mSampleCondition.notify_one();
}

