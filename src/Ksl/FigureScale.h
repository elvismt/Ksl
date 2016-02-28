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

#ifndef KSL_FIGURESCALE_H
#define KSL_FIGURESCALE_H

#include <Ksl/Object.h>
#include <QPainter>

namespace Ksl {

// forward
class Figure;
class FigureItem;


class KSL_EXPORT FigureScale
    : public Ksl::Object
{
public:

    Figure* figure() const;

    virtual void add(FigureItem *item);

    QList<FigureItem*>& itemList();

    const QList<FigureItem*>& itemList() const;

    FigureItem* item(const QString &name) const;

    bool contains(FigureItem *item) const;

    QString name() const;

    void setName(const QString &name);

    bool visible() const;

    void setVisible(bool visible);

    virtual QPoint map(const QPointF &point) const = 0;

    virtual QPointF unmap(const QPoint &point) const = 0;

    virtual void rescale();

    virtual QRectF dataRect() const;

    virtual QRect figureRect() const;


protected:

    friend class Figure;

    virtual void setFigure(Figure *figure);

    virtual void paint(const QRect &rect, QPainter *painter);

    FigureScale(Ksl::ObjectPrivate *priv, const QString &name);
};

} // namespace Ksl 

#endif // KSL_FIGURESCALE_H
