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

#include <Ksl/object.h>
#include <QPainter>

// forward declaration
class KslChart;
class KslChartItem;

class KSL_EXPORT KslChartScale
    : public KslObject
{
public:

    KslChartScale(const QString &name="scale");

    QList<KslChartItem*>& itemList();
    const QList<KslChartItem*>& itemList() const;
    KslChartItem* item(const QString &name) const;
    
    KslChart* chart() const;
    QString name() const;
    bool visible() const;

    virtual void add(KslChartItem *item);
    inline void add(KslChartItem &item) { add(&item); }

    virtual QPoint map(const QPointF &p) const = 0;
    virtual QPointF unmap(const QPoint &p) const = 0;
    virtual void rescale() = 0;

    virtual QRect chartRect() const = 0;
    virtual QRectF dataRect() const = 0;


protected:

    friend class KslChart;

    virtual void setChart(KslChart *chart);

    virtual void paint(const QRect &rect, QPainter *painter);

    KslChartScale(KslObjectPrivate *priv)
        : KslObject(priv)
    { }
};

#endif // KSL_CHARTSCALE_H