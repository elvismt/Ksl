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

#ifndef KSL_BASEPLOT_H
#define KSL_BASEPLOT_H

#include <Ksl/FigureItem.h>
#include <Ksl/Array.h>

namespace Ksl {

class KSL_EXPORT BasePlot
    : public FigureItem
{
    Q_OBJECT

public:

    enum SymbolEnum {
        Line       = 0x00000001,
        Circles    = 0x00000002,
        Squares    = 0x00000004,
        Triangles  = 0x00000008
    };
    Q_DECLARE_FLAGS(Symbol, SymbolEnum)


    virtual void setStyle(const QString &style);

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

    BasePlot(Ksl::ObjectPrivate *priv, const QString &name,
             QObject *parent);


    void paint(QPainter *painter);

    void paintThumb(const QPoint &pos, QPainter *painter);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(BasePlot::Symbol)

} // namespace Ksl

#endif // KSL_BASEPLOT_H
