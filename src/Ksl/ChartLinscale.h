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

#ifndef KSL_CHARTLINSCALE_H
#define KSL_CHARTLINSCALE_H

#include <Ksl/ChartScale.h>
#include <Ksl/ChartAxis.h>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT ChartLinscale
    : public ChartScale
{
public:

    ChartLinscale(const QString &name="scale");

    QHash<QString,ChartAxis*>& axisList();

    const QHash<QString,ChartAxis*>& axisList() const;

    ChartAxis* axis(const QString &name) const;

    void setAxis(const QString &axisSet);

    QPoint map(const QPointF &p) const;

    QPointF unmap(const QPoint &p) const;

    QRect chartRect() const;

    QRectF dataRect() const;

    void rescale();

protected:

    void paint(const QRect &rect, QPainter *painter);

    ChartLinscale(Ksl::ObjectPrivate *priv)
        : ChartScale(priv)
    { }
};

KSL_END_NAMESPACE

#endif // KSL_CHARTLINSCALE_H
