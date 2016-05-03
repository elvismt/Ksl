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

#include <Ksl/Plot_p.h>

namespace Ksl {

Plot::Plot(const ArrayView<double> &x, const ArrayView<double> &y,
           const char *style, const QString &name,
           QObject *parent)
    : BasePlot(new PlotPrivate(this), name, parent)
{
    setData(x, y);
    setStyle(style);
}


void Plot::setData(const ArrayView<double> &x, const ArrayView<double> &y) {
    KSL_PUBLIC(Plot);
    m->x = x;
    m->y = y;
    m->checkRanges();
    emit dataChanged(this);
}

} // namespace Ksl
