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

#ifndef KSL_XYAXIS_P_H
#define KSL_XYAXIS_P_H

#include <Ksl/XYAxis.h>
#include <Ksl/FigureItem_p.h>

namespace Ksl {

class XYAxisPrivate
    : public FigureItemPrivate
{
public:

    XYAxisPrivate(XYAxis *publ)
        : FigureItemPrivate(publ)
        , pen(Qt::black)
        , brush(Qt::blue)
        , components(XYAxis::AllComponents)
    { }

    ~XYAxisPrivate();


    void paintHorizontal(QPainter *painter);
    void paintVertical(QPainter *painter);


    QPen pen;
    QBrush brush;
    XYAxis::Component components;
    Qt::Orientation orientation;
    double min, max;
    double anchor;
    XYAxisSampler *sampler;
};

} // namespace Ksl

#endif // KSL_XYAXIS_P_H
