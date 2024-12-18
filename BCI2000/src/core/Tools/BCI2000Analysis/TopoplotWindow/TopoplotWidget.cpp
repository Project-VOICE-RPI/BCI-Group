////////////////////////////////////////////////////////////////////////////////
// $Id: TopoplotWidget.cpp 8270 2024-07-23 19:34:53Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: A widget that displays topographic plots. The signal must
//   contain electrode names as channel labels for this to work.
//   Channels without electrode names are not plotted.
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
#include "TopoplotWidget.h"
#include "Color.h"
#include "ElectrodeNames.h"
#include "GenericSignal.h"
#include "ThinPlateSplinesInterpolation.h"

#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QToolTip>

namespace
{
const int sLegendWidth = 20;
const float sHeadRadius = 0.4;

enum Mode
{
    Head, Rect
};

inline float sqr(float x)
{
    return x * x;
}

QRgb colorMap(float value /* between 0 and 1 */)
{
    RGBColor c = IsNaN(value) ? RGBColor::Black : RGBColor::FromHSV(value * 2. / 3., 1., 1.);
    return c.ToQRgb();
}

GUI::Point synthesizeLocation(int channel, int channelCount)
{
    // Approximate a square and place channels within it
    // Get smallest number with a square greater or equal channel count
    int n = 1;
    while (n * n < channelCount)
        ++n;
    // Place the channel into an n-by-n square
    int x = channel % n, y = channel / n;
    GUI::Point p = { float(x) / n + 1.f / (2*n), float(y) / n + 1.f / (2*n) };
    return p;
}

float locationGridSize(int channelCount)
{
    int n = 1;
    while (n * n < channelCount)
      ++n;
    return 1.f / n;
}

} // namespace

struct TopoplotWidget::Private : QObject
{
    PhysicalUnit mValueUnit;
    std::vector<std::string> mNames;
    std::vector<GUI::Point> mLocations;
    std::vector<int> mChannels;
    std::vector<float> mValues;
    float mMinVal, mMaxVal;
    int mMode;
    float mGridSize; // for mMode == Rect
    ThinPlateSplinesInterpolation mInterpolation; // for mMode == Head
    Private(QObject *parent) : QObject(parent)
    {
    }
};

TopoplotWidget::TopoplotWidget(QWidget *parent) : QWidget(parent), p(new Private(this))
{
}

void TopoplotWidget::setData(const GenericSignal &s, int element)
{
    p->mValueUnit = s.Properties().ValueUnit();
    p->mNames.clear();
    p->mValues.clear();
    p->mLocations.clear();
    p->mChannels.clear();
    p->mMode = Head;

    for (int ch = 0; ch < s.Channels(); ++ch)
    {
        auto label = s.Properties().ChannelLabel(ch);
        auto pLocation = ElectrodeNames::getLocationFromName(label);
        if (pLocation)
        {
            p->mNames.push_back(label);
            p->mLocations.push_back(*pLocation);
            p->mChannels.push_back(ch);
        }
    }
    if (p->mLocations.empty())
    {
        for (int ch = 0; ch < s.Channels(); ++ch)
        {
            auto label = "Ch" + s.Properties().ChannelLabel(ch);
            auto location = synthesizeLocation(ch, s.Channels());
            p->mNames.push_back(label);
            p->mLocations.push_back(location);
            p->mChannels.push_back(ch);
        }
        p->mMode = Rect;
        p->mGridSize = locationGridSize(s.Channels());
    }

    if (p->mLocations.size() < 3)
        return;
    p->mInterpolation.setPoints(p->mLocations);

    for (const auto &ch : p->mChannels)
        p->mValues.push_back(s(ch, element));
    float min = Inf<float>(), max = -Inf<float>();
    for (const auto &value : p->mValues)
    {
        min = std::min(min, value);
        max = std::max(max, value);
    }
    p->mMinVal = min;
    p->mMaxVal = max;
    p->mInterpolation.setValues(p->mValues);

    update();
}

void TopoplotWidget::paintEvent(QPaintEvent *ev)
{
    if (p->mNames.empty())
        return;

    int width = size().width() - sLegendWidth;
    int height = size().height();
    QImage buffer(width, height, QImage::Format_RGB32);
    buffer.fill(Qt::white);
    QPainter painter(this);

    if (p->mMode == Head)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                GUI::Point point = {1.0 * x / width, 1.0 * y / height};
                float r2 = sqr(point.x - 0.5) + sqr(point.y - 0.5);
                if (r2 <= sqr(sHeadRadius) && ev->rect().contains(x, y))
                {
                    float value = p->mInterpolation.interpolateAt(point);
                    value -= p->mMinVal;
                    value /= p->mMaxVal - p->mMinVal;
                    unsigned int c = colorMap(value);
                    buffer.setPixel(x, y, c);
                }
            }
        }
        painter.fillRect(0, 0, size().width(), size().height(), Qt::white);
        painter.drawImage(0, 0, buffer);
    }
    else if (p->mMode == Rect)
    {
        for (int i = 0; i < p->mLocations.size(); ++i)
        {
            float x = p->mLocations[i].x * width, y = p->mLocations[i].y * height,
                  dx = p->mGridSize * width, dy = p->mGridSize * height;
            float value = p->mValues[i];
            value -= p->mMinVal;
            value /= p->mMaxVal - p->mMinVal;
            unsigned int c = colorMap(value);
            painter.fillRect(x - dx/2, y - dy/2, dx + 1, dy + 1, c);
        }
    }

    painter.setPen(Qt::black);
    for (int i = 0; i < p->mLocations.size(); ++i)
    {
        float x = p->mLocations[i].x * width, y = p->mLocations[i].y * height, r = std::min(width, height) / 100.0f;
        painter.drawEllipse(QPointF(x, y), r, r);
        QString label = QString::fromUtf8(p->mNames[i].c_str());
        painter.drawText(QPointF(x + 1.5 * r, y), label);
    }

    if (p->mMode == Head)
    {
        QPen pen = painter.pen();
        pen.setWidth(2);
        painter.setPen(pen);
        // Draw head shape, nose, and ears.
        // Nose and ears are taken from EEGLAB's topoplot.m.
        float rmax = 0.4;
        float basex = .18 * rmax;
        float tip = rmax * 1.15, base = rmax - .004;
        QPointF p0(0, 0), p1(-basex, -base), p2(0, -tip), p3(basex, -base);
        for (auto p : {&p0, &p1, &p2, &p3})
        {
            *p += QPointF(0.5, 0.5);
            p->rx() *= width;
            p->ry() *= height;
        }
        painter.drawEllipse(p0, sHeadRadius * width, sHeadRadius * height);
        painter.drawLine(p1, p2);
        painter.drawLine(p2, p3);

        float EarX[] = {.497, .510, .518, .5299, .5419, .54, .547, .532, .510, .489};
        float EarY[] = {.0555, .0775, .0783, .0746, .0555, -.0055, -.0932, -.1313, -.1384, -.1199};
        for (int xsign = -1; xsign < 2; xsign += 2)
        {
            std::vector<QPointF> points;
            points.reserve(sizeof(EarX) / sizeof(*EarX));
            for (int i = 0; i < points.capacity(); ++i)
            {
                points.push_back(QPointF(xsign * EarX[i], -EarY[i]));
            }
            for (auto &p : points)
            {
                p *= 0.8;
                p += QPointF(0.5, 0.5);
                p.rx() *= width;
                p.ry() *= height;
            }
            painter.drawPolyline(points.data(), points.size());
        }
    }

    // legend
    int legendheight = 0.8 * height;
    QImage legend(sLegendWidth, legendheight, QImage::Format_RGB32);
    for (int y = 0; y < legendheight; ++y)
    {
        unsigned int c = colorMap(1. - 1. * y / legendheight);
        for (int x = 0; x < sLegendWidth; ++x)
        {
            legend.setPixel(x, y, c);
        }
    }
    painter.drawImage(width, (height - legendheight) / 2, legend);
    QString text = QString::number(p->mMaxVal, 'g', 3) + " ";
    int textwidth = fontMetrics().boundingRect(text).width();
    int textheight = fontMetrics().height();
    painter.drawText(width - textwidth, (height - legendheight) / 2 + textheight / 2, text);
    text = QString::number(p->mMinVal, 'g', 3) + " ";
    textwidth = fontMetrics().boundingRect(text).width();
    painter.drawText(width - textwidth, height - (height - legendheight) / 2 + textheight / 2, text);
}

void TopoplotWidget::mousePressEvent(QMouseEvent *ev)
{
    QPointF pos = ev->pos();
    auto size = this->size();
    GUI::Point where = {pos.x() / size.width(), pos.y() / size.height()};
    float value = p->mInterpolation.interpolateAt(where);
    std::string s = p->mValueUnit.RawToPhysical(value);
    QString text = QString::fromUtf8(s.c_str());
    QToolTip::showText(ev->globalPos(), text, this);
}

void TopoplotWidget::mouseReleaseEvent(QMouseEvent *)
{
    QToolTip::hideText();
}

QSize TopoplotWidget::minimumSizeHint() const
{
    int count = ::ceil(::sqrt(p->mLocations.size()));
    count *= fontMetrics().averageCharWidth() * 8;
    return QSize(count + sLegendWidth, count);
}
