////////////////////////////////////////////////////////////////////////////////
// $Id$
// Author: mellinger@neurotechcenter.org
// Description: Helper functions for interfacing with Video4Linux.
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
#ifndef VIDEO4LINUX_HELPER_H
#define VIDEO4LINUX_HELPER_H

#include "AVSourceEnumerator.h"
#include "VideoMediaType.h"
#include <vector>

void AVEnumerateSourceDevicesVideo4Linux(std::vector<AVSourceEnumerator::Device>&);
std::vector<VideoMediaType> AVListVideoMediaTypesVideo4Linux(const AVSourceEnumerator::Device&);

#endif // VIDEO4LINUX_HELPER_H
