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

#include <Ksl/FeaturePlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

FeaturePlot::FeaturePlot(const QString &name, QObject *parent)
    : FigureItem(new FeaturePlotPrivate(this), name, parent)
{ }


void FeaturePlot::append(const PlotSample &point) {
    KSL_PUBLIC(FeaturePlot);
    if (m->samples.isEmpty()) {
        m->xMin = point.x() - point.xDown();
        m->xMax = point.x() + point.xUp();
        m->yMin = point.y() - point.yDown();
        m->yMax = point.y() + point.yUp();
    }
    else {
        if (point.x() - point.xDown() < m->xMin) m->xMin = point.x() - point.xDown();
        if (point.x() + point.xUp()   > m->xMax) m->xMax = point.x() + point.xUp();
        if (point.y() - point.yDown() < m->yMin) m->yMin = point.y() - point.yDown();
        if (point.y() + point.yUp()   > m->yMax) m->yMax = point.y() + point.yUp();
    }

    m->samples.append(point);
}


QRectF FeaturePlot::dataRect() const {
    KSL_PUBLIC(const FeaturePlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}


void FeaturePlot::paint(QPainter *painter) {
    KSL_PUBLIC(FeaturePlot);

    m->paintErrorsBars(painter);
}


void FeaturePlotPrivate::paintErrorsBars(QPainter *painter) {

    for (auto &sample : samples) {
        QPoint p1 = scale->map(QPointF(sample.x() - sample.xDown(), sample.y() + sample.yUp()));
        QPoint p2 = scale->map(QPointF(sample.x() + sample.xUp(), sample.y() - sample.yDown()));

        painter->setPen(sample.pen());
        painter->setBrush(sample.brush());
        painter->drawEllipse(p1.x(), p1.y(), p2.x() - p1.x(), p2.y() - p1.y());
    }
}

} // namespace Ksl
