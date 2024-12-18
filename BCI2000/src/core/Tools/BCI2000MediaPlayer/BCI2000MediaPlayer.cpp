////////////////////////////////////////////////////////////////////////////////
// $Id: BCI2000MediaPlayer.cpp 8270 2024-07-23 19:34:53Z mellinger $
// Author: juergen.mellinger@uni-tuebingen.de
// Description: The main() function of the BCI2000MediaPlayer tool.
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

#include <QApplication>
#include <QKeyEvent>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <memory>

#include "GLDisplayWindow.h"
#include "ExceptionCatcher.h"
#include "FileUtils.h"
#include "MediaPlayer.h"
#include "ProcessUtils.h"
#include "TextField.h"
#include "ThreadUtils.h"
#include "QtMain.h"

struct KeyPress
{
    int key;
    std::string text;
};
class KeyPressQueue : public std::list<KeyPress>, public QObject
{
  protected:
    bool eventFilter(QObject *pObject, QEvent *pEvent)
    {
        if (pEvent->type() == QEvent::KeyPress)
        {
            QKeyEvent *p = static_cast<QKeyEvent *>(pEvent);
            KeyPress k = {p->key(), p->text().toLocal8Bit().constData()};
            push_back(k);
            return true;
        }
        return QObject::eventFilter(pObject, pEvent);
    }
};
static KeyPressQueue sKeysPressed;

int MediaPlayerMain(int, char **);

int main(int argc, char **argv)
{
    ProcessUtils::InitializeDesktopIntegration("org.bci2000.Tools");
    QtApplication a(argc, argv);
    qApp->installEventFilter(&sKeysPressed);

    std::string message = "Aborting ";
    message += FileUtils::ApplicationTitle();
    FunctionCall<int(int, char **)> call(&MediaPlayerMain, argc, argv);
    bool finished = ExceptionCatcher().SetMessage(message).Run(call);
    return finished ? call.Result() : -1;
}

class Player : public MediaPlayer, private Runnable
{
  public:
    Player(GUI::DisplayWindow &w) : MediaPlayer(w), mWindow(w), mDoLoop(false)
    {
    }
    ~Player()
    {
        Control().SetOnStateChange(0);
    }
    Player &SetDoLoop(bool b)
    {
        mDoLoop = b;
        return *this;
    }
    bool DoLoop() const
    {
        return mDoLoop;
    }

    void OnRun()
    {
        if (mDoLoop && Control().Eof())
            Control().Stop().Play();
    };

    Player &Open(const std::string &file, int mode)
    {
        Control().SetOnStateChange(0);
        MediaPlayer::Open(file, mode);
        Control().SetOnStateChange(this);
        return *this;
    }

    std::string FileInfo() const
    {
        std::ostringstream oss;
        oss << FileUtils::ExtractFile(Control().File()) << " " << std::fixed << std::setprecision(3)
            << Control().NativeDuration().Seconds() << "s";
        return oss.str();
    }

    std::string VideoInfo() const
    {
        std::ostringstream oss;
        if (Video())
            oss << "video: " << Video().Codec() << "  " << Video().NativeWidth() << " x " << Video().NativeHeight()
                << " x " << Video().FrameCount() << " @ " << Video().NativeFramesPerSecond() << "Hz";
        return oss.str();
    }

    std::string AudioInfo() const
    {
        std::ostringstream oss;
        if (Audio())
            oss << "audio: " << Audio().Codec() << "  " << Audio().NativeChannels() << " x " << Audio().FrameCount()
                << " @ " << Audio().NativeSamplesPerSecond() / 1000 << "kHz";
        return oss.str();
    }

    std::string VideoPosition() const
    {
        std::ostringstream oss;
        if (Video())
            oss << std::fixed << std::setprecision(3) << "video: " << Video().TimePosition().Seconds() << "/"
                << Video().NativeDuration().Seconds() << "s"
                << "  #" << Video().FramePosition() << "  " << std::setprecision(2) << Video().FramesPerSecond()
                << "Hz";
        return oss.str();
    }

    std::string AudioPosition() const
    {
        std::ostringstream oss;
        if (Audio())
            oss << std::fixed << std::setprecision(3) << "audio: " << Audio().TimePosition().Seconds() << "/"
                << Audio().NativeDuration().Seconds() << "s"
                << "  #" << Audio().FramePosition() << " (" << std::showpos << std::setw(3) << -Audio().SampleLag()
                << ")" << std::noshowpos << "  " << Audio().SamplesPerSecond() / 1e3 << "kHz";
        return oss.str();
    }

    std::string PlaybackStatistics() const
    {
        ClockTick clock = Control().PlaybackTick();
        ClockTick::Statistics stat;
        std::string master = "unknown";
        if (clock.type & ClockType::Video)
            master = "Display";
        else if (clock.type & ClockType::Audio)
            master = "Audio";
        else if (clock.type & ClockType::Timer)
            master = "Timer";
        stat = mWindow.FrameClockStatistics();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << "master clock: " << master << "@" << clock.rate.Hertz() << "Hz";
        oss << "  jitter " << std::setprecision(1) << Round(1000 * stat.jitter / stat.interval) / 10.0 << "%"
            << "  cycles lost " << stat.missed;
        return oss.str();
    }

  private:
    GUI::DisplayWindow &mWindow;
    bool mDoLoop;
};

int MediaPlayerMain(int argc, char **argv)
{
    int mode = MediaPlayer::OpenAny;
    bool play = false, loop = false, fullscreen = false;
    char *pFile = 0;

    for (int i = 1; i < argc; ++i)
    {
        char *p = argv[i];
        if (*p == '-')
        {
            if (!::strcmp(p, "-v") || !::strcmp(p, "--video"))
                mode = MediaPlayer::OpenVideo;
            else if (!::strcmp(p, "-a") || !::strcmp(p, "--audio"))
                mode = MediaPlayer::OpenAudio;
            else if (!::strcmp(p, "-p") || !::strcmp(p, "--play"))
                play = true;
            else if (!::strcmp(p, "-l") || !::strcmp(p, "--loop"))
                loop = true;
            else if (!::strcmp(p, "-f") || !::strcmp(p, "--fullscreen"))
                fullscreen = true;
        }
        else
            pFile = p;
    }

    StringUtils::String error;
    if (!pFile)
        error = "No file given.";

    GUI::GLDisplayWindow w;
    Player p(w);
    p.SetDoLoop(loop);

    if (error.Empty() && !p.Open(pFile, mode).Control().Error().Empty())
        error = p.Control().Error();

    int videoHeightPx = 0;
    if (p.Video())
    {
        p.Video().SetScalingMode(GUI::ScalingMode::AdjustHeight);
        videoHeightPx = p.Video().NativeHeight();
        while (videoHeightPx > 512)
            videoHeightPx /= 2;
    }

    w.Hide().SetColor(RGBColor::Black).SetAlignment(GUI::Alignment::Center);
    enum
    {
        fileInfo,
        videoInfo,
        audioInfo,
        videoOverlay,
        audioDevice,
        statistics,
        videoPos,
        audioPos,
        textCount
    };
    std::shared_ptr<TextField> fields[textCount] = 
    {
      std::make_shared<TextField>(w), std::make_shared<TextField>(w), std::make_shared<TextField>(w), 
      std::make_shared<TextField>(w), std::make_shared<TextField>(w), std::make_shared<TextField>(w),
      std::make_shared<TextField>(w), std::make_shared<TextField>(w)
    };
    for (int i = 0; i < textCount; ++i)
        fields[i]->SetTextColor(RGBColor::Lime).SetTextHeight(0.8f).SetAlignment(GUI::Alignment::Center);
    fields[videoOverlay]->SetTextColor(RGBColor::Red).SetTextHeight(0.8f);
    const int lineHeightPx = 18;

    if (videoHeightPx < lineHeightPx)
        videoHeightPx = lineHeightPx;
    w.SetHeight(videoHeightPx + (textCount - 1) * lineHeightPx);
    if (videoHeightPx <= lineHeightPx)
        w.SetWidth(640);
    else if (p.Video())
        w.SetWidth((p.Video().NativeWidth() * videoHeightPx) / p.Video().NativeHeight());

    if (fullscreen)
        w.SetFullscreen(true);

    GUI::Rect r = {0, 0, 1, 0};
    int px = 0;
    for (int i = 0; i < videoOverlay; ++i)
    {
        r.top = r.bottom;
        px += lineHeightPx;
        r.bottom = px * 1.0 / w.Height();
        fields[i]->SetObjectRect(r);
    }
    r.top = r.bottom;
    px += videoHeightPx;
    r.bottom = px * 1.0 / w.Height();
    if (p.Video())
        p.Video().SetObjectRect(r);
    fields[videoOverlay]->SetTextHeight(0.8 * lineHeightPx / videoHeightPx).SetObjectRect(r);
    for (int i = videoOverlay + 1; i < textCount; ++i)
    {
        r.top = r.bottom;
        px += lineHeightPx;
        r.bottom = px * 1.0 / w.Height();
        fields[i]->SetObjectRect(r);
    }
    w.Show();
    fields[fileInfo]->SetText(p.FileInfo());
    fields[audioInfo]->SetText(p.AudioInfo());
    if (!p.Audio().DeviceInfo().Empty())
        fields[audioDevice]->SetText("audio: " + p.Audio().DeviceInfo());
    fields[videoInfo]->SetText(p.VideoInfo());

    if (ProcessUtils::IsInteractive(fileno(stderr)))
    {
        if (error.Empty())
            error = p.Control().Error();
        if (!error.Empty())
        {
            std::cerr << error << std::endl;
            return -1;
        }
    }

    struct : Runnable
    {
        GUI::DisplayWindow *pWindow;
        Player *pPlayer;
        std::shared_ptr<TextField> *fields;
        StringUtils::String *pError;
        void OnRun()
        {
            if (pError && !pError->Empty())
                fields[videoOverlay]->SetText(*pError);
            else if (!pPlayer->Control().Error().Empty())
                fields[videoOverlay]->SetText(pPlayer->Control().Error());
            else if (!pPlayer->Video())
                fields[videoOverlay]->SetText("No video available");
            fields[statistics]->SetText(pPlayer->PlaybackStatistics());
            fields[videoPos]->SetText(pPlayer->VideoPosition());
            fields[audioPos]->SetText(pPlayer->AudioPosition());
        }
    } onWindowUpdate;
    onWindowUpdate.pWindow = &w;
    onWindowUpdate.pPlayer = &p;
    onWindowUpdate.fields = fields;
    onWindowUpdate.pError = &error;
    w.AddListener(GUI::GraphDisplay::OnTick, &onWindowUpdate);

    AVPlayer *pSeek = &p.Audio();
    if (p.Video())
        pSeek = &p.Video();

    w.SetAsyncRendering(true);
    bool done = false;
    while (!done)
    {
        ThreadUtils::SleepForMs(100);
        QApplication::sendPostedEvents();
        QApplication::processEvents();
        if (play)
        {
            play = false;
            p.Control().Play();
        }
        while (!sKeysPressed.empty())
        {
            KeyPress key = sKeysPressed.front();
            switch (*key.text.c_str())
            {
            case 'd':
                SuggestDebugging << "User pressed d(ebug) key";
                break;
            case 'q':
            case 'x':
                done = true;
                break;
            case 'l':
                p.SetDoLoop(!p.DoLoop());
                break;
            case 's':
                p.Control().Stop();
                break;
            case ' ':
                if (p.Control().IsPlaying())
                    p.Control().Pause();
                else
                    p.Control().Play();
                break;
            case '+':
                p.Audio().SetVolume(p.Audio().Volume() + 1. / 16);
                break;
            case '-':
                p.Audio().SetVolume(p.Audio().Volume() - 1. / 16);
                break;
            default:
                if (key.key == Qt::Key_Escape) {
                    done = true;
                }
                else if (key.key == Qt::Key_Left) {
                    pSeek->SeekTo(pSeek->TimePosition() - Time::OneSecond());
                }
                else if (key.key == (Qt::Key_Left | Qt::ShiftModifier)) {
                    pSeek->SeekTo(pSeek->TimePosition() - 60 * Time::OneSecond());
                }
                else if (key.key == (Qt::Key_Left | Qt::ControlModifier)) {
                    pSeek->SeekTo(pSeek->FramePosition() - 1);
                }
                else if (key.key == Qt::Key_Right) {
                    pSeek->SeekTo(pSeek->TimePosition() + Time::OneSecond());
                }
                else if (key.key == (Qt::Key_Right | Qt::ShiftModifier)) {
                    pSeek->SeekTo(pSeek->TimePosition() + 60 * Time::OneSecond());
                }
                else if (key.key == (Qt::Key_Right | Qt::ControlModifier)) {
                    pSeek->SeekTo(pSeek->FramePosition() + 1);
                }
                else if (key.key == Qt::Key_Plus) {
                    p.Audio().SetVolume(p.Audio().Volume() + 1. / 16);
                }
                else if (key.key == Qt::Key_Minus) {
                    p.Audio().SetVolume(p.Audio().Volume() - 1. / 16);
                }
            }
            sKeysPressed.pop_front();
        }
    }
    w.SetAsyncRendering(false);
    w.RemoveListener(GUI::GraphDisplay::OnTick, &onWindowUpdate);
    return 0;
}
