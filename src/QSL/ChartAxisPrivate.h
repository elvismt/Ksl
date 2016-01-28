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

#ifndef QSL_CHARTAXISPRIVATE_H
#define QSL_CHARTAXISPRIVATE_H

#include <QSL/ChartAxis.h>
#include <QSL/FigureItemPrivate.h>

QSL_BEGIN_NAMESPACE

class ChartAxisPrivate
    : public FigureItemPrivate
{
public:

    ChartAxisPrivate(ChartAxis *publ, const QString &name,
                     ChartAxis::Position iposition)
        : FigureItemPrivate(publ, name)
        , pen(Qt::black)
        , position(iposition)
        , sampler(new ChartAxisSampler())
        , component(ChartAxis::AllComponents)
    { }

    ~ChartAxisPrivate();


    QPen pen;
    ChartAxis::Position position;
    ChartAxisSampler* sampler;
    ChartAxis::Component component;


    void paintBottom(QPainter *painter);
    void paintLeft(QPainter *painter);
    void paintTop(QPainter *painter);
    void paintRight(QPainter *painter);
};

QSL_END_NAMESPACE

#endif // QSL_CHARTAXISPRIVATE_H
