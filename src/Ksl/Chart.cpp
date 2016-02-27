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

#include <Ksl/Chart_p.h>

KSL_BEGIN_NAMESPACE

Chart::Chart(const QString &title, int width,
             int height, QWidget *parent)
    : Canvas(new ChartPrivate(this, width, height),
             title, width, height, parent)
{
    KSL_PUBLIC(Chart);
    m->chartEngine = new ChartEngine(title);
}


ChartEngine* Chart::chartEngine() const {
    KSL_PUBLIC(const Chart);
    return m->chartEngine;
}


ChartLinscale* Chart::addScale(const QString &name) {
    KSL_PUBLIC(Chart);
    if (m->linearScales.contains(name))
        return m->linearScales[name];
    auto scale = new ChartLinscale(name);
    m->linearScales[name] = scale;
    m->chartEngine->add(scale);
    return scale;
}


void Chart::paint(QPainter *painter, const QRect &rect) {
    KSL_PUBLIC(Chart);
    m->chartEngine->paint(rect, painter);
}

void Chart::mouseMove(const QPoint &pos) {
    KSL_PUBLIC(Chart);
    if (m->linearScales.size() == 1) {
        QPointF pointF = (*m->linearScales.begin())->unmap(pos);
        statusBar()->showMessage(QString("( %1, %2 )")
            .arg(pointF.x(), 3, 'f', 2).arg(pointF.y(), 3, 'f', 2), 2000);
        updateCanvas();
    }
}

KSL_END_NAMESPACE
