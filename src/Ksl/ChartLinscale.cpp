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
    m->axisHash["bottom"] = new ChartAxis(Qt::Horizontal, "BottomAxis");
    m->axisHash["top"] = new ChartAxis(Qt::Horizontal, "TopAxis");
    m->axisHash["left"] = new ChartAxis(Qt::Vertical, "LeftAxis");
    m->axisHash["right"] = new ChartAxis(Qt::Vertical, "RightAxis");
    m->axisHash["x"] = new ChartAxis(Qt::Horizontal, "X_Axis");
    m->axisHash["y"] = new ChartAxis(Qt::Vertical, "Y_Axis");
    for (auto axis : m->axisHash) {
        axis->setScale(this);
    }
    setAxis("bottom,left,top,right");
    rescale();
}

ChartLinscalePrivate::~ChartLinscalePrivate() {
    for (auto axis : axisHash) {
        delete axis;
    }
}

QHash<QString,ChartAxis*>& ChartLinscale::axisHash() {
    KSL_PUBLIC(ChartLinscale);
    return m->axisHash;
}

const QHash<QString,ChartAxis *> &ChartLinscale::axisHash() const {
    KSL_PUBLIC(const ChartLinscale);
    return m->axisHash;
}

ChartAxis* ChartLinscale::axis(const QString &name) const {
    KSL_PUBLIC(const ChartLinscale);
    if (m->axisHash.contains(name))
        return m->axisHash[name];
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
    if (!qIsFinite(m->width) || ! qIsFinite(m->height)) {
        if (m->chart) {
            emit m->chart->errorOccured(m->chart);
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

    m->setupAxis();
    for (auto axis : m->axisHash) {
        if (axis->visible()) {
            axis->paint(painter);
        }
    }
}

void ChartLinscalePrivate::setupAxis() {
    ChartAxis *axis;

    axis = axisHash["bottom"];
    axis->setEnds(xMin, xMax, yMin);

    axis = axisHash["top"];
    axis->setEnds(xMin, xMax, yMax);

    axis = axisHash["left"];
    axis->setEnds(yMin, yMax, xMin);

    axis = axisHash["right"];
    axis->setEnds(yMin, yMax, xMax);

    axis = axisHash["x"];
    axis->setEnds(xMin, xMax, 0.0);

    axis = axisHash["y"];
    axis->setEnds(yMin, yMax, 0.0);
}

void ChartLinscale::setAxis(const QString &axisSet) {
    KSL_PUBLIC(ChartLinscale);
    m->axisHash["bottom"]->setVisible(axisSet.contains("bottom", Qt::CaseInsensitive));
    m->axisHash["top"]->setVisible(axisSet.contains("top", Qt::CaseInsensitive));
    m->axisHash["left"]->setVisible(axisSet.contains("left", Qt::CaseInsensitive));
    m->axisHash["right"]->setVisible(axisSet.contains("right", Qt::CaseInsensitive));
    m->axisHash["x"]->setVisible(axisSet.contains("x", Qt::CaseInsensitive));
    m->axisHash["y"]->setVisible(axisSet.contains("y", Qt::CaseInsensitive));
}

KSL_END_NAMESPACE
