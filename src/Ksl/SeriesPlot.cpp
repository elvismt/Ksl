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

#include <Ksl/SeriesPlot_p.h>
#include <Ksl/ChartScale.h>

KSL_BEGIN_NAMESPACE

SeriesPlot::SeriesPlot(const Array<double> &vx,
                       const Array<double> &vy,
                       Scatter scatter,
                       const QColor &stroke,
                       const QColor &fill,
                       const QString &name,
                       QObject *parent)
    : ChartItem(new SeriesPlotPrivate(this, name), parent)
{
    KSL_PUBLIC(SeriesPlot);
    m->pen = QPen(stroke);
    m->brush = QBrush(fill);
    m->scatter = scatter;
    switch (scatter) {
    case Line:
        m->pen.setWidth(2);
        m->antialias = true;
        break;
    case Circles:
        m->pen.setWidth(1);
        m->antialias = false;
        break;
    }
    setData(vx,vy);
}


void SeriesPlot::setData(const Array<double> &vx, const Array<double> &vy) {
    KSL_PUBLIC(SeriesPlot);
    m->vx = vx;
    m->vy = vy;
    m->checkRanges();
    emit dataChanged(this);
}

QRect SeriesPlot::chartRect() const {
    // TODO
    return QRect();
}

QRectF SeriesPlot::dataRect() const {
    KSL_PUBLIC(const SeriesPlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}

void SeriesPlot::paint(QPainter *painter) {
    KSL_PUBLIC(SeriesPlot);
    if (m->ptNum == 0) {
        return;
    }
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    switch (m->scatter) {
    case Line:
        m->paintLine(painter);
        break;
    case Circles:
        m->paintCircles(painter);
        break;
    }
}

void SeriesPlotPrivate::paintLine(QPainter *painter) {
    QPainterPath path;
    path.moveTo(scale->map(QPointF(vx[0],vy[0])));
    for (int k=1; k<ptNum; ++k) {
        path.lineTo(scale->map(QPointF(vx[k],vy[k])));
    }
    painter->strokePath(path, pen);
}

void SeriesPlotPrivate::paintCircles(QPainter *painter) {
    int rad = scattRadius;
    int twoRad = 2*rad;
    painter->setPen(pen);
    painter->setBrush(brush);
    for (int k=0; k<ptNum; ++k) {
        QPoint p = scale->map(QPointF(vx[k], vy[k]));
        painter->drawEllipse(p.x()-rad, p.y()-rad, twoRad, twoRad);
    }
}

void SeriesPlotPrivate::checkRanges() {
    ptNum = qMin(vx.size(), vy.size());
    if (ptNum == 0) {
        xMin = xMax = 0.0;
        yMin = yMax = 0.0;
        return;
    }
    xMin = xMax = vx[0];
    yMin = yMax = vy[0];
    for (int k=1; k<ptNum; ++k) {
        if (vx[k] < xMin) xMin = vx[k];
        if (vx[k] > xMax) xMax = vx[k];
        if (vy[k] < yMin) yMin = vy[k];
        if (vy[k] > yMax) yMax = vy[k];
    }
}

KSL_END_NAMESPACE
