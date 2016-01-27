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

#ifndef QSL_FIGURESCALE_H
#define QSL_FIGURESCALE_H

#include <QSL/Object.h>
#include <QPainter>
#include <QString>
#include <QList>
#include <QRect>

QSL_BEGIN_NAMESPACE

class Figure;
class FigureItem;

class QSL_API FigureScale
    : public QSL::Object
{
public:

    typedef QList<FigureItem*> ItemList;


    QString name() const;

    Figure *figure() const;

    bool visible() const;

    ItemList& itemList();
    const ItemList& itemList() const;

    FigureItem* item(const QString &name) const;


    void add(FigureItem *item);
    inline void add(FigureItem &item) { add(&item); }


    virtual QRect figureRect() const = 0;
    virtual QRectF dataRect() const = 0;

    virtual QPoint map(const QPointF &p) const = 0;
    virtual QPointF unmap(const QPoint &p) const = 0;

    virtual void rescale() = 0;


protected:

    friend class Figure;

    virtual void setFigure(Figure *figure);


    virtual void paint(const QRect &figureRect, QPainter *painter);


    FigureScale(ObjectPrivate *priv)
        : Object(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_FIGURESCALE_H
