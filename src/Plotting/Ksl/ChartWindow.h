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
#include <Ksl/XYPlot.h>
#include <Ksl/TextLabelPlot.h>
#include <Ksl/LinePlot.h>

namespace Ksl {

class KSL_EXPORT ChartWindow
    : public QWidget
    , public Ksl::Object
{
    Q_OBJECT

public:

    ChartWindow(const QString &title="Ksl Chart", int width=500,
                int height=350, QWidget *parent=0);


    Figure* figure() const;

    XYScale* xyScale(const QString &name="default-scale");

    XYPlot* xyPlot(const QString &name,
                   const Array<1> &x, const Array<1> &y,
                   XYPlot::Symbol symbol=XYPlot::Line,
                   const QColor &stroke=Qt::blue, const QColor &fill=Qt::red,
                   const QString &scaleName="default-scale");

    XYPlot* xyPlot(const QString &name) const;

    TextLabelPlot* textLabel(const QString &text, const QPointF &pos,
                             const QColor &color=Qt::blue, float rotation=0.0,
                             const QString &scaleName="default-scale");

    LinePlot* line(const QString &name, double a, double b,
                   const QPen &pen=QPen(Qt::red),
                   const QString &scaleName="default-scale");


public slots:

    void save();

    void showStatusMessage(const QString &message, int milisecs);

    virtual void toggleTranslation(bool activate);
    virtual void toggleZooming(bool activate);


protected:

    ChartWindow(Ksl::ObjectPrivate *priv, const QString &title,
                int width, int height, QWidget *parent);
};

} // namespace Ksl

#endif // KSL_CHARTWINDOW_H
