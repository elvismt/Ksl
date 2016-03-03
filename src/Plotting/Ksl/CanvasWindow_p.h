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

#ifndef KSL_CANVASWINDOW_P_H
#define KSL_CANVASWINDOW_P_H

#include <Ksl/CanvasWindow.h>
#include <QVBoxLayout>
#include <QToolBar>
#include <QPainter>

namespace Ksl {

class _CanvasArea
    : public QWidget
{
    Q_OBJECT

public:

    _CanvasArea(const QSize defaultSize, QWidget *parent);

    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);


    QSize defaultSize;
    QPainter painter;
    CanvasWindow *canvasWindow;
    QTimer *timer;
    int timeStep;


public slots:

    void startAnimation();
    void stopAnimation();
};

class CanvasWindowPrivate
    : public Ksl::ObjectPrivate
{
public:

    CanvasWindowPrivate(CanvasWindow *publ)
        : Ksl::ObjectPrivate(publ)
    { }


    QVBoxLayout *layout;
    _CanvasArea *canvasArea;
    QToolBar *toolBar;
};

} // namespace Ksl

#endif // KSL_CANVASWINDOW_P_H
