//////////////////////////////////////////////////////////////////////////////
// $Id: PlaybackControl.h 8359 2024-09-23 15:26:18Z mellinger $
// Author: juergen.mellinger@uni-tuebingen.de
// Description: A playback control widget.
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
//////////////////////////////////////////////////////////////////////////////
#ifndef PLAYBACK_CONTROL_H
#define PLAYBACK_CONTROL_H

#include <QWidget>

class BCI2000Viewer;
class QAbstractButton;
class QSlider;
class QComboBox;

class PlaybackControl : public QWidget
{
    Q_OBJECT

  public:
    PlaybackControl(BCI2000Viewer *);
    void updatePosition(int64_t);

  private slots:
    void startToggled(bool);
    void stopClicked();
    void toBeginClicked();
    void toEndClicked();
    void muteClicked();
    void onVolumeSliderValueChanged(int);
    void onRateBoxActivated();
    void onPositionSliderValueChanged(int);

  private:
    BCI2000Viewer *mpViewer;
    QAbstractButton *mpMuteButton, *mpStartButton;
    QSlider *mpVolumeSlider, *mpPositionSlider;
    QComboBox *mpRateBox;
    bool mMuted;
};

#endif // PLAYBACK_CONTROL_H
