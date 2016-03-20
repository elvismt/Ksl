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

#ifndef KSL_POLYPLOT_H
#define KSL_POLYPLOT_H

#include <Ksl/FigureItem.h>
#include <Ksl/Functions.h>

namespace Ksl {

class KSL_EXPORT PolyPlot
    : public FigureItem
{
    Q_OBJECT

public:

    PolyPlot(const Array<1> &a, const QColor &color=Qt::red,
             double xMin=-3.0, double xMax=3.0,
             const QString &name="poly", QObject *parent=0);


    virtual QRectF dataRect() const;

    QPen pen() const;


public slots:

    void setParametes(const Array<1> &a);

    void setLimits(double xMin, double xMax);

    void setPen(const QPen &pen);


protected:

    virtual void paint(QPainter *painter);
};

} // namespace Ksl

#endif // KSL_POLYPLOT_H
