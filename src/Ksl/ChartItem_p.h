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

#ifndef KSL_CHARTITEM_P_H
#define KSL_CHARTITEM_P_H

#include <Ksl/ChartItem.h>

KSL_BEGIN_NAMESPACE

class ChartItemPrivate
    : public Ksl::ObjectPrivate
{
public:

    ChartItemPrivate(ChartItem *publ, const QString &iname)
        : Ksl::ObjectPrivate(publ)
        , name(iname)
        , visible(true)
        , chartEngine(nullptr)
        , scale(nullptr)
        , rescalable(true)
    { }

    QString name;
    bool visible;
    ChartEngine *chartEngine;
    ChartScale *scale;
    bool rescalable;
};

KSL_END_NAMESPACE

#endif // KSL_CHARTITEM_P_H
