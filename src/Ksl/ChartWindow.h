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

namespace Ksl {

class KSL_EXPORT ChartWindow
    : public QWidget
    , public Ksl::Object
{
    Q_OBJECT

public:

    ChartWindow(const QString &title="Ksl Chart", int width=500,
                int height=350, QWidget *parent=0);


    virtual Figure *addFigure(const QString &name,
                              int initRow=-1, int endRow=-1,
                              int initCol=-1, int endCol=-1);

    Figure* figure(const QString &name);

    Figure* figure(int index) const;

    QList<Figure*> figureList() const;


public slots:

    void save();

    void showStatusMessage(const QString &message, int milisecs);


protected:

    ChartWindow(Ksl::ObjectPrivate *priv, const QString &title,
                int width, int height, QWidget *parent);
};

} // namespace Ksl

#endif // KSL_CHARTWINDOW_H
