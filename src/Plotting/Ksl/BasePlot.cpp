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
{ }


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
    const int rad = symbolRadius;
    const int twoRad = 2 * symbolRadius;

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
    const int rad = symbolRadius;
    const int twoRad = 2 * symbolRadius;

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
    const int edge = symbolRadius + 1;
    const int halfEdge = edge / 2;

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
    const int edge = symbolRadius + 1;
    const int halfEdge = edge / 2;

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


void BasePlot::setStyle(const QString &style) {
    KSL_PUBLIC(BasePlot);
    Symbol symbol = Line;
    QPen pen(Qt::blue);
    QBrush brush(Qt::green);
    bool antialias = false;
    int idx = 0;

    // Color
    if (style.size() > idx) {
        switch (style.at(idx).toLatin1()) {
            case 'k': pen.setColor(Qt::black); break;
            case 'w': pen.setColor(Qt::white); break;
            case 'r': pen.setColor(Qt::red); break;
            case 'g': pen.setColor(Qt::green); break;
            case 'b': pen.setColor(Qt::blue); break;
            case 'y': pen.setColor(Qt::yellow); break;
            default: break;
        }
        ++idx;
    }

    // Symbol
    if (style.size() > idx) {
        switch (style.at(idx).toLatin1()) {
            case 'c': symbol = Circles; break;
            case 's': symbol = Squares; break;
            case 't': symbol = Triangles; break;
            case 'l': {
                symbol = Line;
                if (style.size() > idx+1) {
                    QChar s = style.at(idx+1);
                    if (QString("cst").contains(s)) {
                        if (s == 'c') symbol |= Circles;
                        if (s == 's') symbol |= Squares;
                        if (s == 't') symbol |= Triangles;
                        ++idx;
                    }
                }
                break;
            }
            default: break;
        }
        ++idx;
    }

    // Line width
    if (style.size() > idx) {
        bool ok;
        int width = QString(style.at(idx)).toInt(&ok);
        if (ok)
            pen.setWidth(width);
        ++idx;
    }

    // Antialiasing
    if (style.size() > idx) {
        if (style.at(idx) == 'a')
            antialias = true;
    }

    m->pen = pen;
    brush.setColor(pen.color());
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
