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

#ifndef KSL_SERIESPLOT_H
#define KSL_SERIESPLOT_H

#include <Ksl/ChartItem.h>
#include <Ksl/Array.h>
#include <QPen>
#include <QBrush>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT SeriesPlot
    : public ChartItem
{
    Q_OBJECT

public:

    enum ScatterEnum {
        Line,
        Circles
    };
    Q_DECLARE_FLAGS(
        Scatter,
        ScatterEnum
    )


    SeriesPlot(const Array<double> &vx,
               const Array<double> &vy,
               Scatter scatter=Circles,
               const QColor &stroke=Qt::blue,
               const QColor &fill=Qt::green,
               const QString &name="series",
               QObject *parent=0);

    void setData(const Array<double> &vx,
                 const Array<double> &vy);

    virtual QRect chartRect() const;

    virtual QRectF dataRect() const;

protected:

    virtual void paint(QPainter *painter);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SeriesPlot::Scatter)

KSL_END_NAMESPACE

#endif // KSL_SERIESPLOT_H
