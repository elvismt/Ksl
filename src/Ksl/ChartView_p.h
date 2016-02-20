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

#ifndef KSL_PLOT_CHARTVIEW_P_H
#define KSL_PLOT_CHARTVIEW_P_H

#include <Ksl/ChartView.h>
#include <QPixmap>

KSL_BEGIN_NAMESPACE

class ChartViewPrivate
    : public Ksl::ObjectPrivate
{
public:

    ChartViewPrivate(ChartView *publ, Chart *ichart)
        : Ksl::ObjectPrivate(publ)
        , backPixmap(nullptr)
    {
        if (ichart) {
            chart = ichart;
            ownChart = false;
        }
        else {
            chart = new Chart();
            ownChart = true;
        }
        QObject::connect(chart, &Chart::changed,
                         publ, &ChartView::onChartChange);
    }

    ~ChartViewPrivate();

    QPixmap *backPixmap;
    Chart *chart;
    bool ownChart;
    QPainter painter;
};

KSL_END_NAMESPACE

#endif // KSL_CHARTVIEW_P_H
