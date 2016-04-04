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

#ifndef KSL_FEATUREPLOT_H
#define KSL_FEATUREPLOT_H

#include <Ksl/FigureItem.h>

namespace Ksl {


class PlotSample
{
public:

    PlotSample(double x, double y,
               double xDown=0.0, double xUp=0.0,
               double yDown=0.0, double yUp=0.0,
               const QPen &pen=QPen(Qt::blue),
               const QBrush &brush=QBrush(Qt::green))
        : m_x(x), m_y(y)
        , m_xDown(xDown), m_xUp(xUp)
        , m_yDown(yDown), m_yUp(yUp)
        , m_pen(pen), m_brush(brush)
    { }


    double x() const { return m_x; }

    double y() const { return m_y; }

    double xDown() const { return m_xDown; }

    double xUp() const { return m_xUp; }

    double yDown() const { return m_yDown; }

    double yUp() const { return m_yUp; }

    QPen pen() const { return m_pen; }

    QBrush brush() const { return m_brush; }


private:

    double m_x, m_y;
    double m_xDown, m_xUp;
    double m_yDown, m_yUp;
    QPen m_pen;
    QBrush m_brush;
};


class KSL_EXPORT FeaturePlot
    : public FigureItem
{
    Q_OBJECT

public:

    enum Style {
        Discs,
        ErrorBars
    };


    FeaturePlot(const QString &name="plot", QObject *parent=0);

    void append(const PlotSample &point);

    QRectF dataRect() const;


protected:

    virtual void paint(QPainter *painter);
};

} // namespace Ksl

#endif // KSL_FEATUREPLOT_H
