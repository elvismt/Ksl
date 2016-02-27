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

#ifndef KSL_CANVAS_P_H
#define KSL_CANVAS_P_H

#include <Ksl/Canvas.h>
#include <QtWidgets>

KSL_BEGIN_NAMESPACE

class CanvasPrivate;


class CanvasDrawingArea
    : public QWidget
{
    Q_OBJECT

public:

    CanvasDrawingArea(int width, int height,
                      Canvas *canvas, CanvasPrivate *canvPriv);

    QSize sizeHint() const;

    QSize minimumSizeHint() const;

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);


    Canvas *canvas;
    CanvasPrivate *canvPriv;
    QSize defaultSize;
    QPainter *painter;


public slots:

    void _animate();

    void _stopAnimation();
};


class CanvasPrivate
    : public Ksl::ObjectPrivate
{
public:

    CanvasPrivate(Canvas *publ, int width, int height)
        : Ksl::ObjectPrivate(publ)
        , drawingArea(new CanvasDrawingArea(width, height, publ, this))
    { }


    void init(const QString &title);


    CanvasDrawingArea *drawingArea;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QToolBar *toolBar;
    QTimer *timer;
    int timeStep;
};

KSL_END_NAMESPACE

#endif // KSL_CANVAS_P_H
