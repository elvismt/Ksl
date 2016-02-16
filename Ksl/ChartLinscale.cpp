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

KSL_BEGIN_NAMESPACE

ChartLinscale::ChartLinscale(const QString &name)
    : ChartScale(new ChartLinscalePrivate(this, name))
{ }


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
        return;
    }

    auto iter = m->itemList.begin();
    auto end = m->itemList.end();
    auto item = *iter++;
    auto itemRect = item->dataRect();

    m->xMin = itemRect.left();
    m->xMax = itemRect.right();
    m->yMin = itemRect.top();
    m->yMax = itemRect.bottom();

    while (iter != end) {
        item = *iter++;
        itemRect = item->dataRect();
        if (itemRect.left() < m->xMin) m->xMin = itemRect.left();
        if (itemRect.right() > m->xMax) m->xMax = itemRect.right();
        if (itemRect.top() < m->yMin) m->yMin = itemRect.top();
        if (itemRect.bottom() > m->yMax) m->yMax = itemRect.bottom();
    }

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
    m->chartXmin = rect.left() + m->xLowBound;
    m->chartXmax = rect.right() - m->xUpBound;
    m->chartWidth = m->chartXmax - m->chartXmin;
    m->chartYmin = rect.top() + m->yLowBound;
    m->chartYmax = rect.bottom() - m->yUpBound;
    m->chartHeight = m->chartYmax - m->chartYmin;

    painter->setPen(QPen(Qt::black));
    painter->drawRect(chartRect());

    painter->save();
    painter->setClipRect(chartRect());
    ChartScale::paint(rect, painter);
    painter->restore();
}

KSL_END_NAMESPACE
