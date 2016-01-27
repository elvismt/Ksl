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

#include <QSL/SimpleSeriesPrivate.h>
#include <QSL/FigureScale.h>

QSL_BEGIN_NAMESPACE

SimpleSeries::SimpleSeries(const QString &name,
                           const Array1D<double> &x,
                           const Array1D<double> &y,
                           const QPen &pen,
                           const QBrush &brush)
    : FigureItem(new SimpleSeriesPrivate(this, name))
{
    QSL_PUBLIC(SimpleSeries);

    m->pen = pen;
    m->brush = brush;
    setData(x, y);
}


QPen SimpleSeries::pen() const {
    QSL_PUBLIC(const SimpleSeries);
    return m->pen;
}


QBrush SimpleSeries::brush() const {
    QSL_PUBLIC(const SimpleSeries);
    return m->brush;
}


int SimpleSeries::radius() const {
    QSL_PUBLIC(const SimpleSeries);
    return m->radius;
}


SimpleSeries::Symbol SimpleSeries::symbol() const {
    QSL_PUBLIC(const SimpleSeries);
    return m->symbol;
}


QRect SimpleSeries::figureRect() const {
    // TODO
    return QRect();
}


QRectF SimpleSeries::dataRect() const {
    QSL_PUBLIC(const SimpleSeries);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}


void SimpleSeries::setData(const Array1D<double> &x,
                           const Array1D<double> &y)
{
    QSL_PUBLIC(SimpleSeries);
    m->xArray.setView(x);
    m->yArray.setView(y);
    m->checkRanges();
    emit dataChange(this);
}


void SimpleSeries::paint(QPainter *painter) {
    QSL_PUBLIC(SimpleSeries);

    if (m->symbol == Circles)
        m->paintCircles(painter);
    if (m->symbol == Line)
        m->paintLine(painter);
}


void SimpleSeriesPrivate::paintCircles(QPainter *painter) {
    int twoRad = 2*radius;
    painter->setPen(pen);
    painter->setBrush(brush);
    for (quint32 k=0; k<xArray.size(); ++k) {
        QPoint p = scale->map(QPointF(xArray[k], yArray[k]));
        painter->drawEllipse(p.x()-radius, p.y()-radius, twoRad, twoRad);
    }
}


void SimpleSeriesPrivate::paintLine(QPainter *painter) {
    QPoint p = scale->map(QPointF(xArray[0], yArray[0]));
    QPainterPath path;
    path.moveTo(p);
    for (quint32 k=1; k<xArray.size(); ++k) {
        p = scale->map(QPointF(xArray[k], yArray[k]));
        path.lineTo(p);
    }
    painter->strokePath(path, pen);
}


void SimpleSeries::setPen(const QPen &pen) {
    QSL_PUBLIC(SimpleSeries);
    if (m->pen != pen) {
        m->pen = pen;
        emit appearenceChange(this);
    }
}


void SimpleSeries::setBrush(const QBrush &brush) {
    QSL_PUBLIC(SimpleSeries);
    if (m->brush != brush) {
        m->brush = brush;
        emit appearenceChange(this);
    }
}


void SimpleSeries::setRadius(int radius) {
    QSL_PUBLIC(SimpleSeries);
    if (m->radius != radius) {
        m->radius = radius;
        emit appearenceChange(this);
    }
}


void SimpleSeries::setSymbol(Symbol symbol) {
    QSL_PUBLIC(SimpleSeries);
    if (m->symbol != symbol) {
        m->symbol = symbol;
        emit appearenceChange(this);
    }
}


void SimpleSeriesPrivate::checkRanges() {
    auto xIter = xArray.begin();
    auto yIter = yArray.begin();
    auto xEnd = xArray.end();

    xMin = xMax = xArray[0];
    yMin = yMax = yArray[0];

    while (xIter != xEnd) {
        if (*xIter < xMin) xMin = *xIter;
        if (*xIter > xMax) xMax = *xIter;
        if (*yIter < yMin) yMin = *yIter;
        if (*yIter > yMax) yMax = *yIter;
        ++xIter;
        ++yIter;
    }
}

QSL_END_NAMESPACE
