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

#include <ksl/plot/LinearScale_p.h>
#include <ksl/plot/Figure.h>
#include <ksl/plot/FigureItem.h>
#include <QtGui>

namespace ksl {
namespace plot {

LinearScale::LinearScale(const QString &title, Figure *figure)
    : FigureScale(new LinearScalePrivate(this))
{
    KSL_PUBLIC(LinearScale);
    m->title = title;

    m->axis[BottomAxis] = new Axis(Axis::Everything, Qt::Horizontal, "BottomAxis");
    m->axis[LeftAxis] = new Axis(Axis::Everything, Qt::Vertical, "LeftAxis");
    m->axis[TopAxis] = new Axis(Axis::Everything, Qt::Horizontal, "TopAxis");
    m->axis[RightAxis] = new Axis(Axis::Everything, Qt::Vertical, "RightAxis");
    m->axis[X_Axis] = new Axis(Axis::Everything, Qt::Horizontal, "X Axis");
    m->axis[Y_Axis] = new Axis(Axis::Everything, Qt::Vertical, "Y Axis");

    for (auto axis : m->axis) {
        axis->setScale(this);
    }
    rescale();
    setFrameStyle(BoundAxis);
    if (figure != nullptr) {
        figure->addScale(this);
    }
}

void LinearScale::rescale() {
    KSL_PUBLIC(LinearScale);
    if (m->itemList.isEmpty()) {
        setXrange(0.0, 1.0);
        setYrange(0.0, 1.0);
        return;
    }
    // find the first scalable and visible item
    auto iter = m->itemList.begin();
    auto end = m->itemList.end();
    FigureItem *item = nullptr;
    bool someScales = false;
    while (iter != end) {
        item = *(iter++);
        if (item->visible() && item->scalable()) {
            someScales = true;
            break;
        }
    }
    if (!someScales) {
        return;
    }
    QRectF itemRect = item->dataRect();
    setXrange(itemRect.left(), itemRect.right());
    setYrange(itemRect.top(), itemRect.bottom());

    // check if any of the oter visible items stretch the bounds
    while (iter != end) {
        item = *(iter++);
        if (item->visible() && item->scalable()) {
            itemRect = item->dataRect();
            if (itemRect.left() < m->dataXmin) m->dataXmin = itemRect.left();
            if (itemRect.right() > m->dataXmax) m->dataXmax = itemRect.right();
            if (itemRect.top() < m->dataYmin) m->dataYmin = itemRect.top();
            if (itemRect.bottom() > m->dataYmax) m->dataYmax = itemRect.bottom();
        }
    }

    m->dataWidth = m->dataXmax - m->dataXmin;
    m->dataXmin -= m->dataWidth * m->horizontalMargin;
    m->dataXmax += m->dataWidth * m->horizontalMargin;
    m->dataWidth += 2.0 * m->dataWidth * m->horizontalMargin;

    m->dataHeight = m->dataYmax - m->dataYmin;
    m->dataYmin -= m->dataHeight * m->verticalMargin;
    m->dataYmax += m->dataHeight * m->verticalMargin;
    m->dataHeight += 2.0 * m->dataHeight * m->verticalMargin;
}

QRect LinearScale::figureRect() const {
    KSL_PUBLIC(const LinearScale);
    return QRect(m->xMin, m->yMin,
                 m->width, m->height);
}

QRectF LinearScale::dataRect() const {
    KSL_PUBLIC(const LinearScale);
    return QRectF(m->dataXmin, m->dataYmin,
                  m->dataWidth, m->dataHeight);
}

QPoint LinearScale::map(const QPointF &p) const {
    KSL_PUBLIC(const LinearScale);
    QPoint res;
    double temp;

    temp = (p.x() - m->dataXmin) / m->dataWidth;
    res.setX(m->xMin + temp*m->width);
    temp = (p.y() - m->dataYmin) / m->dataHeight;
    res.setY(m->yMax - temp*m->height);
    return res;
}

QPointF LinearScale::unmap(const QPoint &p) const {
    KSL_PUBLIC(const LinearScale);
    QPointF res;
    double temp;

    temp = (p.x() - m->xMin) / m->width;
    res.setX(m->dataXmin + temp*m->dataWidth);
    temp = (m->yMax - p.y()) / m->height;
    res.setY(m->dataYmin - temp*m->dataHeight);
    return res;
}

void LinearScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(LinearScale);

    // collect figure position and bounds
    m->xMin = rect.left() + m->leftPadding;
    m->xMax = rect.right() - m->rightPadding;
    m->width = m->xMax - m->xMin;
    m->yMin = rect.top() + m->topPadding;
    m->yMax = rect.bottom() - m->bottomPadding;
    m->height = m->yMax - m->yMin;

    // clip to the the region inside the padding
    painter->save();
    painter->setClipRect(figureRect());
    FigureScale::paint(rect, painter);
    painter->restore();

    // paint the axis
    m->positionAxis();
    for (auto axis : m->axis) {
        if (axis->visible()) {
            axis->paint(painter);
        }
    }
}

void LinearScale::setXrange(double min, double max) {
    KSL_PUBLIC(LinearScale);
    m->dataXmin = min;
    m->dataXmax = max;
    m->dataWidth = max - min;
}

void LinearScale::setYrange(double min, double max) {
    KSL_PUBLIC(LinearScale);
    m->dataYmin = min;
    m->dataYmax = max;
    m->dataHeight = max - min;
}

void LinearScale::setFrameStyle(FrameStyle frameStyle) {
    KSL_PUBLIC(LinearScale);
    if (frameStyle & BoundAxis) {
        m->axis[LinearScale::BottomAxis]->setVisible(true);
        m->axis[LinearScale::LeftAxis]->setVisible(true);
        m->axis[LinearScale::TopAxis]->setVisible(true);
        m->axis[LinearScale::RightAxis]->setVisible(true);
        m->axis[LinearScale::X_Axis]->setVisible(false);
        m->axis[LinearScale::Y_Axis]->setVisible(false);
    } else if (frameStyle & ZeroAxis) {
        m->axis[LinearScale::BottomAxis]->setVisible(false);
        m->axis[LinearScale::LeftAxis]->setVisible(false);
        m->axis[LinearScale::TopAxis]->setVisible(false);
        m->axis[LinearScale::RightAxis]->setVisible(false);
        m->axis[LinearScale::X_Axis]->setVisible(true);
        m->axis[LinearScale::Y_Axis]->setVisible(true);
    }
}

void LinearScalePrivate::positionAxis() {
    axis[LinearScale::BottomAxis]->setPosition(dataXmin, dataXmax, dataYmin);
    axis[LinearScale::LeftAxis]->setPosition(dataYmin, dataYmax, dataXmin);
    axis[LinearScale::TopAxis]->setPosition(dataXmin, dataXmax, dataYmax);
    axis[LinearScale::RightAxis]->setPosition(dataYmin, dataYmax, dataXmax);
    axis[LinearScale::X_Axis]->setPosition(dataXmin, dataXmax, 0.0);
    axis[LinearScale::Y_Axis]->setPosition(dataYmin, dataYmax, 0.0);
}
}}
