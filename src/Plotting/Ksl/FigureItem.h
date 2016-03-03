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

#ifndef KSL_FIGUREITEM_H
#define KSL_FIGUREITEM_H

#include <Ksl/Object.h>
#include <QObject>
#include <QPainter>

namespace Ksl {

// forward
class Figure;
class FigureScale;


class KSL_EXPORT FigureItem
    : public QObject
    , public Ksl::Object
{
    Q_OBJECT

public:

    Figure* figure() const;

    FigureScale* scale() const;

    QString name() const;

    bool visible() const;

    bool rescalable() const;

    virtual QRectF dataRect() const;

    virtual QRect figureRect() const;


public slots:

    void setName(const QString &name);

    void setVisible(bool visible);


signals:

    void appearenceChanged(FigureItem *self);

    void dataChanged(FigureItem *self);


protected:

    friend class FigureScale;

    virtual void setScale(FigureScale *scale);

    virtual void paint(QPainter *painter) = 0;

    FigureItem(Ksl::ObjectPrivate *priv,
               const QString &name, QObject *parent);
};

} // namespace Ksl 

#endif // FIGUREITEM_H
