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

#include <QSL/ChartAxisPrivate.h>
#include <QSL/FigureScale.h>

QSL_BEGIN_NAMESPACE

ChartAxis::ChartAxis(const QString &name, Position position,
                     FigureScale *scale, QObject *parent)
    : FigureItem(new ChartAxisPrivate(this, name, position), parent)
{
    setScale(scale);
}


ChartAxisPrivate::~ChartAxisPrivate() {
    delete sampler;
}


ChartAxis::Position ChartAxis::position() const {
    QSL_PUBLIC(const ChartAxis);
    return m->position;
}


QRect ChartAxis::figureRect() const {
    // TODO
    return QRect();
}


QRectF ChartAxis::dataRect() const {
    // TODO
    return QRectF();
}


ChartAxisSampler* ChartAxis::sampler() const {
    QSL_PUBLIC(const ChartAxis);
    return m->sampler;
}


void ChartAxis::paint(QPainter *painter) {
    QSL_PUBLIC(ChartAxis);

    painter->setPen(m->pen);
    switch (m->position) {
    case Top:
        m->paintTop(painter);
        break;
    case Left:
        m->paintLeft(painter);
        break;
    case Bottom:
        m->paintBottom(painter);
        break;
    case Right:
        m->paintRight(painter);
        break;
    }
}


void ChartAxisPrivate::paintTop(QPainter *painter) {
    QRect figureRect = scale->figureRect();

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.topLeft(), figureRect.topRight());
    }
}


void ChartAxisPrivate::paintLeft(QPainter *painter) {
    QRect figureRect = scale->figureRect();

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomLeft(), figureRect.topLeft());
    }
}


void ChartAxisPrivate::paintBottom(QPainter *painter) {
    QRect figureRect = scale->figureRect();

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomLeft(), figureRect.bottomRight());
    }
}


void ChartAxisPrivate::paintRight(QPainter *painter) {
    QRect figureRect = scale->figureRect();

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomRight(), figureRect.topRight());
    }
}

QSL_END_NAMESPACE
