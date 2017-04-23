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

#include <ksl/plot/FigureView_p.h>
#include <QtGui>

namespace ksl {
namespace plot {

FigureView::FigureView(ksl::ObjectPrivate *priv,
                       Figure *figure, QWidget *parent)
    : QWidget(parent)
    , ksl::Object(priv)
{
    KSL_PUBLIC(FigureView);
    if (figure != nullptr) {
        m->figure = figure;
        m->ownFigure = false;
    } else {
        m->figure = new Figure();
        m->ownFigure = true;
    }
    setAutoFillBackground(false);
    setMinimumSize(250, 250);
    setMouseTracking(true);
    m->figure->setView(this);
    connect(m->figure, SIGNAL(changeOccured()), this, SLOT(update()));
}

FigureView::FigureView(Figure *figure, QWidget *parent)
    : FigureView(new FigureViewPrivate(this), figure, parent)
{}

FigureView::FigureView(const QString &title, int width, int height,
                       QWidget *parent)
    : FigureView(new FigureViewPrivate(this), nullptr, parent)
{
    setWindowTitle(title);
    resize(width, height);
}

FigureViewPrivate::~FigureViewPrivate() {
    if (ownFigure) delete figure;
}

Figure* FigureView::figure() const {
    KSL_PUBLIC(const FigureView);
    return m->figure;
}

void FigureView::paintEvent(QPaintEvent *event) {
    KSL_PUBLIC(FigureView);
    Q_UNUSED(event)

    // draw the figure's contents
    m->painter.begin(this);
    m->figure->paint(rect(), &m->painter);
    m->painter.end();
}

void FigureView::mousePressEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureView);
    if (m->figure != nullptr) {
        m->figure->mousePressEvent(event);
    }
}

void FigureView::mouseMoveEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureView);
    // only propagate tot he items to handle
    // TODO improve it
    if (m->figure != nullptr) {
        m->figure->mouseMoveEvent(event);
    }
}

void FigureView::mouseReleaseEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureView);
    // only propagate tot he items to handle
    // TODO improve it
    if (m->figure != nullptr) {
        m->figure->mouseReleaseEvent(event);
    }
}

void FigureView::mouseDoubleClickEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureView);
    // only propagate tot he items to handle
    // TODO improve it
    if (m->figure != nullptr) {
        m->figure->mouseDoubleClickEvent(event);
    }
}
}}
