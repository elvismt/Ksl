/*
 * Copyright (C) 2017  Elvis Teixeira
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

#pragma once
#include <ksl/plot/Series.h>
#include <ksl/plot/FigureItem_p.h>
#include <QPen>
#include <QBrush>

namespace ksl {
namespace plot {

class SeriesPrivate: public FigureItemPrivate
{
public:

    SeriesPrivate(Series *publ)
        : FigureItemPrivate(publ)
        , linePen(Qt::blue)
        , symbolPen(Qt::red)
        , symbolBrush(Qt::green)
        , symbol(Series::Line)
        , antialias(true)
        , symbolRadius(2.3)
    {}

    void checkBounds();

    void paintLine(QPainter *painter);

    void paintCircles(QPainter *painter);

    QPen linePen;
    QPen symbolPen;
    QBrush symbolBrush;
    Series::Symbol symbol;
    bool antialias;
    double symbolRadius;
    QVector<double> x, y;

    int64_t pointCount;
    double xMin, xMax;
    double yMin, yMax;
};
}}
