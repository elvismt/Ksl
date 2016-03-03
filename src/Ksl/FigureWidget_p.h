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

#ifndef KSL_FIGUREWIDGET_P_H
#define KSL_FIGUREWIDGET_P_H

#include <Ksl/FigureWidget.h>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <QHash>

namespace Ksl {

class FigureWidgetPrivate
    : public Ksl::ObjectPrivate
{
public:

    struct FigureTableEntry {
        Figure *figure;
        QPoint pos;
        int initRow, endRow;
        int initCol, endCol;
    };


    FigureWidgetPrivate(FigureWidget *publ)
        : Ksl::ObjectPrivate(publ)
        , lastRow(0), lastCol(0)
        , sizeHint(500, 350)
    { }


    int lastRow, lastCol;
    QSize sizeHint;
    QList<FigureTableEntry> figureList;
    QPainter painter;
};

} // namespace Ksl

#endif // KSL_FIGUREWIDGET_P_H
