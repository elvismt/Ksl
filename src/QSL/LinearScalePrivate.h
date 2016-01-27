/*
 * Copyright (C) 2016  Elvis M.Teixeira
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

#ifndef QSL_LINEARSCALE_PRIVATE_H
#define QSL_LINEARSCALE_PRIVATE_H

#include <QSL/LinearScale.h>
#include <QSL/FigureScalePrivate.h>

QSL_BEGIN_NAMESPACE

class LinearScalePrivate
    : public FigureScalePrivate
{
public:

    LinearScalePrivate(LinearScale *publ, const QString &name)
        : FigureScalePrivate(publ, name)
        , xLowBound(20), xUpBound(20)
        , yLowBound(30), yUpBound(20)
    { }


    int xLowBound, xUpBound;
    int yLowBound, yUpBound;

    int figXmin, figXmax;
    int figYmin, figYmax;
    int figWidth, figHeight;

    double xMin, xMax;
    double yMin, yMax;
    double width, height;
};

QSL_END_NAMESPACE

#endif // QSL_LINEARSCALE_PRIVATE_H
