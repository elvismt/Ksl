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

#ifndef KSL_XYSCALE_H
#define KSL_XYSCALE_H

#include <Ksl/FigureScale.h>

namespace Ksl {

class KSL_EXPORT XYScale
    : public FigureScale
{
public:

    XYScale(const QString &name="scale");

    virtual QPoint map(const QPointF &point) const;

    virtual QPointF unmap(const QPoint &point) const;

    virtual void rescale();

    virtual QRectF dataRect() const;

    virtual QRect figureRect() const;

    void setXrange(double xMin, double xMax);

    void setYrange(double yMin, double yMax);

protected:

    virtual void paint(const QRect &rect, QPainter *painter);
};

} // namespace Ksl

#endif // KSL_XYSCALE_H
