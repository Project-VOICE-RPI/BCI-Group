////////////////////////////////////////////////////////////////////////////////
// $Id: ParallelFilterCombination.cpp 7463 2023-06-30 14:59:17Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: A ParallelCombination<> class without templates.
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
#include "ParallelFilterCombination.h"

ParallelFilterCombination &ParallelFilterCombination::Add(Registrar *r)
{
    if (mFilters.empty())
        ParallelCombinationBase::Add(r, &mInput1, &mOutput1);
    else if (mFilters.size() == 1)
        ParallelCombinationBase::Add(r, &mInput2, &mOutput2);
    else
        SuggestDebugging << "More than 2 filters added to ParallelFilterCombination";
    return *this;
}