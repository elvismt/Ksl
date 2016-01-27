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

#include <QSL/FigureScalePrivate.h>
#include <QSL/FigureItem.h>

QSL_BEGIN_NAMESPACE

QString FigureScale::name() const {
    QSL_PUBLIC(const FigureScale);
    return m->name;
}


Figure* FigureScale::figure() const {
    QSL_PUBLIC(const FigureScale);
    return m->figure;
}


bool FigureScale::visible() const {
    QSL_PUBLIC(const FigureScale);
    return m->visible;
}


FigureScale::ItemList& FigureScale::itemList() {
    QSL_PUBLIC(FigureScale);
    return m->itemList;
}


const FigureScale::ItemList& FigureScale::itemList() const {
    QSL_PUBLIC(const FigureScale);
    return m->itemList;
}


FigureItem* FigureScale::item(const QString &name) const {
    QSL_PUBLIC(const FigureScale);

    for (auto &item : m->itemList) {
        if (item->name() == name) {
            return item;
        }
    }
    // not found
    return nullptr;
}


void FigureScale::add(FigureItem *item) {
    QSL_PUBLIC(FigureScale);

    if (m->itemList.contains(item) == false) {
        m->itemList.append(item);
        item->setScale(this);
    }
}


void FigureScale::paint(const QRect &figureRect, QPainter *painter) {
    QSL_PUBLIC(FigureScale);
    Q_UNUSED(figureRect)

    for (auto &item : m->itemList) {
        if (item->visible()) {
            item->paint(painter);
        }
    }
}


void FigureScale::setFigure(Figure *figure) {
    QSL_PUBLIC(FigureScale);

    if (m->figure != figure) {
        m->figure = figure;

        for (auto &item : m->itemList) {
            item->setScale(this);
        }
    }
}

QSL_END_NAMESPACE
