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

#include <Ksl/ChartAxis_p.h>
#include <Ksl/ChartScale.h>
#include <QDebug>

KSL_BEGIN_NAMESPACE

ChartAxis::ChartAxis(Qt::Orientation orient,
                     const QString &name,
                     QObject *parent)
    : ChartItem(new ChartAxisPrivate(this, name), parent)
{
    KSL_PUBLIC(ChartAxis);
    m->orient = orient;
    m->rescalable = false;
    m->pen.setWidth(2);
    m->antialias = true;
}

ChartAxisPrivate::~ChartAxisPrivate() {
    delete sampler;
}

void ChartAxis::setOrientation(Qt::Orientation orient) {
    KSL_PUBLIC(ChartAxis);
    m->orient = orient;
}

void ChartAxis::setEnds(double min, double max) {
    KSL_PUBLIC(ChartAxis);
    m->minCoord = min;
    m->maxCoord = max;
}

void ChartAxis::setEnds(double min, double max, double anchor) {
    KSL_PUBLIC(ChartAxis);
    m->minCoord = min;
    m->maxCoord = max;
    m->anchor = anchor;
}

ChartAxisSampler* ChartAxis::sampler() const {
    KSL_PUBLIC(const ChartAxis);
    return m->sampler;
}

QRect ChartAxis::chartRect() const {
    // TODO
    return QRect();
}

QRectF ChartAxis::dataRect() const {
    // TODO
    return QRectF();
}

void ChartAxis::paint(QPainter *painter) {
    KSL_PUBLIC(ChartAxis);
    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    switch (m->orient) {
        case Qt::Horizontal:
            m->paintHorizontal(painter);
            break;
        case Qt::Vertical:
            m->paintVertical(painter);
            break;
    }
}

void ChartAxisPrivate::paintHorizontal(QPainter *painter) {
    auto fontMetrics = painter->fontMetrics();

    // fixed coordinates
    int y = scale->map(QPointF(minCoord, anchor)).y();
    int xMin = scale->map(QPointF(minCoord, anchor)).x();
    int xMax = scale->map(QPointF(maxCoord, anchor)).x();

    int txtHei = fontMetrics.height() + 2;
    int txtWid = 0;

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(xMin, y, xMax, y);
    }

    // draw downwards ticks
    if (components & ChartAxis::TicksDown) {
        for (const auto &sample : sampler->sampleList()) {
            int x = scale->map(QPointF(sample.coord, anchor)).x();
            txtWid = fontMetrics.width(sample.label);
            painter->drawLine(x, y, x, y+5);
            painter->drawText(x-txtWid/2, y+txtHei, sample.label);
        }
    }

    // draw arrow
    if (components & ChartAxis::Arrow) {
        QPainterPath path;
        path.moveTo(xMax, y);
        path.lineTo(xMax-8, y+3);
        path.lineTo(xMax-8, y-3);
        path.closeSubpath();
        painter->setBrush(QBrush(pen.color()));
        painter->drawPath(path);
    }
}

void ChartAxisPrivate::paintVertical(QPainter *painter) {
    auto fontMetrics = painter->fontMetrics();

    // fixed coordinates
    int x = scale->map(QPointF(anchor, minCoord)).x();
    int yMin = scale->map(QPointF(anchor, minCoord)).y();
    int yMax = scale->map(QPointF(anchor, maxCoord)).y();

    int txtHei = fontMetrics.height() + 2;
    int txtWid = 0;

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(x, yMin, x, yMax);
    }

    // draw leftwards ticks
    if (components & ChartAxis::TicksDown) {
        for (const auto &sample : sampler->sampleList()) {
            int y = scale->map(QPointF(anchor, sample.coord)).y();
            txtWid = fontMetrics.width(sample.label);
            painter->drawLine(x, y, x-5, y);
            painter->drawText(x-txtWid-12, y+txtHei/4, sample.label);
        }
    }

    // draw arrow
    if (components & ChartAxis::Arrow) {
        QPainterPath path;
        path.moveTo(x, yMax);
        path.lineTo(x-3, yMax+8);
        path.lineTo(x+3, yMax+8);
        path.closeSubpath();
        painter->setBrush(QBrush(pen.color()));
        painter->drawPath(path);
    }
}

void ChartAxis::setComponents(Component components) {
    KSL_PUBLIC(ChartAxis);
    if (m->components != components) {
        m->components = components;
        emit appearenceChanged(this);
    }
}

void ChartAxis::setComponents(const QString &components) {
    KSL_PUBLIC(ChartAxis);
    auto oldValue = m->components;

    m->components = AllComponents;
    if (!components.contains("line", Qt::CaseInsensitive)) m->components &= ~Line;
    if (!components.contains("arrow", Qt::CaseInsensitive)) m->components &= ~Arrow;
    if (!components.contains("ticksUp", Qt::CaseInsensitive)) m->components &= ~TicksUp;
    if (!components.contains("ticksDown", Qt::CaseInsensitive)) m->components &= ~TicksDown;
    if (!components.contains("titleUp", Qt::CaseInsensitive)) m->components &= ~TitleUp;
    if (!components.contains("titleDown", Qt::CaseInsensitive)) m->components &= ~TitleDown;

    if (oldValue != m->components) {
        emit appearenceChanged(this);
    }
}

KSL_END_NAMESPACE
