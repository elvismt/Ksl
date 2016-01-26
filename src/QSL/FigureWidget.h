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

#ifndef QSL_FIGUREWIDGET_H
#define QSL_FIGUREWIDGET_H

#include <QSL/Figure.h>
#include <QWidget>

QSL_BEGIN_NAMESPACE

class QSL_API FigureWidget
    : public QWidget
    , public QSL::Object
{
    Q_OBJECT

public:

    FigureWidget(QWidget *parent);

    FigureWidget(const QString &title="QSL",
                 const QSize &size=QSize(500,350),
                 Figure *figure = 0,
                 QWidget *parent = 0);


    Figure* figure() const;


protected:

    virtual void paintEvent(QPaintEvent *event);

    FigureWidget(ObjectPrivate *priv, QWidget *parent)
        : QWidget(parent)
        , QSL::Object(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_FIGUREWIDGET_H
