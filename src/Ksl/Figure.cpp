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

#include <Ksl/Figure_p.h>
#include <Ksl/FigureScale.h>
#include <Ksl/FigureItem.h>

KSL_BEGIN_NAMESPACE

Figure::Figure(Ksl::ObjectPrivate *priv,
               const QString &name, QObject *parent)
    : QObject(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(Figure);
    m->name = name;
}

Figure::Figure(const QString &name, QObject *parent)
    : Figure(new FigurePrivate(this), name, parent)
{ }

void Figure::add(FigureScale *scale) {
    KSL_PUBLIC(Figure);
    if (!scale)
        return;
    if (!m->scaleList.contains(scale)) {
        m->scaleList.append(scale);
        scale->setFigure(this);
        emit changed(this);
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

FigureScale* Figure::scale(const QString &name) const {
    KSL_PUBLIC(const Figure);
    for (auto scale : m->scaleList)
        if (scale->name() == name)
            return scale;
    return nullptr;
}

FigureItem* Figure::item(const QString &name) const {
    KSL_PUBLIC(const Figure);
    for (auto scale : m->scaleList) {
        auto item = scale->item(name);
        if (item)
            return item;
    }
    return nullptr;
}

void Figure::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(Figure);

    if (rect.isEmpty() || !painter)
        return;
    painter->save();
    painter->setClipRect(rect);
    if (m->fillBack)
        painter->fillRect(rect, m->backBrush);
    for (auto scale : m->scaleList)
        if (scale->visible())
            scale->paint(rect, painter);
    painter->restore();
}

void Figure::save(const QString &filePath,
                  const QSize &size,
                  const char *format)
{
    if (filePath.isEmpty() || size.isEmpty())
        return;
    QImage image(size, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(QPoint(0,0), size), &painter);
    image.save(filePath, format);
}

void Figure::onAppearenceChange(FigureItem *item) {
    Q_UNUSED(item)
    emit changed(this);
}

void Figure::onDataChange(FigureItem *item)  {
    item->scale()->rescale();
    emit changed(this);
}

void Figure::setBackBrush(const QBrush &brush) {
    KSL_PUBLIC(Figure);
    if (m->backBrush != brush) {
        m->backBrush = brush;
        m->fillBack = true;
        emit changed(this);
    }
}

QString Figure::name() const {
    KSL_PUBLIC(const Figure);
    return m->name;
}

void Figure::setName(const QString &name) {
    KSL_PUBLIC(Figure);
    if (m->name != name) {
        m->name = name;
        emit changed(this);
    }
}

KSL_END_NAMESPACE
