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
#include <ksl/Object.h>
#include <QRect>

// Qt forward declarations
QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

namespace ksl {
namespace plot {

// forward declarations
class Figure;
class FigureItem;
class FigureView;

class FigureScale: public ksl::Object
{
public:

    Figure* figure() const;

    FigureView* view() const;

    virtual void addItem(FigureItem *item);

    QList<FigureItem*>& itemList();

    const QList<FigureItem*>& itemList() const;

    FigureItem* item(const QString &title) const;

    virtual void rescale() = 0;

    virtual QRect figureRect() const = 0;

    virtual QRectF dataRect() const = 0;

    virtual QPoint map(const QPointF &p) const = 0;

    virtual QPointF unmap(const QPoint &p) const = 0;

    QString title() const;

    void setTitle(const QString &title);

    bool visible() const;

    void setVisible(bool visible);

    QRectF layoutRect() const;

    void setLayoutRect(const QRectF &rect);


protected:

    friend class Figure;

    FigureScale(ksl::ObjectPrivate *priv);

    virtual void paint(const QRect &rect, QPainter *painter);

    virtual void setFigure(Figure *figure);

    void notifyChange();
};
}}
