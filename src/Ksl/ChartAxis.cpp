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
}

ChartAxisPrivate::~ChartAxisPrivate() {
    delete sampler;
}

void ChartAxis::setOrientation(Qt::Orientation orient) {
    KSL_PUBLIC(ChartAxis);
    m->orient = orient;
}


double ChartAxis::min() const {
    KSL_PUBLIC(const ChartAxis);
    return m->minCoord;
}


double ChartAxis::max() const {
    KSL_PUBLIC(const ChartAxis);
    return m->maxCoord;
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


void ChartAxis::setSelected(bool selected) {
    KSL_PUBLIC(ChartAxis);
    Component oldComps = m->components;
    if (selected)
        m->components |= SelectionRect;
    else
        m->components &= ~SelectionRect;
    if (oldComps != m->components)
        emit appearenceChanged(this);
}


bool ChartAxis::selected() const {
    KSL_PUBLIC(const ChartAxis);
    return m->components & SelectionRect;
}


ChartAxisSampler* ChartAxis::sampler() const {
    KSL_PUBLIC(const ChartAxis);
    return m->sampler;
}


QRect ChartAxis::chartRect() const {
    KSL_PUBLIC(const ChartAxis);
    if (m->orient == Qt::Vertical)
        return QRect(m->chartAnchor-5, m->chartMin,
                     10, m->chartMax - m->chartMin);
    // Qt::Orizontal
    return QRect(m->chartMin, m->chartAnchor-5,
                 m->chartMax - m->chartMin, 10);
}


QRectF ChartAxis::dataRect() const {
    KSL_PUBLIC(const ChartAxis);
    if (m->orient == Qt::Vertical)
        return QRectF(m->anchor, m->minCoord,
                      0.0, m->maxCoord - m->minCoord);
    // Qt::Orizontal
    return QRect(m->minCoord, m->anchor,
                 m->maxCoord - m->minCoord, 0.0);
}


void ChartAxis::paint(QPainter *painter) {
    KSL_PUBLIC(ChartAxis);
    painter->setPen(m->pen);
    painter->setBrush(m->brush);
    painter->setRenderHint(QPainter::Antialiasing, false);

    if (m->orient == Qt::Horizontal)
        m->paintHorizontal(painter);
    else // Qt::Vertical
        m->paintVertical(painter);

    // For GUI apps the hability to select things, maybe by clicking
    // is cool. Selected axis will paint it's bounding rect
    if (m->components & SelectionRect) {
        painter->fillRect(chartRect(), m->selectBrush);
    }
}


void ChartAxisPrivate::paintHorizontal(QPainter *painter) {
    auto fontMetrics = painter->fontMetrics();

    // fixed coordinates
    int y = scale->map(QPointF(minCoord, anchor)).y();
    chartAnchor = y;
    chartMin = scale->map(QPointF(minCoord, anchor)).x();
    chartMax = scale->map(QPointF(maxCoord, anchor)).x();

    // A little hack to make txtHei better reflect character height
    int txtHei = qRound(float(fontMetrics.height())*0.65);
    int txtWid = 0;

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(chartMin, y, chartMax, y);
    }

    // draw downwards ticks
    if (components & ChartAxis::TicksDown) {
        for (const auto &sample : sampler->sampleList()) {
            int x = scale->map(QPointF(sample.coord, anchor)).x();
            if (x < chartMin || x > chartMax)
                continue;
            if (sample.isMajor) {
                txtWid = fontMetrics.width(sample.label);
                painter->drawLine(x, y, x, y+bigTick);
                painter->drawText(x-txtWid/2, y+txtHei+10, sample.label);
            }
            if (!sample.isMajor && minTicks)
                painter->drawLine(x, y, x, y+smallTick);
        }
    }
    // draw upwards ticks
    if (components & ChartAxis::TicksUp) {
        for (const auto &sample : sampler->sampleList()) {
            int x = scale->map(QPointF(sample.coord, anchor)).x();
            if (x < chartMin || x > chartMax)
                continue;
            if (sample.isMajor) {
                txtWid = fontMetrics.width(sample.label);
                painter->drawLine(x, y, x, y-bigTick);
                painter->drawText(x-txtWid/2, y-10, sample.label);
            }
            if (!sample.isMajor && minTicks)
                painter->drawLine(x, y, x, y-smallTick);
        }
    }
    // draw middle title
    if (components & ChartAxis::MiddleTitle) {
        txtWid = fontMetrics.width(name);
        int x = chartMin+(chartMax-chartMin-txtWid)/2;
        y = components & ChartAxis::TicksUp ?
            chartAnchor -txtHei -15 : chartAnchor+2*txtHei+15;
        painter->drawText(x, y, name);
    }
    // draw end title
    if (components & ChartAxis::EndTitle) {
        txtWid = fontMetrics.width(name);
        int x = chartMax +4;
        y = chartAnchor -4;
        painter->drawText(x, y, name);
    }
    // draw arrow
    if (components & ChartAxis::Arrow) {
        painter->setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.moveTo(chartMax, chartAnchor);
        path.lineTo(chartMax-8, chartAnchor+3);
        path.lineTo(chartMax-8, chartAnchor-3);
        path.closeSubpath();
        painter->setBrush(QBrush(pen.color()));
        painter->drawPath(path);
    }
}


void ChartAxisPrivate::paintVertical(QPainter *painter) {
    auto fontMetrics = painter->fontMetrics();

    // fixed coordinates
    int x = scale->map(QPointF(anchor, minCoord)).x();
    chartAnchor = x;
    chartMin = scale->map(QPointF(anchor, maxCoord)).y();
    chartMax = scale->map(QPointF(anchor, minCoord)).y();

    // A little hack to make txtHei better reflect character height
    int txtHei = qRound(float(fontMetrics.height())*0.65);
    int txtWid, maxTxtWid = 0;

    // draw main axis line
    if (components & ChartAxis::Line) {
        painter->drawLine(x, chartMin, x, chartMax);
    }
    // draw leftwards ticks
    if (components & ChartAxis::TicksDown) {
        for (const auto &sample : sampler->sampleList()) {
            int y = scale->map(QPointF(anchor, sample.coord)).y();
            if (y < chartMin || y > chartMax)
                continue;
            if (sample.isMajor) {
                txtWid = fontMetrics.width(sample.label);
                if (txtWid > maxTxtWid) maxTxtWid = txtWid;
                painter->drawLine(x, y, x-bigTick, y);
                painter->drawText(x-txtWid-10, y+txtHei/2, sample.label);
            }
            if (!sample.isMajor && minTicks)
                painter->drawLine(x, y, x-smallTick, y);
        }
    }
    // draw rightwards ticks
    if (components & ChartAxis::TicksUp) {
        for (const auto &sample : sampler->sampleList()) {
            int y = scale->map(QPointF(anchor, sample.coord)).y();
            if (y < chartMin || y > chartMax)
                continue;
            if (sample.isMajor) {
                txtWid = fontMetrics.width(sample.label);
                if (txtWid > maxTxtWid) maxTxtWid = txtWid;
                painter->drawLine(x, y, x+bigTick, y);
                painter->drawText(x+10, y+txtHei/2, sample.label);
            }
            if (!sample.isMajor && minTicks)
                painter->drawLine(x, y, x+smallTick, y);
        }
    }
    // draw middle title
    if (components & ChartAxis::MiddleTitle) {
        painter->save();
        painter->rotate(-90.0);
        txtWid = fontMetrics.width(name);
        x = -chartMin -(chartMax-chartMin+txtWid)/2;
        int y = (components & ChartAxis::TicksUp) ?
            chartAnchor +maxTxtWid +txtHei +15 :
            chartAnchor -maxTxtWid -15;
        painter->drawText(x, y, name);
        painter->restore();
    }
    // draw end title
    if (components & ChartAxis::EndTitle) {
        x = chartAnchor;
        int y = chartMin -4;
        painter->drawText(x, y, name);
    }
    // draw arrow
    if (components & ChartAxis::Arrow) {
        painter->setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.moveTo(chartAnchor, chartMin);
        path.lineTo(chartAnchor-3, chartMin+8);
        path.lineTo(chartAnchor+3, chartMin+8);
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

    m->components = NullComponent;
    if (components.contains("line", Qt::CaseInsensitive)) m->components |= Line;
    if (components.contains("arrow", Qt::CaseInsensitive)) m->components |= Arrow;
    if (components.contains("ticksUp", Qt::CaseInsensitive)) m->components |= TicksUp;
    if (components.contains("ticksDown", Qt::CaseInsensitive)) m->components |= TicksDown;
    if (components.contains("middleTitle", Qt::CaseInsensitive)) m->components |= MiddleTitle;
    if (components.contains("endTitle", Qt::CaseInsensitive)) m->components |= EndTitle;
    if (components.contains("selectionRect", Qt::CaseInsensitive)) m->components |= SelectionRect;

    if (oldValue != m->components) {
        emit appearenceChanged(this);
    }
}

void ChartAxis::setShowMinorTicks(bool show) {
    KSL_PUBLIC(ChartAxis);
    if (m->minTicks != show) {
        m->minTicks = show;
        emit appearenceChanged(this);
    }
}

void ChartAxis::setPen(const QPen &pen) {
    KSL_PUBLIC(ChartAxis);
    m->pen = pen;
}

void ChartAxis::setBrush(const QBrush &brush) {
    KSL_PUBLIC(ChartAxis);
    m->brush = brush;
}

void ChartAxis::setSelectBrush(const QBrush &brush) {
    KSL_PUBLIC(ChartAxis);
    m->selectBrush = brush;
}

QPen ChartAxis::pen() const {
    KSL_PUBLIC(const ChartAxis);
    return m->pen;
}

QBrush ChartAxis::brush() const {
    KSL_PUBLIC(const ChartAxis);
    return m->brush;
}

QBrush ChartAxis::selectBrush() const {
    KSL_PUBLIC(const ChartAxis);
    return m->selectBrush;
}

KSL_END_NAMESPACE
