////////////////////////////////////////////////////////////////////////////////
// $Id: SWLDAClassifier.h 7463 2023-06-30 14:59:17Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: An implementation of the SWLDA classifier training algorithm.
//   (Matlab's stepwisefit() function translated into C++ by Cristhian Potes).
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
#ifndef SWLDA_CLASSIFIER_H
#define SWLDA_CLASSIFIER_H

#include "Classifier.h"

class SWLDAClassifier : public Classifier
{
  public:
    SWLDAClassifier();
    ~SWLDAClassifier();

    const char *method() const override;

    void setPenter(double);
    double penter() const;
    void setPremove(double);
    double premove() const;
    void setMaxIterations(double);
    double maxIterations() const;

  protected:
    void onClear() override;
    void onInitialize(int count, int dimensions) override;
    void onObserve(double label, const std::vector<double> &data) override;
    void onFinalize(std::vector<double> &) override;

  private:
    struct Private;
    Private *p;
};

#endif // SWLDA_CLASSIFIER_H
