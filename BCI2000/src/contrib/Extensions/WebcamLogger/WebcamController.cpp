/////////////////////////////////////////////////////////////////////////////
// $Id: WebcamController.cpp 8340 2024-09-09 13:57:34Z mellinger $
// Authors: adam.wilson@uc.edu & Alex Belsten belsten@neurotechcenter.org,
//   mellinger@neurotechcenter.org
//
// Description: The WebcamController controls a WebcamRecorder instance
//   and records the current frame number to a bcievent.
//
// Event Variables:
//   WebcamFrame<n> - The current frame number for camera index n 
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
/////////////////////////////////////////////////////////////////////////////
#include "WebcamController.h"

#include "BCIEvent.h"
#include "BCIStream.h"
#include "ChildProcess.h"
#include "Thread.h"
#include "Runnable.h"
#include "Streambuf.h"
#include "SysError.h"

struct WebcamController::Private
{
  std::string mError;

  std::string mBaseName;
  int mFilePart = 0;

  int mCameraIndex = -1;
  ChildProcess* mpProcess = nullptr;
  std::iostream mStdIO{ nullptr };

  MemberCall<void(WebcamController::Private*)> mLoggerThreadCall{ 
    &WebcamController::Private::loggerThreadFunc, this
  };
  Thread mLoggerThread{
    &mLoggerThreadCall, "WebcamLogger event thread"
  };

  void loggerThreadFunc();
  void awaitGreeting();
  void sendCommand(const std::string&);

  std::string createFileName() const;
};

void WebcamController::Private::awaitGreeting()
{
    const int timeoutSeconds = 20;
    std::string greeting;
    mpProcess->standardIO().Input()->Wait(Time::Seconds(timeoutSeconds));
    while (mpProcess->standardIO().Input()->Test())
    {
        std::string line;
        std::getline(mStdIO, line);
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!greeting.empty())
            greeting += "\n";
        greeting += line;
    }
    if (greeting.empty())
        greeting = "No response from WebcamRecorder within " + std::to_string(timeoutSeconds) + "s";
    if (greeting != "OK")
        mError = greeting;
}

void WebcamController::Private::sendCommand(const std::string& inCommand)
{
  if (!inCommand.empty())
    mStdIO << inCommand << std::endl;
  if (mpProcess->standardIO().Input()->Wait(Time::Seconds(1)))
  {
    std::string error;
    std::getline(mStdIO, error);
    if (!error.empty() && error.back() == '\r')
      error.pop_back();
    if (!error.empty() && mError.empty())
      mError = error;
  }
}

std::string WebcamController::Private::createFileName() const
{
  std::string fileName = mBaseName + "_" + std::to_string(mCameraIndex) + "_vid.";
  if (mFilePart > 1)
    fileName += "part" + std::to_string(mFilePart) + ".";
  fileName += "mp4";
  return fileName;
}

void WebcamController::Private::loggerThreadFunc()
{
    WithThreadPriority(ThreadUtils::Priority::Maximum - 1)
    {
        Waitables waitables;
        waitables.Add(mpProcess->standardError().Input());
        waitables.Add(mpProcess);
        const Waitable* pWaitable;
        while (pWaitable = waitables.Wait())
        {
            if (pWaitable == mpProcess->standardError().Input())
            {
                std::istream is(&mpProcess->standardError());
                std::string line;
                std::getline(is, line);
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                if (line == "end")
                    return;
                else if (line.find("Warning: ") == 0)
                    bciwarn << line;
                bcievent << "WebcamFrame" << mCameraIndex << " " << line;
            }
            else if (pWaitable == mpProcess)
            {
                // If there is data in the process' stdout after termination, it's an error message.
                while (mpProcess->standardIO().Input()->Test())
                {
                    std::istream is(&mpProcess->standardIO());
                    std::string line;
                    std::getline(is, line);
                    if (!line.empty() && line.back() == '\r')
                        line.pop_back();
                    bcierr << line;
                }
                return;
            }
        }
    }
    // If the thread has been terminated without waiting for "end", we need to drain
    // the standardError channel, or we will immediately end the thread next time it runs.
    while (mpProcess->standardError().Input()->Test())
    {
        char buf[512];
        mpProcess->standardError().Input()->Read(buf, sizeof(buf));
    }
}

const std::string& WebcamController::ExecutableName()
{
  static std::string executableName = "WebcamRecorder";
  return executableName;
}

WebcamController::WebcamController()
  : p(new Private)
{
}

WebcamController::~WebcamController()
{
  p->mLoggerThread.Terminate();
  p->sendCommand("quit");
  p->mpProcess->Wait(Time::Seconds(5));
  delete p->mpProcess;
  delete p;
}

const std::string& WebcamController::Error() const
{
  return p->mError;
}

void WebcamController::Initialize(int camIndex, const Parameters &params)
{
  p->mCameraIndex = camIndex;
  std::ostringstream args;
  args << "--camera " << camIndex << " --width " << params.width
       << " --height " << params.height << " --fps " << params.fps;
  args << " --video-profile " << params.videoprofile;
  if (!params.url.empty())
    args << " --url " << params.url;
  if (params.bufferingtime >= 0)
    args << " --bufferingtime " << params.bufferingtime;
  if (params.maxbuffertimems >= 0)
    args << " --maxbuffertimems " << params.maxbuffertimems;
  if (!params.audiourl.empty())
    args << " --audiourl " << params.audiourl;
  if (params.audiobufferingtime >= 0)
    args << " --audiobufferingtime " << params.audiobufferingtime;
  if (params.audiomaxbuffertimems >= 0)
    args << " --audiomaxbuffertimems " << params.audiomaxbuffertimems;
  p->mpProcess = new ChildProcess(ExecutableName(), args.str());
  p->mStdIO.rdbuf(&p->mpProcess->standardIO());
  p->mStdIO.clear();
  if (!p->mpProcess->run())
    p->mError = "Could not start " + ExecutableName() + " process: "
    + std::string(SysError(p->mpProcess->result()).Message());
  p->awaitGreeting();
}

void WebcamController::ShowWindow()
{
  p->sendCommand("show");
}

void WebcamController::HideWindow()
{
  p->sendCommand("hide");
}

void WebcamController::SetDecimation(int decimation)
{
  p->sendCommand("decimation " + std::to_string(decimation));
}

void WebcamController::SetTimestampOption(int option)
{
  p->sendCommand("timestamp " + std::to_string(option));
}

void WebcamController::StartRecording(const std::string& baseName)
{
  p->mBaseName = baseName;
  p->mFilePart = 1;
  p->sendCommand("record " + p->createFileName());
  if (p->mError.empty()) {
    p->mLoggerThread.Start();
    bcidbg << "Started Recording Camera " << p->mCameraIndex;
  }
}

void WebcamController::StopRecording()
{
  p->sendCommand("stop");
  p->mFilePart = 0;
  p->mLoggerThread.Wait(TimeUtils::TimeInterval::Seconds(5));
  p->mLoggerThread.Terminate();
  bcidbg << "Stopped Recording Camera " << p->mCameraIndex;
}

void WebcamController::IncrementFilePart()
{
  if (p->mFilePart > 0) {
    ++p->mFilePart;
    bcievent << "WebcamFrame" << p->mCameraIndex << " 0";
    p->sendCommand("switchto " + p->createFileName());
    bcidbg << "Camera " << p->mCameraIndex << " switched to file part " << p->mFilePart;
  }
}

