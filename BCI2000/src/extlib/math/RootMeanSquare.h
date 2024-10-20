////////////////////////////////////////////////////////////////////////////////
// $Id: RootMeanSquare.h 7195 2023-02-07 18:31:03Z mellinger $
// Authors: griffin.milsap@gmail.com
// Description: Calculates the Root Mean Square of a series of values
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
#ifndef ROOTMEANSQUARE_H
#define ROOTMEANSQUARE_H

#include <algorithm>
#include <numeric>
#include <valarray>

template <typename T> double RootMeanSquare(const std::valarray<T> &);

// Implementation
template <typename T> double RootMeanSquare(const std::valarray<T> &inData)
{
    std::valarray<T> square = inData * inData;
    double RMS = square.sum() / (double)square.size();
    return sqrt(RMS);
}

template <typename T> double RootMeanSquare(const T &inData)
{
    double squareSum = 0;
    for (size_t i = 0; i < inData.size(); i++)
        squareSum += inData[i] * inData[i];
    return sqrt(squareSum / (double)inData.size());
}

#endif // ROOTMEANSQUARE_H
