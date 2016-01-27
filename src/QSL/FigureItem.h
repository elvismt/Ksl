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

#ifndef QSL_FIGUREITEM_H
#define QSL_FIGUREITEM_H

#include <QSL/Object.h>
#include <QObject>
#include <QPainter>

QSL_BEGIN_NAMESPACE

// forward declaration
class Figure;
class FigureScale;

class QSL_API FigureItem
    : public QObject
    , public QSL::Object
{
    Q_OBJECT

public:


    QString name() const;
    bool visible() const;

    FigureScale* scale() const;
    Figure* figure() const;


    virtual QRect figureRect() const = 0;
    virtual QRectF dataRect() const = 0;


Q_SIGNALS:

    void dataChange(FigureItem *self);
    void appearenceChange(FigureItem *self);


public Q_SLOTS:

    void setName(const QString &name);

    void setVisible(bool visible);

protected:

    friend class FigureScale;

    virtual void paint(QPainter *painter) = 0;

    virtual void setScale(FigureScale *scale);


    FigureItem(ObjectPrivate *priv, QObject *parent = 0)
        : QObject(parent)
        , QSL::Object(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_FIGUREITEM_H
