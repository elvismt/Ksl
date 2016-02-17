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

#ifndef KSL_SERIESPLOT_P_H
#define KSL_SERIESPLOT_P_H

#include <Ksl/SeriesPlot.h>
#include <Ksl/ChartItem_p.h>

KSL_BEGIN_NAMESPACE

class SeriesPlotPrivate
    : public ChartItemPrivate
{
public:

    SeriesPlotPrivate(SeriesPlot *publ, const QString &name)
        : ChartItemPrivate(publ, name)
        , pen(Qt::blue)
        , brush(Qt::green)
        , scatter(SeriesPlot::Circles)
        , scattRadius(3)
        , antialias(true)
    { }

    QPen pen;
    QBrush brush;
    SeriesPlot::Scatter scatter;
    int scattRadius;
    bool antialias;

    Array<1> vx, vy;
    double xMin, xMax;
    double yMin, yMax;
    int ptNum;

    void checkRanges();
    void paintLine(QPainter *painter);
    void paintCircles(QPainter *painter);
};

KSL_END_NAMESPACE

#endif // KSL_SERIESPLOT_P_H
