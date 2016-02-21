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

#ifndef KSL_CHARTAXIS_P_H
#define KSL_CHARTAXIS_P_H

#include <Ksl/ChartAxis.h>
#include <Ksl/ChartItem_p.h>

KSL_BEGIN_NAMESPACE

class ChartAxisPrivate
    : public ChartItemPrivate
{
public:

    ChartAxisPrivate(ChartAxis *publ, const QString &name)
        : ChartItemPrivate(publ, name)
        , sampler(new ChartAxisSampler())
        , pen(Qt::black)
        , brush(Qt::black)
        , selectBrush(QColor(0, 0, 255, 127))
        , components(ChartAxis::Line|ChartAxis::TicksDown|ChartAxis::Title)
        , antialias(true)
        , minTicks(true)
        , smallTick(2)
        , bigTick(6)
    { }

    ~ChartAxisPrivate();


    ChartAxisSampler* sampler;
    QPen pen;
    QBrush brush;
    QBrush selectBrush;
    ChartAxis::Component components;
    bool antialias;
    bool minTicks;
    int smallTick;
    int bigTick;

    Qt::Orientation orient;

    double minCoord;
    double maxCoord;
    double anchor;

    int chartMin;
    int chartMax;
    int chartAnchor;

    void paintHorizontal(QPainter *painter);
    void paintVertical(QPainter *painter);
};

KSL_END_NAMESPACE

#endif // KSL_CHARTAXIS_P_H
