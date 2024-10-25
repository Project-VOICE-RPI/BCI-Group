//////////////////////////////////////////////////////////////////////////////
// $Id: PlaybackControl.cpp 8359 2024-09-23 15:26:18Z mellinger $
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
#include "PlaybackControl.h"
#include "BCI2000Viewer.h"
#include "Ratio.h"
#include <cmath>

float sliderToVolume(float f)
{
    return Ratio::FromDecibel((f - 100) / 20).To<float>();
}

PlaybackControl::PlaybackControl(BCI2000Viewer *pViewer) : QWidget(pViewer), mpViewer(pViewer), mMuted(false)
{
    setWindowTitle("Playback Control");
    setWindowFlags(Qt::Tool);

    QHBoxLayout *pLayout = new QHBoxLayout;

    QToolButton *pButton = new QToolButton(this);
    pButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    pLayout->addWidget(pButton);
    connect(pButton, &QAbstractButton::clicked, this, &PlaybackControl::toBeginClicked);

    pButton = new QToolButton(this);
    pButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    pButton->setCheckable(true);
    pLayout->addWidget(pButton);
    connect(pButton, &QAbstractButton::toggled, this, &PlaybackControl::startToggled);
    mpStartButton = pButton;

    pButton = new QToolButton(this);
    pButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    pLayout->addWidget(pButton);
    connect(pButton, &QAbstractButton::clicked, this, &PlaybackControl::stopClicked);

    pButton = new QToolButton(this);
    pButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    pLayout->addWidget(pButton);
    connect(pButton, &QAbstractButton::clicked, this, &PlaybackControl::toEndClicked);

    pButton = new QToolButton(this);
    pButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(pButton, &QAbstractButton::clicked, this, &PlaybackControl::muteClicked);
    pLayout->addWidget(pButton);
    mpMuteButton = pButton;

    mpVolumeSlider = new QSlider(Qt::Horizontal, this);
    mpVolumeSlider->setRange(0, 100);
    mpVolumeSlider->setValue(80);
    connect(mpVolumeSlider, &QSlider::valueChanged, this, &PlaybackControl::onVolumeSliderValueChanged);
    pLayout->addWidget(mpVolumeSlider);
    mpVolumeSlider->setMinimumWidth(50);

    mpRateBox = new QComboBox(this);
    mpRateBox->addItem("0.2x", QVariant(0.2));
    mpRateBox->addItem("0.5x", QVariant(0.5));
    mpRateBox->addItem("1.0x", QVariant(1.0));
    mpRateBox->addItem("2.0x", QVariant(2.0));
    mpRateBox->addItem("5.0x", QVariant(5.0));
    mpRateBox->addItem("10.0x", QVariant(10.0));
    mpRateBox->setCurrentIndex(2);
    connect(mpRateBox, QOverload<int>::of(&QComboBox::activated), this, &PlaybackControl::onRateBoxActivated);
    pLayout->addWidget(mpRateBox);

    QVBoxLayout *pMainLayout = new QVBoxLayout;

    mpPositionSlider = new QSlider(Qt::Horizontal, this);
    mpPositionSlider->setRange(0, 9999);
    mpPositionSlider->setValue(0);
    connect(mpPositionSlider, &QSlider::valueChanged, this, &PlaybackControl::onPositionSliderValueChanged);
    pMainLayout->addWidget(mpPositionSlider);
    pMainLayout->addLayout(pLayout);
    setLayout(pMainLayout);
}

void PlaybackControl::startToggled(bool state)
{
    if (state)
    {
        if (mMuted)
            mpViewer->SetVolume(0);
        else
            mpViewer->SetVolume(sliderToVolume(mpVolumeSlider->value()));
        onRateBoxActivated();
        mpViewer->Play();
    }
    else
    {
        mpViewer->Pause();
    }
}

void PlaybackControl::stopClicked()
{
    mpStartButton->setChecked(false);
}

void PlaybackControl::toBeginClicked()
{
    mpStartButton->setChecked(false);
    mpViewer->ToFirstSample();
}

void PlaybackControl::toEndClicked()
{
    mpStartButton->setChecked(false);
    mpViewer->ToLastSample();
}

void PlaybackControl::muteClicked()
{
    mMuted = !mMuted;
    mpMuteButton->setIcon(style()->standardIcon(mMuted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
    if (mMuted)
        mpViewer->SetVolume(0);
    else
        mpViewer->SetVolume(sliderToVolume(mpVolumeSlider->value()));
}

void PlaybackControl::onVolumeSliderValueChanged(int value)
{
    if (mMuted)
        muteClicked();
    else
        mpViewer->SetVolume(sliderToVolume(value));
}

void PlaybackControl::onRateBoxActivated()
{
    float rate = mpRateBox->itemData(mpRateBox->currentIndex()).toFloat();
    mpViewer->SetPlaybackRatio(rate);
}

void PlaybackControl::onPositionSliderValueChanged(int value)
{
    mpStartButton->setChecked(false);
    double positions = mpViewer->NumSamples() - mpViewer->NumDisplaySamples();
    positions = std::max(positions, 1.0);
    double position = positions * value / mpPositionSlider->maximum();
    mpViewer->SetSamplePos(position);
}

void PlaybackControl::updatePosition(int64_t sample)
{
    if (!mpPositionSlider->isSliderDown())
    {
        bool b = mpPositionSlider->blockSignals(true);
        double positions = mpViewer->NumSamples() - mpViewer->NumDisplaySamples();
        positions = std::max(positions, 1.0);
        double value = mpPositionSlider->maximum() * sample / positions;
        mpPositionSlider->setValue(value);
        if (sample == positions - 1)
            mpStartButton->setChecked(false);
        mpPositionSlider->blockSignals(b);
    }
}