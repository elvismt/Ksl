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

#ifndef KSL_SIMPLESERIESPLOT_P_H
#define KSL_SIMPLESERIESPLOT_P_H

#include <Ksl/simpleplot.h>
#include <Ksl/chartitem_p.h>

class KslSimplePlotPrivate
    : public KslChartItemPrivate
{
public:

 
    KslSimplePlotPrivate(KslSimplePlot *publ,
                               const QString &iname,
                               const QColor &strokeColor,
                               const QColor &fillColor,
                               KslSimplePlot::ScatterSymbol symbol)
        : KslChartItemPrivate(publ, iname)
        , symbol(symbol)
        , pen(strokeColor)
        , brush(fillColor)
        , symbolRadius(3)
        , antialias(true)
    { }


    KslSimplePlot::ScatterSymbol symbol;
    QPen pen;
    QBrush brush;
    int symbolRadius;
    bool antialias;

    KslArray1D<double> x;
    KslArray1D<double> y;
    double xMin, xMax;
    double yMin, yMax;
    double width, height;

    void checkRanges();
    void paintLine(QPainter *painter);
    void paintCircles(QPainter *painter);
};

#endif // KSL_SIMPLESERIESPLOT_P_H
