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
                   const QString &style, const QString &name,
                   QObject *parent)
    : FigureItem(new LinePlotPrivate(this), name, parent)
{
    KSL_PUBLIC(LinePlot);
    m->p1 = p1;
    m->p2 = p2;
    setStyle(style);
    m->rescalable = true;
}


LinePlot::LinePlot(double x1, double y1, double x2, double y2,
                   const QString &style, const QString &name,
                   QObject *parent)
    : LinePlot(QPointF(x1,y1),QPointF(x2,y2), style, name, parent)
{ }


LinePlot::LinePlot(double linear, double angular,
                   const QString &style, const QString &name,
                   QObject *parent)
    : FigureItem(new LinePlotPrivate(this), name, parent)
{
    KSL_PUBLIC(LinePlot);
    m->a = linear;
    m->b = angular;
    setStyle(style);
    m->useParams = true;
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

    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    painter->setPen(m->pen);
    painter->drawLine(figureP1, figureP2);
}


void LinePlot::setStyle(const QString &style) {
    KSL_PUBLIC(LinePlot);
    QPen pen(Qt::blue);
    pen.setWidthF(1.5);
    bool antialias = true;
    int idx = 0;

    if (style.size() > idx) {
        switch (style.at(idx).toLatin1()) {
            case 'r' : pen.setColor(Qt::red); break;
            case 'g' : pen.setColor(Qt::green); break;
            case 'b' : pen.setColor(Qt::blue); break;
        }
        ++idx;
    }

    if (style.size() > idx) {
        bool ok;
        int width = QString(style.at(idx)).toInt(&ok);
        if (ok)
            pen.setWidth(width);
        ++idx;
    }

    if (style.size() > idx) {
        if (style.at(idx) == 'a')
            antialias = false;
    }

    m->pen = pen;
    m->antialias = antialias;
}

} // namespace Ksl
