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

#include <Ksl/XYScale_p.h>
#include <Ksl/Figure.h>
#include <Ksl/FigureItem.h>
#include <QDebug>

namespace Ksl {

XYScale::XYScale(const QString &name)
    : FigureScale(new XYScalePrivate(this), name)
{
    KSL_PUBLIC(XYScale);

    // Create default axis
    m->axisHash[BottomAxis] = new XYAxis(Qt::Horizontal, "X");
    m->axisHash[BottomAxis]->showComponents(
        XYAxis::Line|XYAxis::TicksDown|XYAxis::MiddleTitle);

    m->axisHash[TopAxis] = new XYAxis(Qt::Horizontal, "KSL");
    m->axisHash[TopAxis]->showComponents(XYAxis::Line);

    m->axisHash[LeftAxis] = new XYAxis(Qt::Vertical, "Y");
    m->axisHash[LeftAxis]->showComponents(
        XYAxis::Line|XYAxis::TicksDown|XYAxis::MiddleTitle);

    m->axisHash[RightAxis] = new XYAxis(Qt::Vertical, "");
    m->axisHash[RightAxis]->showComponents(XYAxis::Line);

    m->axisHash[X_Axis] = new XYAxis(Qt::Horizontal, "X");
    m->axisHash[X_Axis]->showComponents(
        XYAxis::Line|XYAxis::TicksDown|XYAxis::EndTitle);
    m->axisHash[X_Axis]->hideZero(true);

    m->axisHash[Y_Axis] = new XYAxis(Qt::Vertical, "Y");
    m->axisHash[Y_Axis]->showComponents(
        XYAxis::Line|XYAxis::TicksDown|XYAxis::EndTitle);
    m->axisHash[Y_Axis]->hideZero(true);

    // Show bounding axis 
    showAxis(BottomAxis|LeftAxis|TopAxis|RightAxis);

    //Tell the axis I am their manager
    for (auto axis : m->axisHash)
        axis->setScale(this);

    // Allocate space for axis on chart bounds
    setXbound(75, 20);
    setYbound(20, 40);
    rescale();
}

XYScalePrivate::~XYScalePrivate() {
    for (auto axis : axisHash)
        delete axis;
}

XYAxis* XYScale::axis(Axis axis) {
    KSL_PUBLIC(XYScale);
    if (m->axisHash.contains(axis))
        return m->axisHash[axis];
    return nullptr;
}


QBrush XYScale::backBrush() const {
    KSL_PUBLIC(const XYScale);
    return m->backBrush;
}

void XYScale::setBackBrush(const QBrush &brush) {
    KSL_PUBLIC(XYScale);
    m->backBrush = brush;
}

QPoint XYScale::map(const QPointF &point) const {
    KSL_PUBLIC(const XYScale);
    QPoint ret;
    double tmp;

    tmp = (point.x() - m->xMin) / m->width;
    ret.setX(m->figXmin + qRound(tmp*m->figWidth));

    tmp = (point.y() - m->yMin) / m->height;
    ret.setY(m->figYmax - qRound(tmp*m->figHeight));

    return ret;
}

QPointF XYScale::unmap(const QPoint &point) const {
    KSL_PUBLIC(const XYScale);
    QPointF ret;
    double tmp;

    tmp = double(point.x() - m->figXmin) / m->figWidth;
    ret.setX(m->xMin + tmp*m->width);

    tmp = double(m->figYmax - point.y()) / m->figHeight;
    ret.setY(m->yMin + tmp*m->height);

    return ret;
}

void XYScale::trackRect(const QRectF &rect) {
    setXrange(rect.left(), rect.right());
    setYrange(rect.top(), rect.bottom());
}

void XYScale::rescale() {
    KSL_PUBLIC(XYScale);

    if (m->itemList.isEmpty()) {
        setXrange(0.0, 1.0);
        setYrange(0.0, 1.0);
        return;
    }

    auto iter = m->itemList.begin();
    auto end = m->itemList.end();
    FigureItem *item = *iter++;

    bool firstRescalable = item->rescalable();
    while (!item->rescalable() && iter != end) {
        item = *iter++;
        if (item->rescalable())
            firstRescalable = true;
    }
    if (!firstRescalable)
        return;

    auto itemRect = item->dataRect();
    setXrange(itemRect.left(), itemRect.right());
    setYrange(itemRect.top(), itemRect.bottom());

    while (iter != end) {
        item = *iter++;
        if (item->rescalable()) {
            itemRect = item->dataRect();
            if (itemRect.left() < m->xMin) m->xMin = itemRect.left();
            if (itemRect.right() > m->xMax) m->xMax = itemRect.right();
            if (itemRect.top() < m->yMin) m->yMin = itemRect.top();
            if (itemRect.bottom() > m->yMax) m->yMax = itemRect.bottom();
        }
    }
    m->width = m->xMax - m->xMin;
    double bound = m->width / 20.0;
    m->xMin -= bound;
    m->xMax += bound;
    m->width += 2.0 * bound;

    m->height = m->yMax - m->yMin;
    bound = m->height / 20.0;
    m->yMin -= bound;
    m->yMax += bound;
    m->height += 2.0 * bound;
}

QRectF XYScale::dataRect() const {
    KSL_PUBLIC(const XYScale);
    return QRectF(m->xMin, m->yMin,
                  m->width, m->height);
}

QRect XYScale::figureRect() const {
    KSL_PUBLIC(const XYScale);
    return QRect(m->figXmin, m->figYmin,
                 m->figWidth, m->figHeight);
}

void XYScale::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(XYScale);

    // Check if any item has NaN or Infs
    if (!std::isfinite(m->width) || !std::isfinite(m->height)) {
        m->figure->informError();
        return;
    }

    // Update figure bounds
    m->figXmin = rect.left() + m->xLowBound;
    m->figXmax = rect.right() - m->xUpBound;
    m->figWidth = m->figXmax - m->figXmin;
    m->figYmin = rect.top() + m->yLowBound;
    m->figYmax = rect.bottom() - m->yUpBound;
    m->figHeight = m->figYmax - m->figYmin;

    // Use base class meyhod to paint item
    QRect innerRect(m->figXmin, m->figYmin,
                    m->figWidth+1, m->figHeight+1);
    painter->save();
    painter->setClipRect(innerRect);
    painter->fillRect(innerRect, m->backBrush);
    FigureScale::paint(rect, painter);
    painter->restore();

    // Inform data bounds to axis and paint them
    m->positionAxis();
    for (auto axis : m->axisHash)
        if (axis->visible())
            axis->paint(painter);
}

void XYScale::setXrange(double xMin, double xMax) {
    KSL_PUBLIC(XYScale);
    m->xMin = xMin;
    m->xMax = xMax;
    m->width = xMax - xMin;
}

void XYScale::setYrange(double yMin, double yMax) {
    KSL_PUBLIC(XYScale);
    m->yMin = yMin;
    m->yMax = yMax;
    m->height = yMax - yMin;
}

void XYScale::setXbound(int xLowBound, int xUpBound) {
    KSL_PUBLIC(XYScale);
    m->xLowBound = xLowBound;
    m->xUpBound = xUpBound;
}

void XYScale::setYbound(int yLowBund, int yUpBound) {
    KSL_PUBLIC(XYScale);
    m->yLowBound = yLowBund;
    m->yUpBound = yUpBound;
}

void XYScalePrivate::positionAxis() {
    axisHash[XYScale::BottomAxis]->setPosition(xMin, xMax, yMin);
    axisHash[XYScale::LeftAxis]->setPosition(yMin, yMax, xMin);
    axisHash[XYScale::TopAxis]->setPosition(xMin, xMax, yMax);
    axisHash[XYScale::RightAxis]->setPosition(yMin, yMax, xMax);
    axisHash[XYScale::X_Axis]->setPosition(xMin, xMax, 0.0);
    axisHash[XYScale::Y_Axis]->setPosition(yMin, yMax, 0.0);

    if (choseAxis) {
        bool xAxOut = xMin > 0.0 || xMax < 0.0;
        bool yAxOut = yMin > 0.0 || yMax < 0.0;

        if (xAxOut && yAxOut) {
            axisHash[XYScale::BottomAxis]->setVisible(true);
            axisHash[XYScale::LeftAxis]->setVisible(true);
            axisHash[XYScale::TopAxis]->setVisible(true);
            axisHash[XYScale::RightAxis]->setVisible(true);
            axisHash[XYScale::X_Axis]->setVisible(false);
            axisHash[XYScale::Y_Axis]->setVisible(false);
        }
        else {
            axisHash[XYScale::BottomAxis]->setVisible(false);
            axisHash[XYScale::LeftAxis]->setVisible(false);
            axisHash[XYScale::TopAxis]->setVisible(false);
            axisHash[XYScale::RightAxis]->setVisible(false);
            axisHash[XYScale::X_Axis]->setVisible(true);
            axisHash[XYScale::Y_Axis]->setVisible(true);
        }
    }
}

void XYScale::showAxis(Axis axis) {
    KSL_PUBLIC(XYScale);
    m->choseAxis = false;
    m->axisHash[XYScale::BottomAxis]->setVisible(axis & XYScale::BottomAxis);
    m->axisHash[XYScale::LeftAxis]->setVisible(axis & XYScale::LeftAxis);
    m->axisHash[XYScale::TopAxis]->setVisible(axis & XYScale::TopAxis);
    m->axisHash[XYScale::RightAxis]->setVisible(axis & XYScale::RightAxis);
    m->axisHash[XYScale::X_Axis]->setVisible(axis & XYScale::X_Axis);
    m->axisHash[XYScale::Y_Axis]->setVisible(axis & XYScale::Y_Axis);
}

void XYScale::autoChoseAxis() {
    KSL_PUBLIC(XYScale);
    m->choseAxis = true;
}


FigureItem* XYScale::selectAt(const QPoint &pos) {
    KSL_PUBLIC(XYScale);
    for (auto item : m->itemList) {
        if (item->figureRect().contains(pos))
            return item;
    }
    for (auto item : m->axisHash) {
        if (item->figureRect().contains(pos))
            return item;
    }
    return nullptr;
}

} // namespace Ksl
