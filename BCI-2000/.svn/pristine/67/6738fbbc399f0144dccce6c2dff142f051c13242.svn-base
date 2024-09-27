////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: mellinger@neurotechcenter.com
// Description: A wrapper for Windows Media Foundation video media types.
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
#include "MFVideoMediaType.h"
#include "Win32/ErrorExceptions.h"
#include "Exception.h"

#include <mfapi.h>

DWORD MFVideoMediaType::pref[] = {
  22, // RGB32
  21, // ARGB32
};

MFVideoMediaType::MFVideoMediaType(com::Ptr<IMFMediaType> pType)
  : mpType(pType)
{
  if (mpType) {
    if (!IsVideo(mpType))
      throw std_runtime_error << "Not a video media type";

    GUID guid;
    HRSucceedOrThrow hr = pType->GetGUID(MF_MT_SUBTYPE, &guid);
    codec = guid.Data1;
    hr = ::MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &width, &height);
    hr = ::MFGetAttributeRatio(pType, MF_MT_FRAME_RATE, &framerateN, &framerateD);
    if (S_OK != ::MFGetAttributeRatio(pType, MF_MT_PIXEL_ASPECT_RATIO, &pxN, &pxD))
    {
      pxN = 1;
      pxD = 1;
      hr = ::MFSetAttributeRatio(pType, MF_MT_PIXEL_ASPECT_RATIO, pxN, pxD);
    }
    if (S_OK != pType->GetUINT32(MF_MT_INTERLACE_MODE, &interlaceType))
    {
      interlaceType = MFVideoInterlace_Progressive;
      hr = pType->SetUINT32(MF_MT_INTERLACE_MODE, interlaceType);
    }
    avgbitrate = ::MFGetAttributeUINT32(pType, MF_MT_AVG_BITRATE, 0);
    if (avgbitrate == 0)
    {
      avgbitrate = width * height * framerateN / (1.0 * framerateD) * 32;
      hr = pType->SetUINT32(MF_MT_AVG_BITRATE, avgbitrate);
    }
  }
}

MFVideoMediaType::MFVideoMediaType(const VideoMediaType& type)
{
    *static_cast<VideoMediaType*>(this) = type;
}

com::Ptr<IMFMediaType> MFVideoMediaType::Strip() const
{
  com::Ptr<IMFMediaType> pOut;
  if (!mpType)
    return pOut;

  HRSucceedOrThrow hr = ::MFCreateMediaType(pOut.Assignee());

  static GUID guidkeys[] = { MF_MT_MAJOR_TYPE, MF_MT_SUBTYPE };
  for (const auto& key : guidkeys) {
    GUID value;
    HRESULT r = mpType->GetGUID(key, &value);
    if (SUCCEEDED(r))
      hr = pOut->SetGUID(key, value);
  }

  static GUID int32keys[] = {
    MF_MT_INTERLACE_MODE, MF_MT_AVG_BITRATE,
  };
  for (const auto& key : int32keys) {
    UINT32 value;
    HRESULT r = mpType->GetUINT32(key, &value);
    if (SUCCEEDED(r))
      hr = pOut->SetUINT32(key, value);
  }

  static GUID int64keys[] = {
    MF_MT_FRAME_SIZE, MF_MT_FRAME_RATE, MF_MT_PIXEL_ASPECT_RATIO
  };
  for (const auto& key : int64keys) {
    UINT64 value;
    HRESULT r = mpType->GetUINT64(key, &value);
    if (SUCCEEDED(r))
      hr = pOut->SetUINT64(key, value);
  }

  return pOut;
}

bool MFVideoMediaType::IsVideo(com::Ptr<IMFMediaType> pType)
{
  GUID guid;
  HRSucceedOrThrow hr = pType->GetGUID(MF_MT_MAJOR_TYPE, &guid);
  return guid == MFMediaType_Video;
}

