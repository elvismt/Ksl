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

#include <Ksl/Object.h>
#include <QObject>
#include <QPainter>

KSL_BEGIN_NAMESPACE

// forward declaration
class ChartScale;
class ChartItem;

class KSL_EXPORT Chart
    : public QObject
    , public Ksl::Object
{
    Q_OBJECT

public:

    Chart(const QString &name="Ksl", QObject *parent=0);

    QString name() const;

    bool showName() const;

    QColor nameColor() const;

    QList<ChartScale*>& scaleList();

    const QList<ChartScale*>& scaleList() const;

    virtual void add(ChartScale *scale);

    inline void add(ChartScale &scale) { add(&scale); }

    virtual void paint(const QRect &rect, QPainter *painter);

    virtual void save(const QString &fileName, const QSize
                      &size=QSize(500,350), const char *format="png");

signals:

    void errorOccured(Chart *self);

    void changed(Chart *self);

public slots:

    void setName(const QString &name);

    void setShowName(bool showName);

    void setNameColor(const QColor &color);

    void onAppearenceChange(ChartItem *item);

    void onDataChange(ChartItem *item);

protected:

    Chart(Ksl::ObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , Ksl::Object(priv)
    { }
};

KSL_END_NAMESPACE

#endif // KSL_CHART_H
