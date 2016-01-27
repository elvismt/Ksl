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
#include <QPoint>

QSL_BEGIN_NAMESPACE

LinearScale::LinearScale(const QString &name)
    : FigureScale(new LinearScalePrivate(this, name))
{ }


QRect LinearScale::figureRect() const {
    // TODO
    return QRect();
}


QRectF LinearScale::dataRect() const {
    // TODO
    return QRectF();
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
    // TODO
    return QPointF();
}


void LinearScale::setFigure(Figure *figure) {

}


void LinearScale::paint(const QRect &figureRect, QPainter *painter) {

}

QSL_END_NAMESPACE
