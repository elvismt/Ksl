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

#ifndef KSL_CHARTWINDOW_H
#define KSL_CHARTWINDOW_H

#include <QWidget>
#include <Ksl/FigureWidget.h>
#include <Ksl/XYScale.h>
#include <Ksl/Plot.h>
#include <Ksl/TextPlot.h>
#include <Ksl/LinePlot.h>
#include <Ksl/PolyPlot.h>

namespace Ksl {

class KSL_EXPORT Chart
    : public QWidget
    , public Ksl::Object
{
    Q_OBJECT

public:

    Chart(const QString &title="Ksl Chart", int width=500,
                int height=350, QWidget *parent=0);


    Figure* figure() const;

    XYScale* scale(const QString &name="default-scale");

    Plot* plot(const QString &name,
               const Array<1> &x, const Array<1> &y,
               const QString &style,
               const QString &scaleName="default-scale");

    TextPlot* text(const QString &text, const QPointF &pos,
                   const QColor &stroke=Qt::blue, float rotation=0.0,
                   const QString &scaleName="default-scale");

    LinePlot* line(const QString &name, double a, double b,
                   const QString &style="b",
                   const QString &scaleName="default-scale");

    PolyPlot* poly(const QString &name,
                   const Array<1> &a, double xMin, double xMax,
                   const QColor &stroke=Qt::blue,
                   const QString &scaleName="default-scale");


public slots:

    void save();

    virtual void toggleTranslation(bool activate);

    virtual void toggleZooming(bool activate);


protected:

    Chart(Ksl::ObjectPrivate *priv, const QString &title,
                int width, int height, QWidget *parent);
};

} // namespace Ksl

#endif // KSL_CHARTWINDOW_H
