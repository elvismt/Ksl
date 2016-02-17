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

#include <Ksl/Object.h>
#include <QObject>
#include <QPainter>

KSL_BEGIN_NAMESPACE

// forward declarations
class Chart;
class ChartScale;


class KSL_EXPORT ChartItem
    : public QObject
    , public Ksl::Object
{
    Q_OBJECT

public:

    Chart* chart() const;

    ChartScale* scale() const;

    QString name() const;

    bool visible() const;

    virtual QRect chartRect() const = 0;

    virtual QRectF dataRect() const = 0;

signals:

    void dataChanged(ChartItem *self);

    void appearenceChanged(ChartItem *self);

protected:

    friend class ChartScale;

    virtual void paint(QPainter *painter) = 0;

    virtual void setScale(ChartScale *scale);

    ChartItem(Ksl::ObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , Ksl::Object(priv)
    { }
};

KSL_END_NAMESPACE

#endif // KSL_CHARTITEM_H
