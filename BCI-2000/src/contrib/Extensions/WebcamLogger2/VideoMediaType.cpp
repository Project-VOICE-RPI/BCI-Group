////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: mellinger@neurotechcenter.com
// Description: A class that represents a video media type.
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
#include "VideoMediaType.h"

#include <cmath>

VideoMediaType::VideoMediaType()
{
}

bool VideoMediaType::IsCompatible(const VideoMediaType& other) const
{
  if (codec != other.codec)
    return false;
  if (width != other.width)
    return false;
  if (height != other.height)
    return false;
  double pxr = 1.0 * pxN / pxD,
    other_pxr = 1.0 * other.pxN / other.pxD;
  if (::fabs(1.0 - pxr / other_pxr) > 0.05)
    return false;
  double fps = EffectiveFps(),
    other_fps = other.EffectiveFps();
  if (::fabs(1.0 - fps / other_fps) > 0.05)
    return false;
  return true;
}

double VideoMediaType::EffectiveFps() const
{
    double fps = 1.0 * framerateN / framerateD;
    if (interlaceType != none && interlaceType != progressive)
        fps /= 2;
    return fps;
}

double VideoMediaType::SqDist(const VideoMediaType& other) const
{
  double total = 0;
  double w1 = this->width, w2 = other.width, h1 = this->height, h2 = other.height;
  total += 1.0 * (w1 - w2) * (w1 - w2);
  total += 1.0 * (h1 - h2) * (h1 - h2);
  double f1 = this->EffectiveFps();
  double f2 = other.EffectiveFps();
  total += 5e3 * (f1 - f2) * (f1 - f2);
  return total;
}

std::string VideoMediaType::CodecAsString() const
{
    std::string s(' ', sizeof(codec));
    for (int i = 0; i < sizeof(codec); ++i)
        s[i] = (codec >> (8*i)) & 0xff;
    return s;
}

std::ostream& VideoMediaType::InsertInto(std::ostream& os) const
{
    os << CodecAsString() << " " << width << "x" << height << "@" << EffectiveFps() << "Hz";
    return os;
}
