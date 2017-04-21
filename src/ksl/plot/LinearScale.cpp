/*
 * Copyright (C) 2017  Elvis Teixeira
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

#include <ksl/plot/LinearScale_p.h>
#include <ksl/plot/Figure.h>
#include <QtGui>

namespace ksl {
namespace plot {

LinearScale::LinearScale(const QString &title, Figure *figure)
    : FigureScale(new LinearScalePrivate(this))
{
    KSL_PUBLIC(LinearScale);
    m->title = title;
    if (figure != nullptr) {
        figure->addScale(this);
    }
}

void LinearScale::rescale() {
    // TODO
}

QRect LinearScale::figureRect() const {
    KSL_PUBLIC(const LinearScale);
    return QRect(m->xMin, m->yMin,
                 m->width, m->height);
}

QRectF LinearScale::dataRect() const {
    KSL_PUBLIC(const LinearScale);
    return QRectF(m->dataXmin, m->dataYmin,
                  m->dataWidth, m->dataHeight);
}

QPoint LinearScale::map(const QPointF &p) const {
    KSL_PUBLIC(const LinearScale);
    QPoint res;
    double temp;

    temp = (p.x() - m->dataXmin) / m->dataWidth;
    res.setX(m->xMin + temp*m->width);
    temp = (p.y() - m->dataYmin) / m->dataHeight;
    res.setY(m->yMax - temp*m->height);
    return res;
}

QPointF LinearScale::unmap(const QPoint &p) const {
    KSL_PUBLIC(const LinearScale);
    QPointF res;
    double temp;

    temp = (p.x() - m->xMin) / m->width;
    res.setX(m->dataXmin + temp*m->dataWidth);
    temp = (m->yMax - p.y()) / m->height;
    res.setY(m->dataYmin - temp*m->dataHeight);
    return res;
}

void LinearScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(LinearScale);

    // collect figure position and bounds
    m->xMin = rect.left() + m->leftPadding;
    m->xMax = rect.right() - m->rightPadding;
    m->width = m->xMax - m->xMin;
    m->yMin = rect.top() + m->topPadding;
    m->yMax = rect.bottom() - m->bottomPadding;
    m->height = m->yMax - m->yMin;

    // clip to the the region inside the padding
    painter->save();
    painter->setClipRect(figureRect());
    FigureScale::paint(rect, painter);
    painter->restore();
}
}}
