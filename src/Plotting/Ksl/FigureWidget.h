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

#ifndef KSL_FIGUREWIDGET_H
#define KSL_FIGUREWIDGET_H

#include <Ksl/Figure.h>
#include <QWidget>

namespace Ksl {

class KSL_EXPORT FigureWidget
    : public QWidget
    , public Ksl::Object
{
    Q_OBJECT

public:

    FigureWidget(QWidget *parent=0);


    Figure* figure() const;

    QSize sizeHint() const;


public slots:

    virtual void save();

    void setSizeHint(const QSize &sizeHint);


protected:

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    FigureWidget(Ksl::ObjectPrivate *priv, QWidget *parent);

    virtual void paintEvent(QPaintEvent *event);
};

} // namespace Ksl

#endif // KSL_FIGUREWIDGET_H
