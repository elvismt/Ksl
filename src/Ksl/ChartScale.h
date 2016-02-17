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

#ifndef KSL_CHARTSCALE_H
#define KSL_CHARTSCALE_H

#include <Ksl/Object.h>
#include <QPainter>

KSL_BEGIN_NAMESPACE

// forward declarations
class Chart;
class ChartItem;


class KSL_EXPORT ChartScale
    : public Ksl::Object
{
public:

    Chart* chart() const;

    QString name() const;

    bool visible() const;

    QList<ChartItem*>& itemList();

    const QList<ChartItem*>& itemList() const;

    virtual void add(ChartItem *item);

    inline void add(ChartItem &item) { add(&item); }

    virtual QPoint map(const QPointF &p) const = 0;

    virtual QPointF unmap(const QPoint &p) const = 0;

    virtual QRect chartRect() const = 0;

    virtual QRectF dataRect() const = 0;

    virtual void rescale() = 0;


protected:

    friend class Chart;

    virtual void setChart(Chart *chart);

    virtual void paint(const QRect &rect, QPainter *painter);

    ChartScale(Ksl::ObjectPrivate *priv)
        : Ksl::Object(priv)
    { }
};

KSL_END_NAMESPACE

#endif // KSL_CHARTSCALE_H
