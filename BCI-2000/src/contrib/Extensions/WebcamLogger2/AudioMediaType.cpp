////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: mellinger@neurotechcenter.com
// Description: A class representing an audio media type.
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
#include "AudioMediaType.h"

AudioMediaType::AudioMediaType()
{
}

bool AudioMediaType::IsCompatible(const AudioMediaType& other) const
{
  if (codec != other.codec)
    return false;
  if (samplerate != other.samplerate)
    return false;
  if (bitspersample != other.bitspersample)
    return false;
  return true;
}

double AudioMediaType::SqDist(const AudioMediaType& other) const
{
  double total = 0;
  double sr1 = this->samplerate, sr2 = other.samplerate;
  total += 1.0 * (sr1 - sr2) * (sr1 - sr2);
  double bps1 = this->bitspersample, bps2 = other.bitspersample;
  total += 1.0 * (bps1 - bps2) * (bps1 - bps2);
  double ch1 = this->channels, ch2 = other.channels;
  total += 1.0 * (ch1 - ch2) * (ch1 - ch2);
  return total;
}

