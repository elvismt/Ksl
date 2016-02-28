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

#include <Ksl/XYScale_p.h>
#include <Ksl/FigureItem.h>

namespace Ksl {

XYScale::XYScale(const QString &name)
    : FigureScale(new XYScalePrivate(this), name)
{ }

QPoint XYScale::map(const QPointF &point) const {
    KSL_PUBLIC(const XYScale);
    QPoint ret;
    double tmp;

    tmp = (point.x() - m->xMin) / m->width;
    ret.setX(m->figXmin + qRound(tmp*m->figWidth));

    tmp = (point.y() - m->yMin) / m->height;
    ret.setY(m->figYmax - qRound(tmp*m->figHeight));

    return ret;
}

QPointF XYScale::unmap(const QPoint &point) const {
    KSL_PUBLIC(const XYScale);
    QPointF ret;
    double tmp;

    tmp = double(point.x() - m->figXmin) / m->figWidth;
    ret.setX(m->xMin + tmp*m->width);

    tmp = double(m->figYmax - point.y()) / m->figHeight;
    ret.setY(m->yMin + tmp*m->height);

    return ret;
}

void XYScale::rescale() {
    KSL_PUBLIC(XYScale);

    if (m->itemList.isEmpty()) {
        setXrange(0.0, 1.0);
        setYrange(0.0, 1.0);
        return;
    }

    auto iter = m->itemList.begin();
    auto end = m->itemList.end();
    FigureItem *item = *iter++;
    auto itemRect = item->dataRect();

    setXrange(itemRect.left(), itemRect.right());
    setYrange(itemRect.top(), itemRect.bottom());

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
    m->width += 2.0 * bound;

    m->height = m->yMax - m->yMin;
    bound = m->height / 20.0;
    m->yMin -= bound;
    m->yMax += bound;
    m->height += 2.0 * bound;
}

QRectF XYScale::dataRect() const {
    KSL_PUBLIC(const XYScale);
    return QRectF(m->xMin, m->yMin,
                  m->width, m->height);
}

QRect XYScale::figureRect() const {
    KSL_PUBLIC(const XYScale);
    return QRect(m->figXmin, m->figYmin,
                 m->figWidth, m->figHeight);
}

void XYScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(XYScale);

    m->figXmin = rect.left() + m->xLowBound;
    m->figXmax = rect.right() - m->xUpBound;
    m->figWidth = m->figXmax - m->figXmin;
    m->figYmin = rect.top() + m->yLowBound;
    m->figYmax = rect.bottom() - m->yUpBound;
    m->figHeight = m->figYmax - m->figYmin;

    painter->save();
    painter->setClipRect(
        m->figXmin, m->figYmin,
        m->figWidth+1, m->figHeight+1);
    FigureScale::paint(rect, painter);
    painter->restore();
}

void XYScale::setXrange(double xMin, double xMax) {
    KSL_PUBLIC(XYScale);
    m->xMin = xMin;
    m->xMax = xMax;
    m->width = xMax - xMin;
}

void XYScale::setYrange(double yMin, double yMax) {
    KSL_PUBLIC(XYScale);
    m->yMin = yMin;
    m->yMax = yMax;
    m->height = yMax - yMin;
}

} // namespace Ksl
