////////////////////////////////////////////////////////////////////////////////
// $Id: Version.cpp.in 5877 2019-02-18 15:57:59Z mellinger $
// Author: juergen.mellinger@uni-tuebingen.de
// Description: Version information template, to be filled in by CMake at
//   configuration time.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2019: BCI2000 team and many external contributors ]
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
#include "VersionInfo.h"
#include "Compiler.h"

const VersionInfo VersionInfo::Current(
  "$Version: 3.6.8364 $"
  "$Source Revision: 8364 $"
  "$Source Date: 2024-09-26T20:29:41Z $"
  "$Build Date: 2024-09-27Z $"
  "$Build Type: " BUILD_TYPE " $"
  "$Build User: " BUILD_USER " $"
  "$Config: " BUILD_CONFIG " $"
  "$Compiler: " COMPILER_NAME " $"
);
