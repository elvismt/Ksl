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
#include <Ksl/XYAxis.h>

namespace Ksl {

class KSL_EXPORT XYScale
    : public FigureScale
{
public:


    enum AxisEnum {
        BottomAxis   = 0x00000001,
        LeftAxis     = 0x00000002,
        TopAxis      = 0x00000004,
        RightAxis    = 0x00000008,
        X_Axis       = 0x00000010,
        Y_Axis       = 0x00000020
    };
    Q_DECLARE_FLAGS(
        Axis,
        AxisEnum
    )

    XYScale(const QString &name="scale");

    XYAxis* axis(Axis axis);

    void showAxis(Axis axis);

    void autoChoseAxis();

    virtual QPoint map(const QPointF &point) const;

    virtual QPointF unmap(const QPoint &point) const;

    virtual void rescale();

    virtual QRectF dataRect() const;

    virtual QRect figureRect() const;

    void setXrange(double xMin, double xMax);

    void setYrange(double yMin, double yMax);

    void setXbound(int xLowBund, int xUpBound);

    void setYbound(int yLowBund, int yUpBound);

protected:

    virtual void paint(const QRect &rect, QPainter *painter);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(XYScale::Axis)

} // namespace Ksl

#endif // KSL_XYSCALE_H
