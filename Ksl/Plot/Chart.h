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

#ifndef KSL_PLOT_CHART_H
#define KSL_PLOT_CHART_H

#include <Ksl/Object.h>
#include <QObject>
#include <QPainter>

KSL_BEGIN_PLOT_NAMESPACE

// forward declaration
class Scale;
class Item;

class KSL_EXPORT Chart
    : public QObject
    , public Ksl::Object
{
    Q_OBJECT

public:

    Chart(const QString &name="Ksl", QObject *parent=0);

    QString name() const;

    QList<Scale*>& scaleList();
    const QList<Scale*>& scaleList() const;

    virtual void add(Scale *scale);
    inline void add(Scale &scale) { add(&scale); }

    virtual void paint(const QRect &rect, QPainter *painter);
    virtual void save(const QString &fileName, const QSize &size=QSize(500,350), const char *format="png");

signals:

    void errorOccured(Chart *self);
    void changed(Chart *self);

public slots:

    void onAppearenceChange(Item *item);
    void onDataChange(Item *item);

protected:

    Chart(Ksl::ObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , Ksl::Object(priv)
    { }
};

KSL_END_PLOT_NAMESPACE

#endif // KSL_PLOT_CHART_H
