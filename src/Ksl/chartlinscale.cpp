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

#include <Ksl/chartlinscale_p.h>
#include <Ksl/chartitem.h>

KslChartLinscale::KslChartLinscale(const QString &name)
    : KslChartScale(new KslChartLinscalePrivate(this, name))
{ }

QPoint KslChartLinscale::map(const QPointF &p) const {
    KSL_PUBLIC(const KslChartLinscale);
    QPoint ret;
    double tmp;

    tmp = (p.x() - m->xMin) / m->width;
    ret.setX(m->chartXmin + qRound(tmp*m->chartWidth));
    tmp = (p.y() - m->yMin) / m->height;
    ret.setY(m->chartYmax - qRound(tmp*m->chartHeight));
    return ret;
}

QPointF KslChartLinscale::unmap(const QPoint &p) const {
    KSL_PUBLIC(const KslChartLinscale);
    QPointF ret;
    double tmp;

    tmp = (p.x() - m->chartXmin) / m->chartWidth;
    ret.setX(m->xMin + tmp*m->width);
    tmp = (m->chartYmax - p.y()) / m->chartHeight;
    ret.setX(m->yMin + tmp*m->height);
    return ret;
}

QRect KslChartLinscale::chartRect() const {
    KSL_PUBLIC(const KslChartLinscale);
    return QRect(m->chartXmin, m->chartYmin,
                 m->chartWidth, m->chartHeight);
}

QRectF KslChartLinscale::dataRect() const {
    KSL_PUBLIC(const KslChartLinscale);
    return QRectF(m->xMin, m->yMin,
                  m->width, m->height);
}

void KslChartLinscale::rescale() {
    KSL_PUBLIC(KslChartLinscale);

    if (m->itemList.isEmpty()) {
        m->xMin = 0.0;
        m->xMax = 1.0;
        m->yMin = 0.0;
        m->yMax = 1.0;
        return;
    }
    
    QList<KslChartItem*>::iterator iter = m->itemList.begin();
    QList<KslChartItem*>::iterator end = m->itemList.end();
    KslChartItem *item = *iter++;
    QRectF itemRect = item->dataRect();

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

void KslChartLinscale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(KslChartLinscale);

    m->chartXmin = rect.left() + m->lowXbound;
    m->chartXmax = rect.right() - m->upXbound;
    m->chartYmin = rect.top() + m->lowYbound;
    m->chartYmax = rect.bottom() - m->upYbound;
    m->chartWidth = m->chartXmax - m->chartXmin;
    m->chartHeight = m->chartYmax - m->chartYmin;

    painter->setPen(QPen(Qt::black));
    painter->drawRect(chartRect());
    
    painter->save();
    painter->setClipRect(this->chartRect());
    KslChartScale::paint(rect, painter);
    painter->restore();
}

// Ksl/chartlinscale.cpp