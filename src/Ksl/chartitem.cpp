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

#include <Ksl/chartitem_p.h>
#include <Ksl/chart.h>
#include <Ksl/chartscale.h>

KslChartItem::KslChartItem(const QString &name, QObject *parent)
    : QObject(parent)
    , KslObject(new KslChartItemPrivate(this, name))
{ }

QString KslChartItem::name() const {
    KSL_PUBLIC(const KslChartItem);
    return m->name;
}

bool KslChartItem::visible() const {
    KSL_PUBLIC(const KslChartItem);
    return m->visible;
}

KslChartScale* KslChartItem::scale() const {
    KSL_PUBLIC(const KslChartItem);
    return m->scale;
}

KslChart* KslChartItem::chart() const {
    KSL_PUBLIC(const KslChartItem);
    return m->chart;
}

void KslChartItem::setScale(KslChartScale *scale) {
    KSL_PUBLIC(KslChartItem);
    KslChart *oldChart = m->chart;
    KslChart *newChart = scale != 0 ? scale->chart() : 0;

    m->scale = scale;
    m->chart = newChart;

    if (oldChart) {
        disconnect(this, SIGNAL(appearenceChanged(KslChartItem*)),
                   oldChart, SLOT(onAppearenceChange(KslChartItem*)));
        disconnect(this, SIGNAL(dataChanged(KslChartItem*)),
                   oldChart, SLOT(onDataChange(KslChartItem*)));
    }
    if (newChart) {
        connect(this, SIGNAL(appearenceChanged(KslChartItem*)),
                newChart, SLOT(onAppearenceChange(KslChartItem*)));
        connect(this, SIGNAL(dataChanged(KslChartItem*)),
                newChart, SLOT(onDataChange(KslChartItem*)));
    }
}

// Ksl/chartitem.cpp