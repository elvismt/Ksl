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

#include <ksl/plot/Axis_p.h>
#include <ksl/plot/FigureScale.h>
#include <QtGui>

namespace ksl {
namespace plot {

Axis::Axis(Component component, Qt::Orientation orientation,
           const QString &title, QObject *parent)
    : FigureItem(new AxisPrivate(this), parent)
{
    KSL_PUBLIC(Axis);
    m->component = component;
    m->orientation = orientation;
    m->title = title;
}

QRect Axis::figureRect() const {
    KSL_PUBLIC(const Axis);
    if (m->orientation == Qt::Vertical) {
        return QRect(m->p1.x() - 4, m->p1.y(),
            9, m->p2.y() - m->p1.y() + 1);
    }
    return QRect(m->p1.x(), m->p1.y() - 4,
        m->p2.x() - m->p1.x() + 1, 9);
}

QRectF Axis::dataRect() const {
    KSL_PUBLIC(const Axis);
    if (m->orientation == Qt::Vertical) {
        return QRectF(m->min, m->anchor,
            0.0, m->max - m->min);
    }
    return QRectF(m->anchor, m->min,
        m->max - m->min, 0.0);
}

void Axis::paint(QPainter *painter) {
    KSL_PUBLIC(Axis);
    if (m->orientation == Qt::Vertical) {
        m->p1 = m->scale->map(QPointF(m->anchor, m->min));
        m->p2 = m->scale->map(QPointF(m->anchor, m->max));
    } else {
        m->p1 = m->scale->map(QPointF(m->max, m->anchor));
        m->p2 = m->scale->map(QPointF(m->min, m->anchor));
    }

    if (m->component & Line) {
        m->paintLine(painter);
    }
    if (m->component & Title) {
        m->paintTitle(painter);
    }
    if (m->selected) {
        painter->fillRect(figureRect(), m->selectBrush);
    }
}

void AxisPrivate::paintLine(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing, lineAntialias);
    painter->setPen(linePen);
    painter->drawLine(p1, p2);
}

void AxisPrivate::paintTitle(QPainter *painter) {
    QFontMetrics fontMetrics = painter->fontMetrics();
    if (orientation == Qt::Horizontal) {
        if (component & Axis::TicksUp) {
            painter->drawText(
                (p2.x() + p1.x() - fontMetrics.width(title))/2,
                 p1.y() - fontMetrics.descent() - 5, title);
        } else {
            painter->drawText(
                (p2.x() + p1.x() - fontMetrics.width(title))/2,
                 p1.y() + fontMetrics.height(), title);
        }
    } else {
        if (component & Axis::TicksUp) {
            painter->save();
            painter->rotate(-90.0);
            painter->drawText(
                -(p1.y() + p2.y() + fontMetrics.width(title))/2,
                p1.x() + fontMetrics.height(), title);
            painter->restore();
        }
        else {
            painter->save();
            painter->rotate(-90.0);
            painter->drawText(
                -(p1.y() + p2.y() + fontMetrics.width(title))/2,
                p1.x() - fontMetrics.descent() - 5, title);
            painter->restore();
        }
    }
}

void Axis::setPosition(double min, double max, double anchor) {
    KSL_PUBLIC(Axis);
    m->min = min;
    m->max = max;
    m->anchor = anchor;
}
}}
