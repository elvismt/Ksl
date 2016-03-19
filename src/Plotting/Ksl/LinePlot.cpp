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

#include <Ksl/LinePlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

LinePlot::LinePlot(const QPointF &p1, const QPointF &p2,
                   const QPen &pen, const QString &name,
                   QObject *parent)
    : FigureItem(new LinePlotPrivate(this), name, parent)
{
    KSL_PUBLIC(LinePlot);
    m->p1 = p1;
    m->p2 = p2;
    m->pen = pen;
    m->rescalable = false;
}


LinePlot::LinePlot(double x1, double y1, double x2, double y2,
                   const QPen &pen, const QString &name,
                   QObject *parent)
    : LinePlot(QPointF(x1,y1),QPointF(x2,y2), pen, name, parent)
{ }


LinePlot::LinePlot(double linear, double angular,
                   const QPen &pen, const QString &name,
                   QObject *parent)
    : FigureItem(new LinePlotPrivate(this), name, parent)
{
    KSL_PUBLIC(LinePlot);
    m->useParams = true;
    m->a = linear;
    m->b = angular;
    m->pen = pen;
    m->rescalable = false;
}


void LinePlot::paint(QPainter *painter) {
    KSL_PUBLIC(LinePlot);

    if (m->useParams) {
        const QRectF dataRect = m->scale->dataRect();

        double x = dataRect.left();
        double y = m->a + m->b*x;
        m->p1.setX(x);
        m->p1.setY(y);

        x = dataRect.right();
        y = m->a + m->b*x;
        m->p2.setX(x);
        m->p2.setY(y);
    }

    QPoint figureP1 = m->scale->map(m->p1);
    QPoint figureP2 = m->scale->map(m->p2);

    painter->setPen(m->pen);
    painter->drawLine(figureP1, figureP2);
}

} // namespace Ksl
