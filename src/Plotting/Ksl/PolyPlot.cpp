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

#include <Ksl/PolyPlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

PolyPlot::PolyPlot(const Array<1> &a, const QColor &color,
                   double xMin, double xMax,
                   const QString &name, QObject *parent)
    : FigureItem(new PolyPlotPrivate(this), name, parent)
{
    KSL_PUBLIC(PolyPlot);

    m->pen.setColor(color);
    m->a = copy(a);
    m->xMin = xMin;
    m->xMax = xMax;
}


void PolyPlot::setParametes(const Array<1> &a) {
    KSL_PUBLIC(PolyPlot);
    m->a = copy(a);
    m->updateData();
    emit appearenceChanged(this);
}


void PolyPlot::setLimits(double xMin, double xMax) {
    KSL_PUBLIC(PolyPlot);
    m->xMin = xMin;
    m->xMax = xMax;
    m->updateData();
    emit appearenceChanged(this);
}


void PolyPlotPrivate::updateData() {
    if (a.size() == 0 || xMin >= xMax)
        return;

    // create arrays
    x = linspace(xMin, xMax, (xMax-xMin)/pointCount);
    y = samesize(x);

    // calculate functional values
    for (uint32_t k=0; k<pointCount; ++k) {
        y[k] = poly(a, x[k]);
    }

    // set data ranges
    xMin = xMin;
    xMax = xMax;
    yMin = y[0];
    yMax = y[0];
    for (uint32_t k=1; k<pointCount; ++k) {
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
}


QPen PolyPlot::pen() const {
    KSL_PUBLIC(const PolyPlot);
    return m->pen;
}


void PolyPlot::setPen(const QPen &pen) {
    KSL_PUBLIC(PolyPlot);
    m->pen = pen;
}


QRectF PolyPlot::dataRect() const {
    KSL_PUBLIC(const PolyPlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}


void PolyPlot::paint(QPainter *painter) {
    KSL_PUBLIC(PolyPlot);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    painter->setPen(m->pen);

    QPoint p1 = m->scale->map(QPointF(m->x[0], m->y[0]));
    for (uint32_t k=1; k<m->pointCount; ++k) {
        QPoint p2 = m->scale->map(QPointF(m->x[k], m->y[k]));
        painter->drawLine(p1, p2);
        p1 = p2;
    }
}

} // namespace Ksl
