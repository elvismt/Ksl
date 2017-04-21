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

#include <ksl/plot/FigureScale_p.h>
#include <QtGui>

namespace ksl {
namespace plot {

FigureScale::FigureScale(ksl::ObjectPrivate *priv)
    : ksl::Object(priv)
{ }

Figure* FigureScale::figure() const {
    KSL_PUBLIC(const FigureScale);
    return m->figure;
}

void FigureScale::addItem(FigureItem *item) {
    KSL_PUBLIC(FigureScale);
    if (item != nullptr) {
        // allow no duplicates
        m->itemList.removeAll(item);
        m->itemList.append(item);
        // TODO
    }
}

QList<FigureItem*>& FigureScale::itemList() {
    KSL_PUBLIC(FigureScale);
    return m->itemList;
}

const QList<FigureItem*>& FigureScale::itemList() const {
    KSL_PUBLIC(const FigureScale);
    return m->itemList;
}

FigureItem* FigureScale::item(const QString &title) const {
    KSL_PUBLIC(FigureScale);
    return m->itemList[0]; // TODO
}

QString FigureScale::title() const {
    KSL_PUBLIC(const FigureScale);
    return m->title;
}

void FigureScale::setTitle(const QString &title) {
    KSL_PUBLIC(FigureScale);
    m->title = title;
}

bool FigureScale::visible() const {
    KSL_PUBLIC(const FigureScale);
    return m->visible;
}

void FigureScale::setVisible(bool visible) {
    KSL_PUBLIC(FigureScale);
    m->visible = visible;
}

QRectF FigureScale::layoutRect() const {
    KSL_PUBLIC(const FigureScale);
    return m->layoutRect;
}

void FigureScale::setLayoutRect(const QRectF &rect) {
    KSL_PUBLIC(FigureScale);
    m->layoutRect = rect;
}

void FigureScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(FigureScale);

    painter->save();
    painter->setClipRect(rect);
    if (m->backBrush != Qt::NoBrush) {
        painter->fillRect(rect, m->backBrush);
    }

    // TODO

    painter->restore();
}

void FigureScale::setFigure(Figure *figure) {
    KSL_PUBLIC(FigureScale);
    m->figure = figure;
    // TODO
}
}}
