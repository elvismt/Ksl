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

#include <QSL/FigureItemPrivate.h>
#include <QSL/FigureScale.h>
#include <QSL/Figure.h>

QSL_BEGIN_NAMESPACE

FigureScale* FigureItem::scale() const {
    QSL_PUBLIC(const FigureItem);
    return m->scale;
}


Figure* FigureItem::figure() const {
    QSL_PUBLIC(const FigureItem);
    return m->figure;
}


QString FigureItem::name() const {
    QSL_PUBLIC(const FigureItem);
    return m->name;
}


bool FigureItem::visible() const {
    QSL_PUBLIC(const FigureItem);
    return m->visible;
}

void FigureItem::setName(const QString &name) {
    QSL_PUBLIC(FigureItem);

    if (m->name != name) {
        m->name = name;
        emit appearenceChange(this);
    }
}


void FigureItem::setVisible(bool visible) {
    QSL_PUBLIC(FigureItem);

    if (m->visible != visible) {
        m->visible = visible;
        emit appearenceChange(this);
    }
}


void FigureItem::setScale(FigureScale *scale) {
    QSL_PUBLIC(FigureItem);

    Figure *oldFigure = m->figure;
    Figure *newFigure = scale != nullptr ? scale->figure() : nullptr;

    m->scale = scale;
    m->figure = newFigure;

    if (oldFigure != nullptr) {
        disconnect(this, SIGNAL(appearenceChange(FigureItem*)),
                   oldFigure, SLOT(handleAppearenceChange(FigureItem*)));
        disconnect(this, SIGNAL(dataChange(FigureItem*)),
                   oldFigure, SLOT(handleDataChange(FigureItem*)));
    }

    if (newFigure != nullptr) {
        connect(this, SIGNAL(appearenceChange(FigureItem*)),
                newFigure, SLOT(handleAppearenceChange(FigureItem*)));
        connect(this, SIGNAL(dataChange(FigureItem*)),
                newFigure, SLOT(handleDataChange(FigureItem*)));
    }
}

QSL_END_NAMESPACE
