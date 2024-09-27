////////////////////////////////////////////////////////////////////////////////
//  $Id: RandomFilter.h 7195 2023-02-07 18:31:03Z mellinger $
//  Author:      juergen.mellinger@uni-tuebingen.de
//  Description: A filter that returns zero-mean white noise multiplied by the
//               input signal's value.
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
#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H

#include "GenericFilter.h"
#include "RandomGenerator.h"

class RandomFilter : public GenericFilter
{
  public:
    RandomFilter();
    ~RandomFilter();

    void Preflight(const SignalProperties &, SignalProperties &) const;
    void Initialize(const SignalProperties &, const SignalProperties &);
    void Process(const GenericSignal &, GenericSignal &);

  private:
    RandomGenerator mRandomGenerator;
    float GetRandomUniform();
    float (RandomFilter::*mpGetRandom)();
    enum
    {
        none,
        uniform,
    } RandomType;
};
#endif // RANDOM_FILTER_H
