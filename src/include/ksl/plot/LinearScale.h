/*
 * Copyright (C) 2017  Elvis Teixeira
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

#pragma once
#include <ksl/plot/FigureScale.h>
#include <ksl/plot/Axis.h>
#include <QString>

namespace ksl {
namespace plot {

class LinearScale: public FigureScale
{
public:

    enum FrameAxis {
        BottomAxis    = 0,
        LeftAxis      = 1,
        TopAxis       = 2,
        RightAxis     = 3,
        X_Axis        = 4,
        Y_Axis        = 5
    };

    enum FrameStyleEnum {
        BoundAxis     = 0x00000001,
        ZeroAxis      = 0x00000002
    };
    Q_DECLARE_FLAGS(FrameStyle,FrameStyleEnum)


    LinearScale(const QString &title="Ksl",
                Figure *figure=nullptr);

    Axis* axis(FrameAxis axisId) const;

    void setFrameStyle(FrameStyle frameStyle);

    virtual void rescale() override;

    virtual QRect figureRect() const override;

    virtual QRectF dataRect() const override;

    virtual QPoint map(const QPointF &p) const override;

    virtual QPointF unmap(const QPoint &p) const override;

    void setXrange(double min, double max);

    void setYrange(double min, double max);


protected:

    virtual void paint(const QRect &rect, QPainter *painter) override;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(LinearScale::FrameStyle)
}}
