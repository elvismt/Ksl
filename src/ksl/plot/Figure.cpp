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

#include <ksl/plot/Figure_p.h>
#include <ksl/plot/FigureItem.h>
#include <ksl/plot/FigureScale.h>
#include <QPainter>

namespace ksl {
namespace plot {

Figure::Figure(ksl::ObjectPrivate *priv, QObject *parent)
    : QObject(parent)
    , ksl::Object(priv)
{}

Figure::Figure(const QString &title, QObject *parent)
    : Figure(new FigurePrivate(this), parent)
{
    KSL_PUBLIC(Figure);
    m->title = title;
}

FigureView* Figure::view() const {
    KSL_PUBLIC(const Figure);
    return m->view;
}

void Figure::addScale(FigureScale *scale) {
    KSL_PUBLIC(Figure);
    if (scale != nullptr) {
        // allow no duplicates
        m->scaleList.removeAll(scale);
        m->scaleList.append(scale);
        scale->setFigure(this);
        m->updateLayout();
    }
}

QList<FigureScale*>& Figure::scaleList() {
    KSL_PUBLIC(Figure);
    return m->scaleList;
}

const QList<FigureScale*>& Figure::scaleList() const {
    KSL_PUBLIC(const Figure);
    return m->scaleList;
}

FigureScale* Figure::scale(const QString &title) const {
    KSL_PUBLIC(Figure);
    for (auto scale : m->scaleList) {
        if (scale->title() == title) {
            return scale;
        }
    }
    // not found
    return nullptr;
}

FigureItem* Figure::item(const QString &title) const {
    KSL_PUBLIC(Figure);
    for (auto scale : m->scaleList) {
        auto item = scale->item(title);
        if (item != nullptr) {
            return item;
        }
    }
    // not found
    return nullptr;
}

void Figure::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(Figure);

    Q_ASSERT(!rect.isEmpty() && painter!=nullptr);
    m->activeError = false;
    painter->save();
    painter->setClipRect(rect);
    painter->setFont(m->font);
    if (m->backBrush != Qt::NoBrush) {
        painter->fillRect(rect, m->backBrush);
    }
    double cellWidth = rect.width() / m->layoutWidth;
    double cellHeight = rect.height() / m->layoutHeight;
    for (auto scale : m->scaleList) {
        if (m->activeError == true) {
            break;
        }
        if (scale->visible()) {
            QRectF scaleRect = scale->layoutRect();
            QRect targetRect(
                rect.x() + scaleRect.x() * cellWidth,
                rect.y() + scaleRect.y() * cellHeight,
                scaleRect.width() * cellWidth,
                scaleRect.height() * cellHeight
            );
            scale->paint(targetRect, painter);
        }
    }
    if (m->activeError == true) {
        QFont errorFont("Monospace", 10);
        errorFont.setBold(true);
        painter->setFont(errorFont);
        painter->setPen(QPen(Qt::red));
        painter->drawText(30, 40,
            "An error ocurred while painting the figure");
    }
    painter->restore();
}

void Figure::save(const QString fileName, int width,
                  int height, const char *format) {
    QImage image(width, height, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(0, 0, width, height), &painter);
    image.save(fileName, format);
}

void FigurePrivate::updateLayout() {
    layoutWidth = 0.0;
    layoutHeight = 0.0;
    for (auto scale : scaleList) {
        QRectF scaleRect = scale->layoutRect();
        if (scaleRect.right() > layoutWidth) {
            layoutWidth = scaleRect.right();
        }
        if (scaleRect.bottom() > layoutHeight) {
            layoutHeight = scaleRect.bottom();
        }
    }
}

void Figure::notifyError() {
    KSL_PUBLIC(Figure);
    m->activeError = true;
}

void Figure::notifyChange() {
    KSL_PUBLIC(Figure);
    m->updateLayout();
    emit changeOccured();
}

void Figure::onDataChange(FigureItem *item) {
    item->scale()->rescale();
    emit changeOccured();
}

void Figure::onAppearenceChange(FigureItem *item) {
    Q_UNUSED(item)
    emit changeOccured();
}

void Figure::setView(FigureView *view) {
    KSL_PUBLIC(Figure);
    m->view = view;
    for (auto scale : m->scaleList) {
        scale->setFigure(this);
    }
}

void Figure::mousePressEvent(QMouseEvent *event) {
    KSL_PUBLIC(Figure);
    // only propagate to the items to handle
    // TODO improve it
    for (auto scale : m->scaleList) {
        scale->mousePressEvent(event);
    }
}

void Figure::mouseMoveEvent(QMouseEvent *event) {
    KSL_PUBLIC(Figure);
    // only propagate to the items to handle
    // TODO improve it
    for (auto scale : m->scaleList) {
        scale->mouseMoveEvent(event);
    }
}

void Figure::mouseReleaseEvent(QMouseEvent *event) {
    KSL_PUBLIC(Figure);
    // only propagate to the items to handle
    // TODO improve it
    for (auto scale : m->scaleList) {
        scale->mouseReleaseEvent(event);
    }
}

void Figure::mouseDoubleClickEvent(QMouseEvent *event) {
    KSL_PUBLIC(Figure);
    // only propagate to the items to handle
    // TODO improve it
    for (auto scale : m->scaleList) {
        scale->mouseDoubleClickEvent(event);
    }
}
}}
