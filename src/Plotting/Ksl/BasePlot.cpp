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

#include <Ksl/BasePlot_p.h>
#include <Ksl/FigureScale.h>
#include <QtGui>

namespace Ksl {

BasePlot::BasePlot(Ksl::ObjectPrivate *priv,
                   const QString &name, QObject *parent)
    : FigureItem(priv, name, parent)
{
    KSL_PUBLIC(BasePlot);
    m->hasThumb = true;
}


QRectF BasePlot::dataRect() const {
    KSL_PUBLIC(const BasePlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}


void BasePlot::paint(QPainter *painter) {
    KSL_PUBLIC(BasePlot);
    if (m->pointCount == 0)
        return;

    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(
        QPainter::Antialiasing, m->antialias);

    if (m->symbol == Line)
        m->paintLine(m->scale, painter);
    if (m->symbol == Circles)
        m->paintCircles(m->scale, painter);
    if (m->symbol == (Line|Circles))
        m->paintLineCircles(m->scale, painter);
    if (m->symbol == Squares)
        m->paintSquares(m->scale, painter);
    if (m->symbol == (Line|Squares))
        m->paintLineSquares(m->scale, painter);
}


void BasePlotPrivate::checkRanges() {
    pointCount = qMin(x.size(), y.size());
    if (pointCount == 0)
        return;

    xMin = xMax = x[0];
    yMin = yMax = y[0];
    for (int k=1; k<pointCount; ++k) {
        if (x[k] < xMin) xMin = x[k];
        if (x[k] > xMax) xMax = x[k];
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
}


void BasePlotPrivate::paintLine(FigureScale *scale,
                                QPainter *painter)
{
    QPainterPath path;

    QPoint p1 = scale->map(QPointF(x[0], y[0]));
    path.moveTo(p1);

    for (int k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int d2 = dx*dx + dy*dy;

        if (d2 >= 9) {
            path.lineTo(p2);
            p1 = p2;
        }
    }
    painter->strokePath(path, pen);
}


void BasePlotPrivate::paintCircles(FigureScale *scale,
                                   QPainter *painter)
{
    const float rad = symbolRadius;
    const float twoRad = 2.0 * symbolRadius;

    QPoint p1 = scale->map(QPointF(x[0], y[0]));
    painter->drawEllipse(p1.x() - rad, p1.y() - rad, twoRad, twoRad);

    for (int k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int d2 = dx*dx + dy*dy;

        if (d2 >= 4) {
            painter->drawEllipse(p2.x() - rad, p2.y() - rad, twoRad, twoRad);
            p1 = p2;
        }
    }
}


void BasePlotPrivate::paintLineCircles(FigureScale *scale,
                                       QPainter *painter)
{
    const float rad = symbolRadius;
    const float twoRad = 2.0 * symbolRadius;

    QPoint p1 = scale->map(QPointF(x[0], y[0]));

    for (int k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int d2 = dx*dx + dy*dy;

        if (d2 >= 4) {
            painter->drawLine(p1, p2);
            painter->drawEllipse(p1.x() - rad, p1.y() - rad, twoRad, twoRad);
            p1 = p2;
        }
    }

    p1 = scale->map(QPointF(x[pointCount-1], y[pointCount-1]));
    painter->drawEllipse(p1.x() - rad, p1.y() - rad, twoRad, twoRad);
}


void BasePlotPrivate::paintSquares(FigureScale *scale,
                                   QPainter *painter)
{
    const float edge = symbolRadius - 1.0;
    const float halfEdge = edge / 2.0;

    QPoint p1 = scale->map(QPointF(x[0], y[0]));
    painter->drawRect(p1.x()-halfEdge, p1.y()-halfEdge, edge, edge);

    for (int k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int d2 = dx*dx + dy*dy;

        if (d2 >= 4) {
            painter->drawRect(p2.x()-halfEdge, p2.y()-halfEdge, edge, edge);
        }
    }
}


void BasePlotPrivate::paintLineSquares(FigureScale *scale,
                                       QPainter *painter)
{
    const float edge = symbolRadius - 1.0;
    const float halfEdge = edge / 2.0;

    QPoint p1 = scale->map(QPointF(x[0], y[0]));

    for (int k=1; k<pointCount; ++k) {
        QPoint p2 = scale->map(QPointF(x[k], y[k]));

        int dx = p2.x() - p1.x();
        int dy = p2.y() - p1.y();
        int d2 = dx*dx + dy*dy;

        if (d2 >= 4) {
            painter->drawLine(p1, p2);
            painter->drawRect(p1.x()-halfEdge, p1.y()-halfEdge, edge, edge);
            p1 = p2;
        }
    }
    p1 = scale->map(QPointF(x[pointCount-1], y[pointCount-1]));
    painter->drawEllipse(p1.x()-halfEdge, p1.y()-halfEdge, edge, edge);
}


void BasePlot::paintThumb(const QPoint &pos,
                          QPainter *painter)
{
    KSL_PUBLIC(BasePlot);
    const int rad = 2;
    const int twoRad = 2*rad;
    painter->setPen(m->pen);
    painter->setBrush(m->brush);

    if (m->symbol == Line) {
        painter->drawLine(pos.x()-12, pos.y(), pos.x()+12, pos.y());
    }
    if (m->symbol == Circles) {
        painter->drawEllipse(pos.x()-rad, pos.y()-rad, twoRad, twoRad);
    }
    if (m->symbol == (Line|Circles)) {
        painter->drawLine(pos.x()-12, pos.y(), pos.x()+12, pos.y());
        painter->drawEllipse(pos.x()-rad, pos.y()-rad, twoRad, twoRad);
    }
}


void BasePlot::setStyle(const char *style) {
    KSL_PUBLIC(BasePlot);
    Symbol symbol = Line;
    QPen pen(Qt::black);
    QBrush brush(Qt::red);
    bool antialias = true;
    float width = 1.0;
    int idx = 0;

    // Parse color
    if (style != nullptr && style[idx] != '\0') {
        switch (style[idx]) {
            case 'k': { pen.setColor(Qt::black); brush.setColor(Qt::black); } break;
            case 'w': { pen.setColor(Qt::white); brush.setColor(Qt::white); } break;
            case 'r': { pen.setColor(Qt::red); brush.setColor(Qt::red); } break;
            case 'g': { pen.setColor(Qt::green); brush.setColor(Qt::green); } break;
            case 'b': { pen.setColor(Qt::blue); brush.setColor(Qt::blue); } break;
            case 'y': { pen.setColor(Qt::yellow); brush.setColor(Qt::yellow); } break;
            case 'c': { pen.setColor(Qt::cyan); brush.setColor(Qt::cyan); } break;
            case 'm': { pen.setColor(Qt::magenta); brush.setColor(Qt::magenta); } break;
        }
        idx += 1;
    }

    // Parse symbol
    if (style != nullptr && style[idx] != '\0') {
        switch (style[idx]) {
            case 'o': symbol = Circles; break;
            case 's': symbol = Squares; break;
            case '^': symbol = Triangles; break;
            case '-': {
                symbol = Line;
                if (style[idx+1] != '\0') {
                    switch (style[idx+1]) {
                        case 'o': { symbol |= Circles; idx+=1; } break;
                        case 's': { symbol |= Squares; idx+=1; } break;
                        case '^': { symbol |= Triangles; idx+=1; } break;
                    }
                }
                break;
            }
        }
        idx += 1;
    }

    // Parse fill color
    if (style != nullptr && style[idx] != '\0') {
        switch (style[idx]) {
            case 'k': { brush.setColor(Qt::black); } break;
            case 'w': { brush.setColor(Qt::white); } break;
            case 'r': { brush.setColor(Qt::red); } break;
            case 'g': { brush.setColor(Qt::green); } break;
            case 'b': { brush.setColor(Qt::blue); } break;
            case 'y': { brush.setColor(Qt::yellow); } break;
            case 'c': { brush.setColor(Qt::cyan); } break;
            case 'm': { brush.setColor(Qt::magenta); } break;
        }
        ++idx;
    }

    if (symbol == Line) {
        width = 1.5;
        pen.setWidthF(width);
    }

    m->pen = pen;
    m->brush = brush;
    m->symbol = symbol;
    m->antialias = antialias;
}


QPen BasePlot::pen() const {
    KSL_PUBLIC(const BasePlot);
    return m->pen;
}

QBrush BasePlot::brush() const {
    KSL_PUBLIC(const BasePlot);
    return m->brush;
}

BasePlot::Symbol BasePlot::symbol() const {
    KSL_PUBLIC(const BasePlot);
    return m->symbol;
}

bool BasePlot::antialias() const {
    KSL_PUBLIC(const BasePlot);
    return m->antialias;
}

void BasePlot::setPen(const QPen &pen) {
    KSL_PUBLIC(BasePlot);
    if (m->pen != pen) {
        m->pen = pen;
        emit appearenceChanged(this);
    }
}

void BasePlot::setBrush(const QBrush &brush) {
    KSL_PUBLIC(BasePlot);
    if (m->brush != brush) {
        m->brush = brush;
        emit appearenceChanged(this);
    }
}

void BasePlot::setSymbol(BasePlot::Symbol symbol) {
    KSL_PUBLIC(BasePlot);
    if (m->symbol != symbol) {
        m->symbol = symbol;
        emit appearenceChanged(this);
    }
}

void BasePlot::setAntialias(bool antialias) {
    KSL_PUBLIC(BasePlot);
    if (m->antialias != antialias) {
        m->antialias = antialias;
        emit appearenceChanged(this);
    }
}

} // namespace Ksl
