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

#include <ksl/plot/FigureItem_p.h>
#include <ksl/plot/FigureScale.h>
#include <ksl/plot/Figure.h>
#include <QtGui>

namespace ksl {
namespace plot {

FigureItem::FigureItem(ksl::ObjectPrivate *priv, QObject *parent)
    : QObject(parent)
    , ksl::Object(priv)
{}

FigureScale* FigureItem::scale() const {
    KSL_PUBLIC(const FigureItem);
    return m->scale;
}


Figure* FigureItem::figure() const {
    KSL_PUBLIC(const FigureItem);
    return m->figure;
}

FigureView* FigureItem::view() const {
    KSL_PUBLIC(const FigureItem);
    return m->view;
}

QString FigureItem::title() const {
    KSL_PUBLIC(const FigureItem);
    return m->title;
}

void FigureItem::setTitle(const QString &title) {
    KSL_PUBLIC(FigureItem);
    if (m->title != title) {
        m->title = title;
        emit appearenceChanged(this);
    }
}

bool FigureItem::visible() const {
    KSL_PUBLIC(const FigureItem);
    return m->visible;
}

void FigureItem::setVisible(bool visible) {
    KSL_PUBLIC(FigureItem);
    if (m->visible != visible) {
        m->visible = visible;
        emit appearenceChanged(this);
    }
}

bool FigureItem::scalable() const {
    KSL_PUBLIC(const FigureItem);
    return m->scalable;
}

void FigureItem::setScalable(bool scalable) {
    KSL_PUBLIC(FigureItem);
    m->scalable = scalable;
}

void FigureItem::setScale(FigureScale *scale) {
    KSL_PUBLIC(FigureItem);
    Figure *oldFigure = m->figure;
    Figure *newFigure = (scale != nullptr) ? scale->figure() : nullptr;

    m->figure = newFigure;
    m->scale = scale;
    m->view = (scale != nullptr) ? scale->view() : nullptr;

    if (oldFigure != nullptr) {
        disconnect(this, SIGNAL(dataChanged(FigureItem*)),
                   oldFigure, SLOT(onDataChange(FigureItem*)));
        disconnect(this, SIGNAL(appearenceChanged(FigureItem*)),
                   oldFigure, SLOT(onAppearenceChange(FigureItem*)));
    }
    if (newFigure != nullptr) {
        connect(this, SIGNAL(dataChanged(FigureItem*)),
                newFigure, SLOT(onDataChange(FigureItem*)));
        connect(this, SIGNAL(appearenceChanged(FigureItem*)),
                newFigure, SLOT(onAppearenceChange(FigureItem*)));
    }
}

void FigureItem::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    // pass
}

void FigureItem::mouseMoveEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    // pass
}

void FigureItem::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    // pass
}

void FigureItem::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    // pass
}
}}
