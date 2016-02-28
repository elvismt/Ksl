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

#ifndef KSL_XYPLOT_P_H
#define KSL_XYPLOT_P_H

#include <Ksl/XYPlot.h>
#include <Ksl/FigureItem_p.h>

namespace Ksl {

class XYPlotPrivate
    : public FigureItemPrivate
{
public:

    XYPlotPrivate(XYPlot *publ)
        : FigureItemPrivate(publ)
        , symbol(XYPlot::Line)
        , antialias(true)
        , symbolRadius(3)
    { }


    void checkRanges();
    void paintLine(QPainter *painter);
    void paintCircles(QPainter *painter);
    void paintSquares(QPainter *painter);


    XYPlot::Symbol symbol;
    bool antialias;
    int symbolRadius;
    QPen pen;
    QBrush brush;

    Array<1> x, y;
    size_t pointCount;
    double xMin, xMax;
    double yMin, yMax;
};

} // namespace Ksl

#endif // KSL_XYPLOT_P_H
