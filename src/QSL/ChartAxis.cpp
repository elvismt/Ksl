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
    QRect r = (m->scale != nullptr) ?
              m->scale->figureRect() :
              QRect();
    switch (m->position) {
    case Top:
        r.setY(r.top()-5);
        r.setHeight(10);
        break;
    case Bottom:
        r.setY(r.bottom()-5);
        r.setHeight(10);
        break;
    case Left:
        r.setX(r.left()-5);
        r.setWidth(10);
        break;
    case Right:
        r.setX(r.right()-5);
        r.setWidth(10);
        break;
    }
    return r;
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
    QRectF dataRect = scale->dataRect();
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtHei = fontMetrics.height() - fontMetrics.descent();
    int txtWid;
    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.topLeft(), figureRect.topRight());
    }
    if (component & ChartAxis::Samples || component & ChartAxis::Ticks) {
        if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
            sampler->autoSampleDecimal(
                dataRect.left(),
                dataRect.right(),
                figureRect.width()/60
            );
        }
    }
    for (auto &sample : sampler->sampleList()) {
        QPointF dataPos = scale->dataRect().bottomLeft();
        dataPos.setX(sample.coord);
        QPoint pos = scale->map(dataPos);
        if (component & ChartAxis::Samples) {
            txtWid = fontMetrics.width(sample.label);
            painter->drawText(pos.x()-txtWid/2, pos.y()-txtHei/2, sample.label);
        }
        if (component & ChartAxis::Ticks) {
            painter->drawLine(pos.x(), pos.y(), pos.x(), pos.y()+5);
        }
    }
}


void ChartAxisPrivate::paintLeft(QPainter *painter) {
    QRect figureRect = scale->figureRect();
    QRectF dataRect = scale->dataRect();
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtHei = fontMetrics.height() - fontMetrics.descent();
    int txtWid;
    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomLeft(), figureRect.topLeft());
    }
    if (component & ChartAxis::Samples || component & ChartAxis::Ticks) {
        if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
            sampler->autoSampleDecimal(
                dataRect.top(),
                dataRect.bottom(),
                figureRect.height()/60
            );
        }
    }
    for (auto &sample : sampler->sampleList()) {
        QPointF dataPos = scale->dataRect().topLeft();
        dataPos.setY(sample.coord);
        QPoint pos = scale->map(dataPos);
        if (component & ChartAxis::Samples) {
            txtWid = fontMetrics.width(sample.label);
            painter->drawText(pos.x()-txtWid-txtHei/2, pos.y()+txtHei/2, sample.label);
        }
        if (component & ChartAxis::Ticks) {
            painter->drawLine(pos.x(), pos.y(), pos.x()+5, pos.y());
        }
    }
}


void ChartAxisPrivate::paintBottom(QPainter *painter) {
    QRect figureRect = scale->figureRect();
    QRectF dataRect = scale->dataRect();
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtHei = fontMetrics.height() - fontMetrics.descent();
    int txtWid;
    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomLeft(), figureRect.bottomRight());
    }
    if (component & ChartAxis::Samples || component & ChartAxis::Ticks) {
        if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
            sampler->autoSampleDecimal(
                dataRect.left(),
                dataRect.right(),
                figureRect.width()/60
            );
        }
    }
    for (auto &sample : sampler->sampleList()) {
        QPointF dataPos = scale->dataRect().topLeft();
        dataPos.setX(sample.coord);
        QPoint pos = scale->map(dataPos);
        pos.setY(pos.y() - 1);
        if (component & ChartAxis::Samples) {
            txtWid = fontMetrics.width(sample.label);
            painter->drawText(pos.x()-txtWid/2, pos.y() + 3*txtHei/2, sample.label);
        }
        if (component & ChartAxis::Ticks) {
            painter->drawLine(pos.x(), pos.y(), pos.x(), pos.y()-5);
        }
    }
}


void ChartAxisPrivate::paintRight(QPainter *painter) {
    QRect figureRect = scale->figureRect();
    QRectF dataRect = scale->dataRect();
    QFontMetrics fontMetrics = painter->fontMetrics();
    int txtHei = fontMetrics.height() - fontMetrics.descent();
    // int txtWid;
    if (component & ChartAxis::Line) {
        painter->drawLine(figureRect.bottomRight(), figureRect.topRight());
    }
    if (component & ChartAxis::Samples || component & ChartAxis::Ticks) {
        if (sampler->mode() == ChartAxisSampler::AutoDecimal) {
            sampler->autoSampleDecimal(
                dataRect.top(),
                dataRect.bottom(),
                figureRect.height()/60
            );
        }
    }
    for (auto &sample : sampler->sampleList()) {
        QPointF dataPos = scale->dataRect().topRight();
        dataPos.setY(sample.coord);
        QPoint pos = scale->map(dataPos);
        pos.setX(pos.x() - 1);
        if (component & ChartAxis::Samples) {
            // txtWid = fontMetrics.width(sample.label);
            painter->drawText(pos.x()+txtHei/2, pos.y()+txtHei/2, sample.label);
        }
        if (component & ChartAxis::Ticks) {
            painter->drawLine(pos.x(), pos.y(), pos.x()-5, pos.y());
        }
    }
}


void ChartAxis::setFont(const QFont &font) {
    QSL_PUBLIC(ChartAxis);
    m->font = font;
}


void ChartAxis::setScale(FigureScale *scale) {
    FigureItem::setScale(scale);
    if (scale && scale->figure()) {
        setFont(scale->figure()->font());
    }
}


void ChartAxis::setComponents(Component component) {
    QSL_PUBLIC(ChartAxis);
    if (m->component != component) {
        m->component = component;
        emit appearenceChange(this);
    }
}

QSL_END_NAMESPACE
