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

#ifndef KSL_CHARTLINEARSCALE_H
#define KSL_CHARTLINEARSCALE_H

#include <Ksl/chartscale.h>

class KSL_EXPORT KslChartLinearScale
    : public KslChartScale
{
public:

    KslChartLinearScale(const QString &name="scale");

    virtual QPoint map(const QPointF &p) const;
    virtual QPointF unmap(const QPoint &p) const;
    virtual void rescale();
    
    virtual QRect chartRect() const;
    virtual QRectF dataRect() const;


protected:

    virtual void paint(const QRect &rect, QPainter *painter);

    KslChartLinearScale(KslObjectPrivate *priv)
        : KslChartScale(priv)
    { }
};

#endif // KSL_CHARTLINEARSCALE_H