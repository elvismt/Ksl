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
#include <ksl/plot/Figure.h>
#include <QBrush>
#include <QFont>

namespace ksl {
namespace plot {

class FigurePrivate: public ksl::ObjectPrivate
{
public:

    FigurePrivate(Figure *publ)
        : ksl::ObjectPrivate(publ)
        //, backBrush(QColor(230,230,230))
        , backBrush(Qt::white)
        //, backBrush(Qt::black)
        , font("Times", 11)
        , view(nullptr)
    {}

    void updateLayout();

    QBrush backBrush;
    QFont font;
    FigureView* view;
    QString title;
    QList<FigureScale*> scaleList;
    double layoutWidth;
    double layoutHeight;
    bool activeError;
};
}}
