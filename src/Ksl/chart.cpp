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

#include <Ksl/chart_p.h>
#include <Ksl/chartscale.h>
#include <Ksl/chartitem.h>

KslChart::KslChart(const QString &name, QObject *parent)
    : QObject(parent)
    , KslObject(new KslChartPrivate(this, name))
{ }

QList<KslChartScale*>& KslChart::scaleList() {
    KSL_PUBLIC(KslChart);
    return m->scaleList;
}

const QList<KslChartScale*>& KslChart::scaleList() const {
    KSL_PUBLIC(const KslChart);
    return m->scaleList;
}

KslChartScale* KslChart::scale(const QString &name) const {
    KSL_PUBLIC(const KslChart);

    Q_FOREACH (KslChartScale *scale, m->scaleList) {
        if (scale->name() == name) {
            return scale;
        }
    }
    // not found
    return 0;
}

KslChartItem* KslChart::item(const QString &name) const {
    KSL_PUBLIC(const KslChart);
    
    Q_FOREACH (KslChartScale *scale, m->scaleList) {
        KslChartItem *item = scale->item(name);
        if (item) {
            return item;
        }
    }
    // not found
    return 0;
}

void KslChart::add(KslChartScale *scale) {
    KSL_PUBLIC(KslChart);
    
    if (scale == 0) {
        return;
    }
    if (!m->scaleList.contains(scale)) {
        m->scaleList.append(scale);
        scale->setChart(this);
        Q_EMIT changed(this);
    }
}

void KslChart::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(KslChart);

    painter->save();
    painter->setClipRect(rect);
    painter->fillRect(rect, m->backBrush);

    Q_FOREACH (KslChartScale *scale, m->scaleList) {
        if (scale->visible()) {
            scale->paint(rect, painter);
        }
    }
    painter->restore();
}

void KslChart::save(const QString &fileName, const QSize &size,
                    const char *format)
{
    QImage image(size, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(QPoint(0,0),size), &painter);
    image.save(fileName, format);
}

void KslChart::onAppearenceChange(KslChartItem *item) {
    Q_UNUSED(item)
    Q_EMIT changed(this);
}

void KslChart::onDataChange(KslChartItem *item) {
    item->scale()->rescale();
    Q_EMIT changed(this);
}

// Ksl/chart.cpp