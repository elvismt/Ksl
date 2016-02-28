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

#include <Ksl/FigureScale_p.h>
#include <Ksl/FigureItem.h>

namespace Ksl {

FigureScale::FigureScale(Ksl::ObjectPrivate *priv,
                         const QString &name)
    : Ksl::Object(priv)
{
    KSL_PUBLIC(FigureScale);
    m->name = name;
}

Figure* FigureScale::figure() const {
    KSL_PUBLIC(const FigureScale);
    return m->figure;
}

void FigureScale::add(FigureItem *item) {
    KSL_PUBLIC(FigureScale);
    if (!item)
        return;
    if (!m->itemList.contains(item)) {
        m->itemList.append(item);
        item->setScale(this);
        rescale();
        if (m->figure)
            emit item->appearenceChanged(item);
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

FigureItem* FigureScale::item(const QString &name) const {
    KSL_PUBLIC(FigureScale);
    for (auto item : m->itemList)
        if (item->name() == name)
            return item;
    return nullptr;
}

bool FigureScale::contains(FigureItem *item) const {
    KSL_PUBLIC(FigureScale);
    return m->itemList.contains(item);
}

QString FigureScale::name() const {
    KSL_PUBLIC(const FigureScale);
    return m->name;
}

void FigureScale::setName(const QString &name) {
    KSL_PUBLIC(FigureScale);
    m->name = name;
}

bool FigureScale::visible() const {
    KSL_PUBLIC(const FigureScale);
    return m->visible;
}

void FigureScale::setVisible(bool visible) {
    KSL_PUBLIC(FigureScale);
    m->visible = visible;
}

void FigureScale::rescale() {
    // pass
}

QRectF FigureScale::dataRect() const {
    return QRectF();
}

QRect FigureScale::figureRect() const {
    return QRect();
}

void FigureScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(FigureScale);
    Q_UNUSED(rect)
    for (auto item : m->itemList)
        if (item->visible())
            item->paint(painter);
}

void FigureScale::setFigure(Figure *figure) {
    KSL_PUBLIC(FigureScale);
    if (m->figure == figure)
        return;
    m->figure = figure;
    for (auto item : m->itemList)
        item->setScale(this);
}

} // namespace Ksl 
