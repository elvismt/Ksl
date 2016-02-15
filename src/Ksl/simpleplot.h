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

#ifndef KSL_SIMPLEPLOT_H
#define KSL_SIMPLEPLOT_H

#include <Ksl/chartitem.h>
#include <Ksl/array1d.h>

class KSL_EXPORT KslSimplePlot
    : public KslChartItem
{
    Q_OBJECT

public:

    enum ScatterSymbolEnum {
        Line,
        Circles
    };
    typedef QFlags<ScatterSymbolEnum> ScatterSymbol;


    KslSimplePlot(const KslArray1D<double> &x,
                  const KslArray1D<double> &y,
                  const QString &name,
                  const QColor &strokeColor=Qt::blue,
                  const QColor &fillColor=Qt::red,
                  ScatterSymbol symbol=Line,
                  QObject *parent=0);


    void setData(const KslArray1D<double> &x,
                 const KslArray1D<double> &y);

    virtual QRect chartRect() const;
    virtual QRectF dataRect() const;

protected:

    virtual void paint(QPainter *painter);

    KslSimplePlot(KslObjectPrivate *priv, QObject *parent)
        : KslChartItem(priv, parent)
    { }
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KslSimplePlot::ScatterSymbol)

#endif // KSL_SIMPLEPLOT_H
