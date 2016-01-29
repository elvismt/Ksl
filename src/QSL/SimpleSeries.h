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

#ifndef QSL_SIMPLESERIES_H
#define QSL_SIMPLESERIES_H

#include <QSL/FigureItem.h>
#include <QSL/Array1D.h>

QSL_BEGIN_NAMESPACE

class QSL_API SimpleSeries
    : public FigureItem
{
    Q_OBJECT

public:

    enum EnumSymbol {
       Line        = 0x00000001,
       Circles     = 0x00000002
    };
    typedef QFlags<EnumSymbol> Symbol;


    SimpleSeries(const QString &name,
                 const Array1D<double> &x,
                 const Array1D<double> &y,
                 const QPen &pen=QPen(Qt::blue),
                 const QBrush &brush=QBrush(Qt::red),
                 Symbol symbol=Circles);


    QPen pen() const;

    QBrush brush() const;

    int radius() const;

    Symbol symbol() const;

    virtual QRect figureRect() const;
    virtual QRectF dataRect() const;

    virtual void setData(const Array1D<double> &x,
                         const Array1D<double> &y);


public Q_SLOTS:

    void setPen(const QPen &pen);

    void setBrush(const QBrush &brush);

    void setRadius(int radius);

    void setSymbol(Symbol symbol);


protected:

    virtual void paint(QPainter *painter);

    SimpleSeries(ObjectPrivate *priv, QObject *parent = 0)
        : FigureItem(priv, parent)
    { }
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SimpleSeries::Symbol)

QSL_END_NAMESPACE

#endif // QSL_SIMPLESERIES_H
