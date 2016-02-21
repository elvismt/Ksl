/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <Ksl/ChartLinscale_p.h>
#include <Ksl/ChartItem.h>
#include <Ksl/Chart.h>

KSL_BEGIN_NAMESPACE

ChartLinscale::ChartLinscale(const QString &name)
    : ChartScale(new ChartLinscalePrivate(this, name))
{
    KSL_PUBLIC(ChartLinscale);

    // The order of creation must be preserved!
    auto axis = new ChartAxis(Qt::Horizontal, "X_Axis");
    m->axisList.append(axis);
    axis->setComponents("line,ticksDown,arrow,title");

    axis = new ChartAxis(Qt::Horizontal, "BottomAxis");
    axis->setComponents("line,ticksDown,title");
    m->axisList.append(axis);

    axis = new ChartAxis(Qt::Horizontal, "TopAxis");
    axis->setComponents("line,ticksDown,title");
    m->axisList.append(axis);

    axis = new ChartAxis(Qt::Vertical, "Y_Axis");
    axis->setComponents("line,ticksDown,arrow,title");
    m->axisList.append(axis);

    axis = new ChartAxis(Qt::Vertical, "LeftAxis");
    axis->setComponents("line,ticksDown,title");
    m->axisList.append(axis);

    axis = new ChartAxis(Qt::Vertical, "RightAxis");
    axis->setComponents("line,ticksDown,title");
    m->axisList.append(axis);

    for (auto axis : m->axisList)
        axis->setScale(this);
    rescale();
}


ChartLinscalePrivate::~ChartLinscalePrivate() {
    for (auto axis : axisList) {
        delete axis;
    }
}


ChartAxis* ChartLinscale::axis(AxisKey key) const {
    KSL_PUBLIC(const ChartLinscale);

    // As you can see order is important
    switch (key) {
        case X_Axis:
            return m->axisList[0];
        case BottomAxis:
            return m->axisList[1];
        case TopAxis:
            return m->axisList[2];
        case Y_Axis:
            return m->axisList[3];
        case LeftAxis:
            return m->axisList[4];
        case RightAxis:
            return m->axisList[5];
    }
    return nullptr;
}


QPoint ChartLinscale::map(const QPointF &p) const {
    KSL_PUBLIC(const ChartLinscale);
    QPoint ret;
    double tmp;

    tmp = (p.x() - m->xMin) / m->width;
    ret.setX(m->chartXmin + qRound(tmp*m->chartWidth));
    tmp = (p.y() - m->yMin) / m->height;
    ret.setY(m->chartYmax - qRound(tmp*m->chartHeight));

    return ret;
}


QPointF ChartLinscale::unmap(const QPoint &p) const {
    KSL_PUBLIC(const ChartLinscale);
    QPointF ret;
    double tmp;

    tmp = (p.x() - m->chartXmin) / m->chartWidth;
    ret.setX(m->xMin + tmp*m->width);
    tmp = (m->chartYmax - p.y()) / m->chartHeight;
    ret.setY(m->yMin + tmp*m->height);

    return ret;
}


QRect ChartLinscale::chartRect() const {
    KSL_PUBLIC(const ChartLinscale);
    return QRect(m->chartXmin, m->chartYmin,
                 m->chartWidth, m->chartHeight);
}


QRectF ChartLinscale::dataRect() const {
    KSL_PUBLIC(const ChartLinscale);
    return QRect(m->xMin, m->yMin,
                 m->width, m->height);
}


void ChartLinscale::rescale() {
    KSL_PUBLIC(ChartLinscale);
    if (m->itemList.isEmpty()) {
        m->xMin = 0.0;
        m->xMax = 1.0;
        m->yMin = 0.0;
        m->yMax = 1.0;
        m->width = 1.0;
        m->height = 1.0;
        return;
    }

    auto iter = m->itemList.begin();
    auto end = m->itemList.end();
    auto item = *iter++;

    // Do not adjust scale for invisible objects or
    // objects explicitly marked to be not rescalable
    bool firstRescalable = item->rescalable() && item->visible();
    while (iter != end && !firstRescalable) {
        item = *iter++;
        firstRescalable = item->rescalable() && item->visible();
    }
    if (!firstRescalable) {
        return;
    }
    auto itemRect = item->dataRect();
    m->xMin = itemRect.left();
    m->xMax = itemRect.right();
    m->yMin = itemRect.top();
    m->yMax = itemRect.bottom();

    while (iter != end) {
        item = *iter++;
        if (item->rescalable() && item->visible()) {
            itemRect = item->dataRect();
            if (itemRect.left() < m->xMin) m->xMin = itemRect.left();
            if (itemRect.right() > m->xMax) m->xMax = itemRect.right();
            if (itemRect.top() < m->yMin) m->yMin = itemRect.top();
            if (itemRect.bottom() > m->yMax) m->yMax = itemRect.bottom();
        }
    }

    // Expand area visible to a little bigger than the area data
    // this ensures that all possible symbol borders are visible
    m->width = m->xMax - m->xMin;
    double bound = m->width / 20.0;
    m->xMin -= bound;
    m->xMax += bound;
    m->width += 2.0*bound;

    m->height = m->yMax - m->yMin;
    bound = m->height / 20.0;
    m->yMin -= bound;
    m->yMax += bound;
    m->height += 2.0*bound;
}


void ChartLinscale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(ChartLinscale);

    // Tell the chart that something is wrong if there is NaN or Inf
    // In the data ranges.
    if (!qIsFinite(m->width) || ! qIsFinite(m->height) ||
        m->width==0 || m->height==0)
    {
        if (m->chart) {
            m->chart->informError();
        }
        return;
    }
    m->chartXmin = rect.left() + m->xLowBound;
    m->chartXmax = rect.right() - m->xUpBound;
    m->chartWidth = m->chartXmax - m->chartXmin;
    m->chartYmin = rect.top() + m->yLowBound;
    m->chartYmax = rect.bottom() - m->yUpBound;
    m->chartHeight = m->chartYmax - m->chartYmin;

    painter->save();
    painter->setClipRect(chartRect());
    ChartScale::paint(rect, painter);
    painter->restore();

    // This set axis limits and manages minor
    // details
    m->setupAxis();
    for (auto axis : m->axisList) {
        if (axis->visible()) {
            axis->paint(painter);
        }
    }
}


void ChartLinscalePrivate::setupAxis() {
    ChartAxis *axis;

    for (int k=0; k<3; ++k) {
        axis = axisList[k];
        axis->setEnds(xMin, xMax, yMin);
        if (axis->sampler()->mode() == ChartAxisSampler::AutoDecimal)
            axis->sampler()->autoSampleDecimal(
                 xMin, xMax, chartWidth / 90);
    }
    // X axis have another anchor
    axisList[0]->setEnds(xMin, xMax, 0.0);

    for (int k=3; k<6; ++k) {
    axis = axisList[k];
        axis->setEnds(yMin, yMax, xMin);
        if (axis->sampler()->mode() == ChartAxisSampler::AutoDecimal)
            axis->sampler()->autoSampleDecimal(
                 yMin, yMax, chartHeight / 90);
    }
    // Y axis have another anchor
    axisList[3]->setEnds(yMin, yMax, 0.0);

    // Axis choosing strategy is the following: show X and Y axis
    // if the origin is in the viewport. Otherwise show the bounding axis
    if (autoChooseAxis) {
        bool xAxisOut = yMin > 0.0 || yMax < 0.0;
        bool yAxisOut = xMin > 0.0 || xMax < 0.0;
        if (xAxisOut || yAxisOut) {
            axisKeys = BottomAxis|TopAxis|LeftAxis|RightAxis;
            axisList[0]->setVisible(false);
            axisList[1]->setVisible(true);
            axisList[2]->setVisible(true);
            axisList[3]->setVisible(false);
            axisList[4]->setVisible(true);
            axisList[5]->setVisible(true);
        }
        else {
            axisKeys = X_Axis|Y_Axis;
            axisList[0]->setVisible(true);
            axisList[1]->setVisible(false);
            axisList[2]->setVisible(false);
            axisList[3]->setVisible(true);
            axisList[4]->setVisible(false);
            axisList[5]->setVisible(false);

            // Zero coordinate stands right on the intersection
            // of the axis, remove these
            auto sampler = axisList[0]->sampler();
            if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
                int k = 0;
                for (auto &sample : sampler->sampleList()) {
                    if (sample.coord == 0.0)
                        sampler->sampleList().removeAt(k);
                    ++k;
                }
            }
            sampler = axisList[3]->sampler();
            if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
                int k = 0;
                for (auto &sample : sampler->sampleList()) {
                    if (sample.coord == 0.0)
                        sampler->sampleList().removeAt(k);
                    ++k;
                }
            }
        }
    }
}


void ChartLinscale::showAxis(AxisKey keys) {
    KSL_PUBLIC(ChartLinscale);
    m->autoChooseAxis = false;
    m->axisKeys = keys;
    m->axisList[0]->setVisible(keys & X_Axis);
    m->axisList[1]->setVisible(keys & BottomAxis);
    m->axisList[2]->setVisible(keys & TopAxis);
    m->axisList[3]->setVisible(keys & Y_Axis);
    m->axisList[4]->setVisible(keys & LeftAxis);
    m->axisList[5]->setVisible(keys & RightAxis);
    if (m->chart)
        emit m->chart->changed(m->chart);
}


void ChartLinscale::autoChooseAxis() {
    KSL_PUBLIC(ChartLinscale);
    m->autoChooseAxis = true;
    if (m->chart)
        emit m->chart->changed(m->chart);
}

KSL_END_NAMESPACE
