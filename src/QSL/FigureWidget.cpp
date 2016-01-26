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

#include <QSL/FigureWidgetPrivate.h>

QSL_BEGIN_NAMESPACE

FigureWidget::FigureWidget(QWidget *parent)
    : QWidget(parent)
    , QSL::Object(new FigureWidgetPrivate(this))
{
    QSL_PUBLIC(FigureWidget);

    setMinimumSize(250, 200);
    m->figure = new Figure();
    m->ownFigure = true;
}


FigureWidget::FigureWidget(const QString &title,
                           const QSize &size,
                           Figure *figure,
                           QWidget *parent)
    : QWidget(parent)
    , QSL::Object(new FigureWidgetPrivate(this))
{
    QSL_PUBLIC(FigureWidget);

    setWindowTitle(title);
    resize(size);
    setMinimumSize(250, 200);

    if (figure != nullptr) {
        m->figure = figure;
        m->ownFigure = false;
    }
    else {
        m->figure = new Figure();
        m->ownFigure = true;
    }
}


FigureWidgetPrivate::~FigureWidgetPrivate() {
    if (ownFigure) {
        delete figure;
    }
}


Figure* FigureWidget::figure() const {
    QSL_PUBLIC(const FigureWidget);
    return m->figure;
}


void FigureWidget::paintEvent(QPaintEvent *event) {
    QSL_PUBLIC(FigureWidget);
    Q_UNUSED(event)

    m->painter.begin(this);
    m->figure->paint(rect(), &m->painter);
    m->painter.end();
}

QSL_END_NAMESPACE
