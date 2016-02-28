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

#ifndef KSL_XYAXIS_H
#define KSL_XYAXIS_H

#include <Ksl/FigureItem.h>
#include <Ksl/XYAxisSampler.h>

namespace Ksl {

// forward
class XYScale;

class KSL_EXPORT XYAxis
    : public FigureItem
{
    Q_OBJECT

public:


    enum ComponentEnum {
        NoComponent   = 0x00000000,
        Line          = 0x00000001,
        TicksUp       = 0x00000002,
        TicksDown     = 0x00000004,
        AllComponents = 0xFFFFFFFF
    };
    Q_DECLARE_FLAGS(
        Component,
        ComponentEnum
    )


    XYAxis(Qt::Orientation orientation, const QString &name,
           QObject *parent=0);


    void setPosition(double min, double max, double anchor);

    XYAxisSampler* sampler() const;

    Component visibleComponents() const;

    void showComponents(Component components);

    QRect figureRect() const;

    QRectF dataRect() const;


protected:

    friend class XYScale;

    virtual void paint(QPainter *painter);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(XYAxis::Component)

} // namespace Ksl

#endif // KSL_XYAXIS_H
