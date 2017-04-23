/*
 * Copyright (C) 2017  Elvis Teixeira
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

#include <ksl/plot/Plot_p.h>

namespace ksl {
namespace plot {

Plot::Plot() : Plot(new PlotPrivate(this)) {}

Plot::Plot(ksl::ObjectPrivate *priv) : ksl::Object(priv) {}

Figure* Plot::figure() const {
    KSL_PUBLIC(Plot);
    return &m->figure;
}

FigureScale* Plot::scale(const QString &title) const {
    KSL_PUBLIC(Plot);
    // if there is no scale with this title, create one
    auto scale = m->figure.scale(title);
    if (scale == nullptr) {
        scale = new LinearScale(title, &m->figure);
    }
    return scale;
}

FigureItem* Plot::item(const QString &title) const {
    KSL_PUBLIC(Plot);
    return m->figure.item(title);
}

void Plot::series(const QVector<double> &x, const QVector<double> &y,
                 const char *style, const QString &scaleTitle) {
    auto scale = this->scale(scaleTitle);
    auto series = new Series(x, y, style);
    scale->addItem(series);
}
}}
