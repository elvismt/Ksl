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
#include <ksl/plot/LinearScale.h>
#include <ksl/plot/FigureScale_p.h>

namespace ksl {
namespace plot {

constexpr int64_t MAX_AXIS = 6;

class LinearScalePrivate: public FigureScalePrivate
{
public:

    LinearScalePrivate(LinearScale *publ)
        : FigureScalePrivate(publ)
        , leftPadding(60), rightPadding(20)
        , topPadding(20), bottomPadding(60)
        , horizontalMargin(0.05)
        , verticalMargin(0.05)
    {}

    void positionAxis();

    int leftPadding, rightPadding;
    int topPadding, bottomPadding;

    double horizontalMargin;
    double verticalMargin;

    Axis* axis[MAX_AXIS];

    int xMin, xMax;
    int yMin, yMax;
    int width, height;

    double dataXmin, dataXmax;
    double dataYmin, dataYmax;
    double dataWidth, dataHeight;
};
}}
