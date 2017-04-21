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
#include <ksl/plot/FigureScale.h>
#include <QBrush>

namespace ksl {
namespace plot {

class FigureScalePrivate: public ksl::ObjectPrivate
{
public:

    FigureScalePrivate(FigureScale *publ)
        : ksl::ObjectPrivate(publ)
        , figure(nullptr)
        , visible(true)
        , backBrush(Qt::white)
        , layoutRect(0.0, 0.0, 1.0, 1.0)
    {}

    Figure *figure;
    bool visible;
    QBrush backBrush;
    QRectF layoutRect;
    QString title;
    QList<FigureItem*> itemList;
};
}}
