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

#ifndef KSL_CHARTITEM_H
#define KSL_CHARTITEM_H

#include <Ksl/object.h>
#include <QObject>
#include <QPainter>

// forward declaration
class KslChart;
class KslChartScale;

class KSL_EXPORT KslChartItem
    : public QObject
    , public KslObject
{
    Q_OBJECT

public:

    KslChartItem(const QString &name="figure", QObject *parent=0);
    
    QString name() const;
    bool visible() const;

    KslChartScale* scale() const;
    KslChart* chart() const;

    virtual QRect chartRect() const = 0;
    virtual QRectF dataRect() const = 0;


Q_SIGNALS:

    void appearenceChanged(KslChartItem *self);
    void dataChanged(KslChartItem *self);


protected:
    
    friend class KslChartScale;
    
    virtual void setScale(KslChartScale *scale);

    virtual void paint(QPainter *painter) = 0;
    
    KslChartItem(KslObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , KslObject(priv)
    { }
};

#endif // KSL_CHARTITEM_H