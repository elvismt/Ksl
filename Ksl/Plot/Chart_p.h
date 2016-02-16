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

#ifndef KSL_PLOT_CHART_P_H
#define KSL_PLOT_CHART_P_H

#include <Ksl/Plot/Chart.h>
#include <QBrush>

KSL_BEGIN_PLOT_NAMESPACE

class ChartPrivate
    : public Ksl::ObjectPrivate
{
public:

    ChartPrivate(Chart *publ, const QString &iname)
        : Ksl::ObjectPrivate(publ)
        , name(iname)
        , backBrush(Qt::white)
    { }

    QString name;
    QBrush backBrush;
    QList<Scale*> scaleList;
};

KSL_END_PLOT_NAMESPACE

#endif // KSL_PLOT_CHART_P_H
