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

#ifndef KSL_CHART_H
#define KSL_CHART_H

#include <Ksl/object.h>
#include <QObject>
#include <QPainter>

// forward declaration
class KslChartScale;
class KslChartItem;

class KSL_EXPORT KslChart
    : public QObject
    , public KslObject
{
    Q_OBJECT

public:

    KslChart(const QString &name="Ksl", QObject *parent=0);

    QList<KslChartScale*>& scaleList();
    const QList<KslChartScale*>& scaleList() const;
    KslChartScale* scale(const QString &name) const;
    KslChartItem* item(const QString &name) const;

    virtual void add(KslChartScale *scale);
    inline void add(KslChartScale &scale) { add(&scale); }

    virtual void paint(const QRect &rect, QPainter *painter);

public Q_SLOTS:

    virtual void save(const QString &fileName,
                      const QSize &size=QSize(500,350),
                      const char *format="png");

    virtual void onAppearenceChange(KslChartItem *item);
    virtual void onDataChange(KslChartItem *item);


Q_SIGNALS:

    void changed(KslChart *self);

protected:

    KslChart(KslObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , KslObject(priv)
    { }
};

#endif // KSL_CHART_H