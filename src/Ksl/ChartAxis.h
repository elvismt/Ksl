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

#ifndef KSL_CHARTAXIS_H
#define KSL_CHARTAXIS_H

#include <Ksl/ChartItem.h>
#include <Ksl/ChartAxisSampler.h>

KSL_BEGIN_NAMESPACE

// forward declaration
class ChartLinscale;

class KSL_EXPORT ChartAxis
    : public ChartItem
{
    Q_OBJECT

public:

    enum ComponentEnum {
        NullComponent  = 0x00000000,
        Line           = 0x00000001,
        TicksUp        = 0x00000002,
        TicksDown      = 0x00000004,
        Title          = 0x00000008,
        Arrow          = 0x00000010,
        SelectionRect  = 0x00000020,
        AllComponents  = 0xFFFFFFFF
    };
    Q_DECLARE_FLAGS(
        Component,
        ComponentEnum
    )


    ChartAxis(Qt::Orientation orient,
              const QString &name,
              QObject *parent=0);


    double min() const;

    double max() const;

    void setEnds(double min, double max);

    void setEnds(double min, double max, double anchor);

    ChartAxisSampler* sampler() const;

    virtual QRect chartRect() const;

    virtual QRectF dataRect() const;

    bool selected() const;

    QPen pen() const;

    QBrush brush() const;

    QBrush selectBrush() const;


public slots:

    void setPen(const QPen &pen);

    void setBrush(const QBrush &brush);

    void setSelectBrush(const QBrush &brush);

    void setComponents(Component components);

    void setComponents(const QString &components);

    void setOrientation(Qt::Orientation orient);

    void setShowMinorTicks(bool show=true);

    void setSelected(bool selected);


protected:

    friend class ChartLinscale;

    virtual void paint(QPainter *painter);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ChartAxis::Component)

KSL_END_NAMESPACE

#endif // KSL_CHARTAXIS_H
