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
#include <ksl/plot/FigureItem.h>
#include <QVector>

namespace ksl {
namespace plot {

class Series: public FigureItem
{
    Q_OBJECT

public:

    enum SymbolEnum {
        Line           = 0x00000001,
        Big            = 0x00000002,
        Circles        = 0x00000004,
        SmallCircles   = Circles,
        BigCircles     = Circles|Big,
        Squares        = 0x00000008,
        SmallSquares   = Squares,
        BigSquares     = Squares|Big
    };
    Q_DECLARE_FLAGS(Symbol,SymbolEnum)

    Series(const QVector<double> &x, const QVector<double> &y,
           const char *style="bOg", QObject *parent=nullptr);

    void setData(const double *x, const double *y, int64_t pointCount);

    void setData(const QVector<double> &x, const QVector<double> &y) {
        setData(x.data(), y.data(), qMin(x.size(), y.size()));
    }

    void setStyle(const char *style);

    virtual QRect figureRect() const override;

    virtual QRectF dataRect() const override;


protected:

    Series(ksl::ObjectPrivate *priv, QObject *parent=nullptr);

    virtual void paint(QPainter *painter) override;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Series::Symbol)
}}
