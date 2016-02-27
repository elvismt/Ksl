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

#ifndef KSL_CHART_H
#define KSL_CHART_H

#include <Ksl/ChartEngine.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/ChartLabel.h>
#include <Ksl/Canvas.h>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT Chart
    : public Canvas
{
    Q_OBJECT

public:

    Chart(const QString &title="Ksl", int width=500,
          int height=400, QWidget *parent=0);

    ChartEngine* chartEngine() const;

    ChartLinscale* addScale(const QString &name="scale");

    virtual void paint(QPainter *painter, const QRect &rect);

    virtual void mouseMove(const QPoint &pos);
};

KSL_END_NAMESPACE

#endif // KSL_CHART_H
