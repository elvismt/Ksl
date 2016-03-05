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

#ifndef KSL_LINEPLOT_H
#define KSL_LINEPLOT_H

#include <Ksl/FigureItem.h>

namespace Ksl {

class KSL_EXPORT LinePlot
    : public FigureItem
{
public:

    LinePlot(const QPointF &p1, const QPointF &p2,
             const QPen &pen=QPen(Qt::red),
             const QString &name="line", QObject *parent=0);

    LinePlot(double x1, double y1, double x2, double y2,
             const QPen &pen=QPen(Qt::red),
             const QString &name="line", QObject *parent=0);

    LinePlot(double linear, double angular,
             const QPen &pen=QPen(Qt::red),
             const QString &name="line", QObject *parent=0);

protected:

    virtual void paint(QPainter *painter);
};

} // namespace Ksl

#endif // KSL_LINEPLOT_H
