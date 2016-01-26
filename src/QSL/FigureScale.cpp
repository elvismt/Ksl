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

QSL_BEGIN_NAMESPACE

FigureScale::FigureScale(const QString &name)
    : Object(new FigureScalePrivate(this, name))
{ }


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
    // TODO
}


const FigureScale::ItemList& FigureScale::itemList() const {
    // TODO
}


FigureItem* FigureScale::item(const QString &name) const {
    // TODO
}


void FigureScale::add(FigureItem *item) {
    // TODO
}


void FigureScale::paint(const QRect &figureRect, QPainter *painter) {
    QSL_PUBLIC(FigureScale);

    // TODO
}


void FigureScale::setFigure(Figure *figure) {
    QSL_PUBLIC(FigureScale);

    if (m->figure != figure) {
        m->figure = figure;

        // TODO
    }
}

QSL_END_NAMESPACE
