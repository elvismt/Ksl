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

#include <Ksl/ChartView_p.h>

KSL_BEGIN_NAMESPACE

ChartView::ChartView(QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(new ChartViewPrivate(this, nullptr))
{
    setMinimumSize(200,200);
    setAutoFillBackground(false);
}

ChartView::ChartView(Chart *chart, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(new ChartViewPrivate(this, chart))
{
    setMinimumSize(200,200);
    setAutoFillBackground(false);
}

ChartView::ChartView(const QString &title, int width, int height, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(new ChartViewPrivate(this, nullptr))
{
    setWindowTitle(title);
    resize(width,height);
    setMinimumSize(200,200);
    setAutoFillBackground(false);
}

Chart* ChartView::chart() const {
    KSL_PUBLIC(ChartView);
    return m->chart;
}

void ChartView::paintEvent(QPaintEvent *event) {
    KSL_PUBLIC(ChartView);
    Q_UNUSED(event)
    m->painter.begin(this);
    m->chart->paint(rect(), &m->painter);
    m->painter.end();
}

KSL_END_NAMESPACE
