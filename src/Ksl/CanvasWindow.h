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

#ifndef KSL_CANVASWINDOW_H
#define KSL_CANVASWINDOW_H

#include <QWidget>
#include <QPainter>
#include <Ksl/Object.h>

namespace Ksl {

class KSL_EXPORT CanvasWindow
    : public QWidget
    , public Ksl::Object
{
    Q_OBJECT

public:

    CanvasWindow(const QString &title="Ksl Canvas", int width=450,
                int height=450, QWidget *parent=0);


    virtual void paint(const QRect &rect, QPainter *painter);

    virtual void leftClick(const QPoint &pos);

    virtual void rightClick(const QPoint &pos);

    virtual void clickRelease(const QPoint &pos);

    virtual void pointerMove(const QPoint &pos);


public slots:

    void save();

    void repaintCanvas();

    QRect canvasRect();

    void setTimeStep(int milisecs);

    virtual void reset();

    virtual void start();

    virtual void animate();

    virtual void stop();


protected:

    CanvasWindow(Ksl::ObjectPrivate *priv, const QString &title,
                 int width, int height, QWidget *parent);
};

} // namespace Ksl

#endif // KSL_CANVASWINDOW_H
