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

#ifndef QSL_CHARTAXIS_H
#define QSL_CHARTAXIS_H

#include <QSL/FigureItem.h>

QSL_BEGIN_NAMESPACE

// forward declaration
class LinearScale;

class QSL_API ChartAxis
    : public FigureItem
{
public:

    enum Position {
        Top             = 0x00000001,
        Left            = 0x00000002,
        Bottom          = 0x00000004,
        Right           = 0x00000008,
    };


    ChartAxis(const QString &name, Position position,
              FigureScale *scale, QObject *parent = 0);


    Position position() const;

    virtual QRect figureRect() const;
    virtual QRectF dataRect() const;


protected:

    friend class LinearScale;

    virtual void paint(QPainter *painter);

    ChartAxis(ObjectPrivate *priv, QObject *parent = 0)
        : FigureItem(priv, parent)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_CHARTAXIS_H
