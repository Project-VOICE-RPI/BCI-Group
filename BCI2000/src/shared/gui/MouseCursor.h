////////////////////////////////////////////////////////////////////////////////
// $Id: MouseCursor.h 7195 2023-02-07 18:31:03Z mellinger $
// Authors: juergen.mellinger@uni-tuebingen.de
// Description: A class template for objects that replace the mouse cursor
//   during their lifetime, i.e. from construction to destruction.
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
#ifndef MOUSE_CURSOR_H
#define MOUSE_CURSOR_H

#include "Windows.h"

template <int CursorID> class MouseCursor
{
  public:
    MouseCursor() : mPrevCursor(::SetCursor(::LoadCursor(NULL, CursorID)))
    {
    }
    ~MouseCursor()
    {
        ::SetCursor(mPrevCursor);
    }

  private:
    HCURSOR mPrevCursor;
};

typedef MouseCursor<IDC_WAIT> HourglassCursor;

#endif MOUSE_CURSOR_H
