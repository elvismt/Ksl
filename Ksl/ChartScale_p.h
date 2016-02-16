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

#ifndef KSL_CHARTSCALE_P_H
#define KSL_CHARTSCALE_P_H

#include <Ksl/ChartScale.h>

KSL_BEGIN_NAMESPACE

class ChartScalePrivate
    : public Ksl::ObjectPrivate
{
public:

    ChartScalePrivate(ChartScale *publ, const QString &iname)
        : Ksl::ObjectPrivate(publ)
        , name(iname)
        , visible(true)
        , chart(nullptr)
    { }

    QString name;
    bool visible;
    Chart *chart;
    QList<ChartItem*> itemList;
};

KSL_END_NAMESPACE

#endif // KSL_CHARTSCALE_P_H
