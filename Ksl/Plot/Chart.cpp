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

#include <Ksl/Plot/Chart_p.h>

KSL_BEGIN_PLOT_NAMESPACE

Chart::Chart(const QString &name, QObject *parent)
    : QObject(parent)
    , Ksl::Object(new ChartPrivate(this,name))
{ }

QString Chart::name() const {
    KSL_PUBLIC(Chart);
    return m->name;
}

QList<Scale*>& Chart::scaleList() {
    KSL_PUBLIC(Chart);
    return m->scaleList;
}

const QList<Scale*>& Chart::scaleList() const {
    KSL_PUBLIC(const Chart);
    return m->scaleList;
}

void Chart::add(Scale *scale) {
    KSL_PUBLIC(Chart);
    if (!m->scaleList.contains(scale)) {
        m->scaleList.append(scale);
        emit changed(this);
    }
}

void Chart::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(Chart);

    painter->save();
    painter->setClipRect(rect);
    painter->fillRect(rect, m->backBrush);

    painter->restore();
}

void Chart::save(const QString &fileName, const QSize &size, const char *format) {
    QImage image(size, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(QPoint(0,0),size), &painter);
    image.save(fileName, format);
}

void Chart::onAppearenceChange(Item *item) {

}

void Chart::onDataChange(Item *item) {

}

KSL_END_PLOT_NAMESPACE
