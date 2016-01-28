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
#include <QSL/Figure.h>

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
    QSL_PUBLIC(ChartAxis);
    QRect rect = m->scale->figureRect();
    int c = 0;
    switch (m->position) {
    case Top:
    case Bottom:
        c = rect.y();
        rect.setY(c - 5);
        rect.setHeight(10);
        break;
    case Left:
    case Right:
        c = rect.x();
        rect.setX(c - 5);
        rect.setWidth(10);
        break;
    }
    return rect;
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
    painter->setFont(m->font);
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
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtSpac = qRound(fontMetrics.height() * 0.66);

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.topLeft(), figureRect.topRight());
    }

    if (component & ChartAxis::Samples) {
        for (auto &sample : sampler->sampleList()) {
            QPointF dataPos = scale->dataRect().bottomLeft();
            dataPos.setX(sample.coord);
            QPoint pos = scale->map(dataPos);
            pos.setY(pos.y() - txtSpac);
            painter->drawText(pos, sample.label);
        }
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
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtSpac = qRound(fontMetrics.height() * 0.66);

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomLeft(), figureRect.bottomRight());
    }

    if (component & ChartAxis::Samples) {
        for (auto &sample : sampler->sampleList()) {
            QPointF dataPos = scale->dataRect().topLeft();
            dataPos.setX(sample.coord);
            QPoint pos = scale->map(dataPos);
            pos.setY(pos.y() + 2*txtSpac);
            painter->drawText(pos, sample.label);
        }
    }
}


void ChartAxisPrivate::paintRight(QPainter *painter) {
    QRect figureRect = scale->figureRect();

    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomRight(), figureRect.topRight());
    }
}


void ChartAxis::setFont(const QFont &font) {
    QSL_PUBLIC(ChartAxis);
    m->font = font;
}


void ChartAxis::setScale(FigureScale *scale) {
    QSL_PUBLIC(ChartAxis);
    FigureItem::setScale(scale);
    if (scale && scale->figure()) {
        setFont(scale->figure()->font());
    }
}

QSL_END_NAMESPACE
