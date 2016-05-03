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

#include <Ksl/PolyPlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

PolyPlot::PolyPlot(const Array<1> &a,
                   double xMin, double xMax,
                   const char *style,
                   const QString &name,
                   QObject *parent)
    : BasePlot(new PolyPlotPrivate(this), name, parent)
{
    KSL_PUBLIC(PolyPlot);
    m->a = copy(a);
    m->xMin = xMin;
    m->xMax = xMax;
    setStyle(style);
    m->updateData();
}


void PolyPlot::setParametes(const Array<1> &a) {
    KSL_PUBLIC(PolyPlot);
    m->a = copy(a);
    m->updateData();
    emit appearenceChanged(this);
}


void PolyPlot::setLimits(double xMin, double xMax) {
    KSL_PUBLIC(PolyPlot);
    m->xMin = xMin;
    m->xMax = xMax;
    m->updateData();
    emit appearenceChanged(this);
}


void PolyPlotPrivate::updateData() {
    if (a.size() == 0 || xMin >= xMax)
        return;

    // create arrays
    double dx = (xMax-xMin)/pointCount;
    x = linspace(xMin, xMax, dx);
    y = zeros(x.size());

    // calculate functional values
    for (int k=0; k<pointCount; ++k) {
        //y[k] = poly(a, x[k]);
    }

    // set data ranges
    yMin = y[0];
    yMax = y[0];
    for (int k=1; k<pointCount; ++k) {
        if (y[k] < yMin) yMin = y[k];
        if (y[k] > yMax) yMax = y[k];
    }
}

} // namespace Ksl
