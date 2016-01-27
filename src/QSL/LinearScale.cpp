/*
 * Copyright (C) 2016  Elvis M.Teixeira
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

#include <QSL/LinearScalePrivate.h>
#include <QSL/FigureItem.h>
#include <QPoint>

QSL_BEGIN_NAMESPACE

LinearScale::LinearScale(const QString &name)
    : FigureScale(new LinearScalePrivate(this, name))
{ }


QRect LinearScale::figureRect() const {
    QSL_PUBLIC(LinearScale);
    return QRect(m->figXmin, m->figYmin,
                 m->figWidth, m->figHeight);
}


QRectF LinearScale::dataRect() const {
    QSL_PUBLIC(LinearScale);
    return QRectF(m->xMin, m->yMin,
                  m->width, m->height);
}


QPoint LinearScale::map(const QPointF &p) const {
    QSL_PUBLIC(LinearScale);
    QPoint ret;
    double g;

    // map X coordinate
    g = (p.x() - m->xMin) / m->width;
    ret.setX(m->figXmin + qRound(g*m->figWidth));
    // map Y coordinate
    g = (p.y() - m->yMin) / m->height;
    ret.setY(m->figYmax - qRound(g*m->figHeight));

    return ret;
}


QPointF LinearScale::unmap(const QPoint &p) const {
    QSL_PUBLIC(LinearScale);
    QPointF ret;
    double g;

    // map X coordinate
    g = (p.x() - m->figXmin) / m->figWidth;
    ret.setX(m->xMin + g*m->width);
    // map Y coordinate
    g = (m->figYmax - p.y()) / m->figHeight;
    ret.setY(m->yMin + g*m->height);

    return ret;
}


void LinearScale::paint(const QRect &figureRect, QPainter *painter) {
    QSL_PUBLIC(LinearScale);

    // use an inner rect in the figure
    m->figXmin = figureRect.left() + m->xLowBound;
    m->figXmax = figureRect.right() - m->xUpBound;
    m->figWidth = m->figXmax - m->figXmin;
    m->figYmin = figureRect.top() + m->yLowBound;
    m->figYmax = figureRect.bottom() - m->yUpBound;
    m->figHeight = m->figYmax - m->figYmin;

    // TODO: remove it when working on axis
    painter->drawRect(this->figureRect());

    // draw user's interesting data items
    painter->save();
    painter->setClipRect(m->figXmin, m->figYmin,
                         m->figWidth, m->figHeight);
    FigureScale::paint(figureRect, painter);
    painter->restore();
}


void LinearScale::rescale() {
    // TODO
}

QSL_END_NAMESPACE
