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

#include <Ksl/chartview_p.h>

KslChartView::KslChartView(QWidget *parent)
    : QWidget(parent)
    , KslObject(new KslChartViewPrivate(this))
{
    KSL_PUBLIC(KslChartView);
    m->chart = new KslChart();
    m->ownChart = true;
    setMinimumSize(200,200);
    setAutoFillBackground(false);
}

KslChartView::KslChartView(const QString &title, int width,
                           int height, QWidget *parent)
    : QWidget(parent)
    , KslObject(new KslChartViewPrivate(this))
{
    KSL_PUBLIC(KslChartView);
    m->chart = new KslChart();
    m->ownChart = true;
    setWindowTitle(title);
    resize(width, height);
    setMinimumSize(200,200);
    setAutoFillBackground(false);
}

KslChart* KslChartView::chart() const {
    KSL_PUBLIC(const KslChartView);
    return m->chart;
}

void KslChartView::paintEvent(QPaintEvent *event) {
    KSL_PUBLIC(KslChartView);
    Q_UNUSED(event)
    m->painter.begin(this);
    m->chart->paint(this->rect(), &m->painter);
    m->painter.end();
}

// Ksl/chartview.cpp