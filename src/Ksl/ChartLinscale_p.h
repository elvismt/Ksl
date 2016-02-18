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

#ifndef KSL_CHARTLINSCALE_P_H
#define KSL_CHARTLINSCALE_P_H

#include <Ksl/ChartLinscale.h>
#include <Ksl/ChartScale_p.h>

KSL_BEGIN_NAMESPACE

class ChartLinscalePrivate
    : public ChartScalePrivate
{
public:

    ChartLinscalePrivate(ChartLinscale *publ, const QString &iname)
        : ChartScalePrivate(publ, iname)
        , xLowBound(30), xUpBound(30)
        , yLowBound(30), yUpBound(30)
        , autoChooseAxis(true)
    { }

    ~ChartLinscalePrivate();


    int xLowBound, xUpBound;
    int yLowBound, yUpBound;

    bool autoChooseAxis;
    AxisKey axisKeys;
    QVector<ChartAxis*> axisList;

    int chartXmin, chartXmax;
    int chartYmin, chartYmax;
    int chartWidth, chartHeight;

    double xMin, xMax;
    double yMin, yMax;
    double width, height;

    void setupAxis();
};

KSL_END_NAMESPACE

#endif // KSL_CHARTLINSCALE_P_H
