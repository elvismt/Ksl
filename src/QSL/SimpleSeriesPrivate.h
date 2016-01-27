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

#ifndef QSL_SIMPLESERIES_PRIVATE_H
#define QSL_SIMPLESERIES_PRIVATE_H

#include <QSL/SimpleSeries.h>
#include <QSL/FigureItemPrivate.h>

QSL_BEGIN_NAMESPACE

class SimpleSeriesPrivate
    : public FigureItemPrivate
{
public:

    SimpleSeriesPrivate(SimpleSeries *publ, const QString &name)
        : FigureItemPrivate(publ, name)
        , pen(Qt::blue)
        , brush(Qt::green)
        , radius(3)
    { }


    QPen pen;
    QBrush brush;
    int radius;

    Array1D<double> xArray;
    Array1D<double> yArray;
    double xMin, xMax;
    double yMin, yMax;


    void checkRanges();
    void drawCircles(QPainter *painter);
};

QSL_END_NAMESPACE

#endif // QSL_SIMPLESERIES_PRIVATE_H
