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

#include <Ksl/ChartItem_p.h>
#include <Ksl/ChartScale.h>
#include <Ksl/Chart.h>

KSL_BEGIN_NAMESPACE

Chart* ChartItem::chart() const {
    KSL_PUBLIC(const ChartItem);
    return m->chart;
}

ChartScale* ChartItem::scale() const {
    KSL_PUBLIC(const ChartItem);
    return m->scale;
}

QString ChartItem::name() const {
    KSL_PUBLIC(const ChartItem);
    return m->name;
}

bool ChartItem::visible() const {
    KSL_PUBLIC(const ChartItem);
    return m->visible;
}

void ChartItem::setScale(ChartScale *scale) {
    KSL_PUBLIC(ChartItem);
    Chart *newChart = scale ? scale->chart() : nullptr;
    Chart *oldChart = m->chart;

    m->chart = newChart;
    m->scale = scale;

    if (oldChart) {
        disconnect(this, &ChartItem::appearenceChanged,
                   oldChart, &Chart::onAppearenceChange);
        disconnect(this, &ChartItem::dataChanged,
                   oldChart, &Chart::onDataChange);
    }
    if (newChart) {
        connect(this, &ChartItem::appearenceChanged,
                newChart, &Chart::onAppearenceChange);
        connect(this, &ChartItem::dataChanged,
                newChart, &Chart::onDataChange);
    }
}

KSL_END_NAMESPACE
