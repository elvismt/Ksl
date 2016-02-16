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

#include <Ksl/ChartScale_p.h>
#include <Ksl/ChartItem.h>

KSL_BEGIN_NAMESPACE

Chart* ChartScale::chart() const {
    KSL_PUBLIC(const ChartScale);
    return m->chart;
}

QString ChartScale::name() const {
    KSL_PUBLIC(const ChartScale);
    return m->name;
}

bool ChartScale::visible() const {
    KSL_PUBLIC(const ChartScale);
    return m->visible;
}

QList<ChartItem*>& ChartScale::itemList() {
    KSL_PUBLIC(ChartScale);
    return m->itemList;
}

const QList<ChartItem*>& ChartScale::itemList() const {
    KSL_PUBLIC(const ChartScale);
    return m->itemList;
}

void ChartScale::add(ChartItem *item) {
    KSL_PUBLIC(ChartScale);
    if (!m->itemList.contains(item)) {
        m->itemList.append(item);
        item->setScale(this);
        rescale();
    }
}

void ChartScale::setChart(Chart *chart) {
    KSL_PUBLIC(ChartScale);
    if (m->chart != chart) {
        m->chart = chart;
        for (auto item : m->itemList) {
            item->setScale(this);
        }
    }
}

void ChartScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(ChartScale);
    Q_UNUSED(rect)
    for (auto item : m->itemList) {
        if (item->visible()) {
            item->paint(painter);
        }
    }
}

KSL_END_NAMESPACE
