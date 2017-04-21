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

void Figure::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(Figure);

    Q_ASSERT(!rect.isEmpty() && painter!=nullptr);
    m->activeError = true;
    painter->save();
    painter->setClipRect(rect);
    painter->setFont(m->font);
    if (m->backBrush != Qt::NoBrush) {
        painter->fillRect(rect, m->backBrush);
    }

    if (m->activeError == true) {
        painter->setPen(QPen(Qt::red));
        painter->drawText(30, 40, "An error ocurred while painting the figure");
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

void Figure::onDataChange(FigureItem *item) {
    // TODO
}

void Figure::onAppearenceChange(FigureItem *item) {
    // TODO
}
}}
