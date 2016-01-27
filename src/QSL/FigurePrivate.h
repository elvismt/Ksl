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

#ifndef QSL_FIGURE_PRIVATE_H
#define QSL_FIGURE_PRIVATE_H

#include <QSL/Figure.h>
#include <QBrush>

QSL_BEGIN_NAMESPACE

class FigurePrivate
    : public ObjectPrivate
{
public:

    FigurePrivate(Figure *publ, const QString &iname)
        : ObjectPrivate(publ)
#ifdef Q_OS_LINUX
        , font("Times", 11)
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN
            , font("Times New Roman", 11)
#endif // Q_OS_LINUX
        , name(iname)
        , backBrush(Qt::white)
        , fillBack(true)
        , titlePen(Qt::black)
        , showTitle(true)
    { }


    QFont font;
    QString name;
    QBrush backBrush;
    bool fillBack;
    QPen titlePen;
    bool showTitle;
    Figure::ScaleList scaleList;
};

QSL_END_NAMESPACE

#endif // QSL_FIGURE_PRIVATE_H
