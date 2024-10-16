//////////////////////////////////////////////////////////////////////
// $Id: AVEncoder.h 8304 2024-08-06 15:39:37Z mellinger $
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
#ifndef AV_ENCODER_H
#define AV_ENCODER_H

#include "TimeUtils.h"
#include "Rate.h"

class AVEncoder
{
  public:
    AVEncoder();
    ~AVEncoder();

    AVEncoder(const AVEncoder&) = delete;
    AVEncoder& operator=(const AVEncoder&) = delete;

    AVEncoder& OpenFile(const std::string& file);
    enum { anyCodec = 0, h264 = 1, mp3 = 100 };
    AVEncoder& AddVideoStream(int* pStreamIndex, int codec = anyCodec);
    AVEncoder& InitializeVideoStream(int streamIndex, int width, int height, const Rate& fps, int preset = 0, int compressionFactor = 8);
    AVEncoder& AddAudioStream(int* pStreamIndex, int codec = anyCodec);
    AVEncoder& InitializeAudioStream(int streamIndex, int channels, int bitspersample, const Rate& sps);
    AVEncoder& BeginWriting();
    AVEncoder& WriteFrame(int streamIndex, const void*, int bytes, Time::Interval timestamp);
    AVEncoder& FinalizeStream(int streamIndex);
    AVEncoder& CloseFile();

    std::string Error() const;

  private:
    struct Private;
    Private* p;
};

#endif // AV_ENCODER_H
