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

#include <Ksl/FigureItem_p.h>
#include <Ksl/Figure.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

FigureItem::FigureItem(Ksl::ObjectPrivate *priv,
                       const QString &name, QObject *parent)
    : QObject(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(FigureItem);
    m->name = name;
}

Figure* FigureItem::figure() const {
    KSL_PUBLIC(const FigureItem);
    return m->figure;
}

FigureScale* FigureItem::scale() const {
    KSL_PUBLIC(const FigureItem);
    return m->scale;
}

QString FigureItem::name() const {
    KSL_PUBLIC(const FigureItem);
    return m->name;
}

bool FigureItem::visible() const {
    KSL_PUBLIC(const FigureItem);
    return m->visible;
}

bool FigureItem::rescalable() const {
    KSL_PUBLIC(const FigureItem);
    return m->rescalable;
}

QRectF FigureItem::dataRect() const {
    // pass
    return QRectF();
}

QRect FigureItem::figureRect() const {
    // pass
    return QRect();
}

void FigureItem::setName(const QString &name) {
    KSL_PUBLIC(FigureItem);
    if (m->name != name) {
        m->name = name;
        emit appearenceChanged(this);
    }
}

void FigureItem::setVisible(bool visible) {
    KSL_PUBLIC(FigureItem);
    if (m->visible != visible) {
        m->visible = visible;
        emit appearenceChanged(this);
    }
}

void FigureItem::setScale(FigureScale *scale) {
    KSL_PUBLIC(FigureItem);
    auto oldFigure = m->figure;
    auto newFigure = scale ? scale->figure() : nullptr;

    m->figure = newFigure;
    m->scale = scale;

    if (oldFigure == newFigure)
        return;

    if (oldFigure) {
        disconnect(this, SIGNAL(appearenceChanged(FigureItem*)),
                   oldFigure, SLOT(onAppearenceChange(FigureItem*)));
        disconnect(this, SIGNAL(dataChanged(FigureItem*)),
                   oldFigure, SLOT(onDataChange(FigureItem*)));
    }

    if (newFigure) {
        connect(this, SIGNAL(appearenceChanged(FigureItem*)),
                newFigure, SLOT(onAppearenceChange(FigureItem*)));
        connect(this, SIGNAL(dataChanged(FigureItem*)),
                newFigure, SLOT(onDataChange(FigureItem*)));
    }
}

} // namespace Ksl 
