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

#include <ksl/plot/Chart_p.h>

namespace ksl {
namespace plot {

Chart::Chart(ksl::ObjectPrivate *priv, QWidget *parent)
    : QWidget(parent)
    , Plot(priv)
{}

Chart::Chart(const QString &title, int width,
          int height, QWidget *parent)
    : Chart(new ChartPrivate(this), parent)
{
    KSL_PUBLIC(Chart);

    setWindowTitle(title);
    resize(width, height);

    m->layout = new QVBoxLayout(this);
    setLayout(m->layout);

    m->toolBar = new QToolBar(this);
    m->layout->addWidget(m->toolBar);

    m->figureView = new FigureView(&m->figure, this);
    m->layout->addWidget(m->figureView);
}

FigureView* Chart::figureView() const {
    KSL_PUBLIC(const Chart);
    return m->figureView;
}
}}
