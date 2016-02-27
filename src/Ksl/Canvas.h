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

#ifndef KSL_CANVAS_H
#define KSL_CANVAS_H

#include <Ksl/Object.h>
#include <QMainWindow>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT Canvas
    : public QMainWindow
    , public Ksl::Object
{
    Q_OBJECT

public:

    Canvas(const QString &title="Ksl", int width=500,
           int height=500, QWidget *parent=0);

    virtual ~Canvas();

    virtual void paint(QPainter *painter, const QRect &rect);


public slots:

    virtual void updateCanvas();

    virtual void savePng();

    virtual void setTimeStep(int milisecs);

    virtual void leftClick(const QPoint &pos);

    virtual void rightClick(const QPoint &pos);

    virtual void mouseMove(const QPoint &pos);

    virtual void mouseRelease(const QPoint &pos);

    virtual void reset();

    virtual void start();

    virtual void animate();

    virtual void stop();


protected:

    Canvas(ObjectPrivate *priv, const QString &title, int width,
           int height, QWidget *parent);
};

KSL_END_NAMESPACE

#endif // KSL_CANVAS_H
