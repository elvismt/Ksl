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

#include <Ksl/simpleplot_p.h>
#include <Ksl/chartscale.h>
#include <QPainterPath>

KslSimplePlot::KslSimplePlot(const KslArrayView<double> &x,
                             const KslArrayView<double> &y,
                             const QString &name,
                             const QColor &strokeColor,
                             const QColor &fillColor,
                             ScatterSymbol symbol,
                             QObject *parent)
    : KslChartItem(new KslSimplePlotPrivate(
        this,
        name,
        strokeColor,
        fillColor,
        symbol),
        parent)
{
    KSL_PUBLIC(KslSimplePlot);
    switch (symbol) {
        case Line:
            m->pen.setWidth(2);
            break;
        default:
            break;
    }
    setData(x,y);
}

QRect KslSimplePlot::chartRect() const {
    // KSL_PUBLIC(const KslSimplePlot);
    // TODO
    return QRect();
}

QRectF KslSimplePlot::dataRect() const {
    KSL_PUBLIC(const KslSimplePlot);
    return QRectF(m->xMin, m->yMin,
                  m->width, m->height);
}

void KslSimplePlot::setData(const KslArrayView<double> &x,
                            const KslArrayView<double> &y)
{
    KSL_PUBLIC(KslSimplePlot);
    m->x.mirror(x);
    m->y.mirror(y);
    m->checkRanges();
}

void KslSimplePlot::paint(QPainter *painter) {
    KSL_PUBLIC(KslSimplePlot);

    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    if (m->symbol == Line) {
        m->paintLine(painter);
    }
    if (m->symbol == Circles) {
        m->paintCircles(painter);
    }
}

void KslSimplePlotPrivate::checkRanges() {
    xMin = xMax = x[0];
    yMin = yMax = y[0];

    for (quint32 k=1; k<x.size(); ++k) {
        if (x[k] < xMin) xMin = x[k];
        if (x[k] > xMax) xMax = x[k];
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
    width = xMax - xMin;
    height = yMax - yMin;
}

void KslSimplePlotPrivate::paintLine(QPainter *painter) {
    QPainterPath path;
    path.moveTo(scale->map(QPointF(x[0], y[0])));
    for (quint32 k=1; k<x.size(); ++k) {
        path.lineTo(scale->map(QPointF(x[k], y[k])));
    }
    painter->strokePath(path, pen);
}

void KslSimplePlotPrivate::paintCircles(QPainter *painter) {
    int rad = symbolRadius;
    int twoRad = 2*symbolRadius;
    painter->setPen(pen);
    painter->setBrush(brush);
    for (quint32 k=0; k<x.size(); ++k) {
        QPoint p = scale->map(QPointF(x[k], y[k]));
        painter->drawEllipse(p.x()-rad, p.y()-rad, twoRad, twoRad);
    }
}

// Ksl/simpleplot.cpp