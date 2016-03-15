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

#include <Ksl/XYPlot_p.h>
#include <Ksl/FigureScale.h>
#include <QtGui>

namespace Ksl {

XYPlot::XYPlot(Ksl::ObjectPrivate *priv, const QString &name,
               Symbol symbol, QObject *parent)
    : FigureItem(priv, name, parent)
{
    KSL_PUBLIC(XYPlot);
    m->symbol = symbol;
}

XYPlot::XYPlot(const Array<1> &x, const Array<1> &y,
               const QString &name,
               const QPen &pen,
               const QBrush &brush,
               QObject *parent)
    : XYPlot(new XYPlotPrivate(this), name, Line, parent)
{
    KSL_PUBLIC(XYPlot);
    m->pen = pen;
    m->brush = brush;
    setData(x, y);
}

XYPlot::XYPlot(const Array<1> &x, const Array<1> &y,
               XYPlot::Symbol symbol,
               const QString &name,
               const QPen &pen,
               const QBrush &brush,
               QObject *parent)
    : XYPlot(new XYPlotPrivate(this), name, symbol, parent)
{
    KSL_PUBLIC(XYPlot);
    m->pen = pen;
    m->brush = brush;
    setData(x, y);
}

void XYPlot::setData(const Array<1> &x, const Array<1> &y) {
    KSL_PUBLIC(XYPlot);
    m->x = x;
    m->y = y;
    m->checkRanges();
    emit dataChanged(this);
}

QRectF XYPlot::dataRect() const {
    KSL_PUBLIC(const XYPlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}

void XYPlot::paint(QPainter *painter) {
    KSL_PUBLIC(XYPlot);
    if (m->pointCount == 0)
        return;

    painter->setRenderHint(
        QPainter::Antialiasing, m->antialias);

    if (m->symbol == Line)
        m->paintLine(painter);
    else if (m->symbol == Circles)
        m->paintCircles(painter);
    else if (m->symbol == (Line|Circles))
        m->paintLineCircles(painter);
    else if (m->symbol == Squares)
        m->paintSquares(painter);
    else if (m->symbol == (Line|Squares))
        m->paintLineSquares(painter);
    else if (m->symbol == (AreaUnder))
        m->paintAreaUnder(painter);
}

void XYPlotPrivate::checkRanges() {
    pointCount = qMin(x.size(), y.size());
    if (pointCount == 0)
        return;

    xMin = xMax = x[0];
    yMin = yMax = y[0];
    for (size_t k=1; k<pointCount; ++k) {
        if (x[k] < xMin) xMin = x[k];
        if (x[k] > xMax) xMax = x[k];
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
}

void XYPlotPrivate::paintLine(QPainter *painter) {
    painter->setPen(pen);
    QPoint p1 = scale->map(QPointF(x[0],y[0]));
    for (size_t k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k],y[k]));

        // Only draw segments that are at least 3 pixels away
        if ((Math::pow2(p2.x()-p1.x()) + Math::pow2(p2.y()-p1.y())) > 8) {
            painter->drawLine(p1, p2);
            p1 = p2;
        }
    }
}

void XYPlotPrivate::paintCircles(QPainter *painter) {
    int rad = symbolRadius;
    int twoRad = 2*rad;
    painter->setPen(pen);
    painter->setBrush(brush);
    for (size_t k=0; k<pointCount; ++k) {
        QPoint p = scale->map(QPointF(x[k],y[k]));
        painter->drawEllipse(p.x()-rad, p.y()-rad, twoRad, twoRad);
    }
}

void XYPlotPrivate::paintLineCircles(QPainter *painter) {
    QPoint p1, p2;
    int rad = symbolRadius;
    int twoRad = 2*rad - 1;
    painter->setPen(pen);
    painter->setBrush(brush);
    p1 = scale->map(QPointF(x[0],y[0]));
    for (size_t k=1; k<pointCount; ++k) {
        p2 = scale->map(QPointF(x[k],y[k]));
        painter->drawLine(p1, p2);
        painter->drawEllipse(p1.x()-rad, p1.y()-rad, twoRad, twoRad);
        p1 = p2;
    }
    painter->drawEllipse(p2.x()-rad, p2.y()-rad, twoRad, twoRad);
}

void XYPlotPrivate::paintSquares(QPainter *painter) {
    int rad = symbolRadius;
    int twoRad = 2*rad - 1;
    painter->setPen(pen);
    painter->setBrush(brush);
    for (size_t k=0; k<pointCount; ++k) {
        QPoint p = scale->map(QPointF(x[k],y[k]));
        painter->drawRect(p.x()-rad, p.y()-rad, twoRad, twoRad);
    }
}

void XYPlotPrivate::paintLineSquares(QPainter *painter) {
    QPoint p1, p2;
    int rad = symbolRadius;
    int twoRad = 2*rad - 1;
    painter->setPen(pen);
    painter->setBrush(brush);
    p1 = scale->map(QPointF(x[0],y[0]));
    for (size_t k=1; k<pointCount; ++k) {
        p2 = scale->map(QPointF(x[k],y[k]));
        painter->drawLine(p1, p2);
        painter->drawRect(p1.x()-rad, p1.y()-rad, twoRad, twoRad);
        p1 = p2;
    }
    painter->drawRect(p2.x()-rad, p2.y()-rad, twoRad, twoRad);
}

void XYPlotPrivate::paintAreaUnder(QPainter *painter) {
    QPainterPath dataPath;
    QPainterPath boundPath;
    QPoint p1, p2;
    int firstX, y0;

    p1 = scale->map(QPointF(x[0],y[0]));
    firstX = p1.x();
    y0 = scale->map(QPointF(x[0],0.0)).y();
    dataPath.moveTo(p1);

    for (size_t k=1; k<pointCount; ++k) {
        p2 = scale->map(QPointF(x[k],y[k]));

        // Only draw segments that are at least 3 pixels away
        if ((Math::pow2(p2.x()-p1.x()) + Math::pow2(p2.y()-p1.y())) > 8) {
            dataPath.lineTo(p2);
            p1 = p2;
        }
    }

    boundPath.addPath(dataPath);
    boundPath.lineTo(QPoint(p2.x(), y0));
    boundPath.lineTo(QPoint(firstX, y0));
    boundPath.closeSubpath();

    painter->fillPath(boundPath, brush);
    if (pen != Qt::NoPen)
        painter->strokePath(dataPath, pen);
}

QPen XYPlot::pen() const {
    KSL_PUBLIC(const XYPlot);
    return m->pen;
}

QBrush XYPlot::brush() const {
    KSL_PUBLIC(const XYPlot);
    return m->brush;
}

XYPlot::Symbol XYPlot::symbol() const {
    KSL_PUBLIC(const XYPlot);
    return m->symbol;
}

bool XYPlot::antialias() const {
    KSL_PUBLIC(const XYPlot);
    return m->antialias;
}

void XYPlot::setPen(const QPen &pen) {
    KSL_PUBLIC(XYPlot);
    if (m->pen != pen) {
        m->pen = pen;
        emit appearenceChanged(this);
    }
}

void XYPlot::setBrush(const QBrush &brush) {
    KSL_PUBLIC(XYPlot);
    if (m->brush != brush) {
        m->brush = brush;
        emit appearenceChanged(this);
    }
}

void XYPlot::setSymbol(Symbol symbol) {
    KSL_PUBLIC(XYPlot);
    if (m->symbol != symbol) {
        m->symbol = symbol;
        emit appearenceChanged(this);
    }
}

void XYPlot::setAntialias(bool antialias) {
    KSL_PUBLIC(XYPlot);
    if (m->antialias != antialias) {
        m->antialias = antialias;
        emit appearenceChanged(this);
    }
}

} // namespace Ksl
