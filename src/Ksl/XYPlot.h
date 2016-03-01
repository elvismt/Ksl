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

#ifndef KSL_XYPLOT_H
#define KSL_XYPLOT_H

#include <Ksl/Array.h>
#include <Ksl/FigureItem.h>
#include <QPen>
#include <QBrush>

namespace Ksl {

class KSL_EXPORT XYPlot
    : public FigureItem
{
    Q_OBJECT

public:

    enum SymbolEnum {
        Line         = 0x00000001,
        Circles      = 0x00000002,
        Squares      = 0x00000004,
        AreaUnder    = 0x00000008
    };
    Q_DECLARE_FLAGS(
        Symbol,
        SymbolEnum
    )



    XYPlot(const Array<1> &x, const Array<1> &y,
           const QString &name="plot",
           const QColor &stroke=Qt::blue,
           const QColor &fill=Qt::green,
           QObject *parent=0);

    XYPlot(const Array<1> &x, const Array<1> &y,
           Symbol symbol,
           const QString &name="plot",
           const QColor &stroke=Qt::blue,
           const QColor &fill=Qt::green,
           QObject *parent=0);


    virtual void setData(const Array<1> &x, const Array<1> &y);

    virtual QRectF dataRect() const;

    QPen pen() const;

    QBrush brush() const;

    Symbol symbol() const;

    bool antialias() const;


public slots:

    void setPen(const QPen &pen);

    void setBrush(const QBrush &brush);

    void setSymbol(Symbol symbol);

    void setAntialias(bool antialias);

protected:

    virtual void paint(QPainter *painter);

    XYPlot(Ksl::ObjectPrivate *priv, const QString &name,
           Symbol symbol, QObject *parent);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(XYPlot::Symbol)

} // namespace Ksl

#endif // KSL_XYPLOT_H
