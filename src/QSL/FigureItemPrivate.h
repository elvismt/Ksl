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

#ifndef QSL_FIGUREITEMPRIVATE_H
#define QSL_FIGUREITEMPRIVATE_H

#include <QSL/FigureItem.h>

QSL_BEGIN_NAMESPACE

class FigureItemPrivate
    : public ObjectPrivate
{
public:

    FigureItemPrivate(FigureItem *publ, const QString &iname)
        : ObjectPrivate(publ)
        , name(iname)
        , visible(true)
        , scale(nullptr)
        , figure(nullptr)
    { }


    QString name;
    bool visible;
    FigureScale *scale;
    Figure *figure;
};

QSL_END_NAMESPACE

#endif // QSL_FIGUREITEMPRIVATE_H
