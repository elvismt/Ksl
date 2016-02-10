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

#include <Ksl/chartscale_p.h>
#include <Ksl/chartitem.h>

KslChartScale::KslChartScale(const QString &name)
    : KslObject(new KslChartScalePrivate(this, name))
{ }

QList<KslChartItem*>& KslChartScale::itemList() {
    KSL_PUBLIC(KslChartScale);
    return m->itemList;
}

const QList<KslChartItem*>& KslChartScale::itemList() const {
    KSL_PUBLIC(const KslChartScale);
    return m->itemList;
}

KslChart* KslChartScale::chart() const {
    KSL_PUBLIC(const KslChartScale);
    return m->chart;
}

KslChartItem* KslChartScale::item(const QString &name) const {
    KSL_PUBLIC(const KslChartScale);

    Q_FOREACH (KslChartItem *item, m->itemList) {
        if (item->name() == name) {
            return item;
        }
    }
    // not found
    return 0;
}

QString KslChartScale::name() const {
    KSL_PUBLIC(const KslChartScale);
    return m->name;
}

bool KslChartScale::visible() const {
    KSL_PUBLIC(const KslChartScale);
    return m->visible;
}

void KslChartScale::add(KslChartItem *item) {
    KSL_PUBLIC(KslChartScale);

    if (item == 0) {
        return;
    }
    if (!m->itemList.contains(item)) {
        m->itemList.append(item);
        item->setScale(this);
        rescale();
    }
}

void KslChartScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(KslChartScale);
    Q_UNUSED(rect)

    Q_FOREACH (KslChartItem *item, m->itemList) {
        if (item->visible()) {
            item->paint(painter);
        }
    }
}

void KslChartScale::setChart(KslChart *chart) {
    KSL_PUBLIC(KslChartScale);

    if (m->chart != chart) {
        m->chart = chart;
        Q_FOREACH (KslChartItem *item, m->itemList) {
            item->setScale(this);
        }
    }
}

// Ksl/chartscale.cpp