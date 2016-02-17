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

KSL_BEGIN_NAMESPACE

ChartAxis::ChartAxis(Qt::Orientation orient,
                     const QString &name,
                     QObject *parent)
    : ChartItem(new ChartAxisPrivate(this, name), parent)
{
    KSL_PUBLIC(ChartAxis);
    m->orient = orient;
    m->rescalable = false;
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
    // fixed coordinates
    int y = scale->map(QPointF(minCoord, anchor)).y();
    int xMin = scale->map(QPointF(minCoord, anchor)).x();
    int xMax = scale->map(QPointF(maxCoord, anchor)).x();

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(xMin, y, xMax, y);
    }

    // draw arrow
    if (components & ChartAxis::Arrow) {
        QPainterPath path;
        path.moveTo(xMax, y);
        path.lineTo(xMax-6, y+4);
        path.lineTo(xMax-6, y-4);
        path.closeSubpath();
        painter->setBrush(QBrush(pen.color()));
        painter->drawPath(path);
    }
}

void ChartAxisPrivate::paintVertical(QPainter *painter) {
    // fixed coordinates
    int x = scale->map(QPointF(anchor, minCoord)).x();
    int yMin = scale->map(QPointF(anchor, minCoord)).y();
    int yMax = scale->map(QPointF(anchor, maxCoord)).y();

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(x, yMin, x, yMax);
    }

    // draw arrow
    if (components & ChartAxis::Arrow) {
        QPainterPath path;
        path.moveTo(x, yMax);
        path.lineTo(x-4, yMax+6);
        path.lineTo(x+4, yMax+6);
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
