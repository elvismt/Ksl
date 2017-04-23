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

#pragma once
#include <QWidget>
#include <ksl/plot/Figure.h>
#include <ksl/plot/LinearScale.h>
#include <ksl/plot/Series.h>

namespace ksl {
namespace plot {

class FigureView:
    public QWidget,
    public ksl::Object
{
    Q_OBJECT

public:

    FigureView(const QString &title="Ksl", int width=460,
               int height=460, QWidget *parent=nullptr);

    FigureView(Figure *figure, QWidget *parent=nullptr);

    Figure* figure() const;


protected:

    virtual void paintEvent(QPaintEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    FigureView(ksl::ObjectPrivate *priv, Figure *figure,
               QWidget *parent=nullptr);
};
}}
