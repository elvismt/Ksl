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

#include <Ksl/Chart_p.h>
#include <Ksl/ChartScale.h>
#include <Ksl/ChartItem.h>

KSL_BEGIN_NAMESPACE

Chart::Chart(const QString &name, QObject *parent)
    : QObject(parent)
    , Ksl::Object(new ChartPrivate(this,name))
{
    setColorTheme(LightTheme);
}


QList<ChartScale*>& Chart::scaleList() {
    KSL_PUBLIC(Chart);
    return m->scaleList;
}


const QList<ChartScale*>& Chart::scaleList() const {
    KSL_PUBLIC(const Chart);
    return m->scaleList;
}


void Chart::add(ChartScale *scale) {
    KSL_PUBLIC(Chart);
    if (!scale) {
        return;
    }
    if (!m->scaleList.contains(scale)) {
        m->scaleList.append(scale);
        scale->setChart(this);
        scale->setColorTheme(m->colorTheme);
        emit changed(this);
    }
}


void Chart::setColorTheme(ColorTheme theme) {
    KSL_PUBLIC(Chart);
    m->colorTheme = theme;
    if (theme == ColorTheme::DarkTheme) {
        m->backBrush.setColor(Qt::black);
        m->nameColor = Qt::white;
    }
    else {
        m->backBrush.setColor(Qt::white);
        m->nameColor = Qt::black;
    }
    for (auto scale : m->scaleList)
        scale->setColorTheme(theme);
    emit changed(this);
}


void Chart::informError() {
    KSL_PUBLIC(Chart);
    m->onError = true;
    emit errorOccurred(this);
}


void Chart::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(Chart);
    m->onError = false;
    painter->save();
    painter->setFont(m->font);
    painter->setClipRect(rect);
    if (m->paintBack) {
        painter->fillRect(rect, m->backBrush);
    }
    for (auto scale : m->scaleList) {
        if (scale->visible()) {
            scale->paint(rect, painter);
        }
    }
    if (m->showName) {
        painter->setPen(QPen(m->nameColor));
        QFontMetrics fm = painter->fontMetrics();
        painter->drawText(
            rect.center().x() - fm.width(m->name)/2,
            fm.height(),
            m->name
        );
    }

    if (m->onError) {
        painter->setPen(QPen(Qt::red));
        painter->drawText(20, 40, "Ksl::Chart ERROR: NON NUMERIC VALUES");
    }
    painter->restore();
}


void Chart::save(const QString &fileName,
                 const QSize &size, const char *format)
{
    QImage image(size, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(QPoint(0,0),size), &painter);
    image.save(fileName, format);
}


void Chart::onAppearenceChange(ChartItem *item) {
    Q_UNUSED(item)
    emit changed(this);
}


void Chart::onDataChange(ChartItem *item) {
    item->scale()->rescale();
    emit changed(this);
}


QString Chart::name() const {
    KSL_PUBLIC(const Chart);
    return m->name;
}


bool Chart::showName() const {
    KSL_PUBLIC(const Chart);
    return m->showName;
}


QColor Chart::nameColor() const {
    KSL_PUBLIC(const Chart);
    return m->nameColor;
}


void Chart::setName(const QString &name) {
    KSL_PUBLIC(Chart);
    if (m->name != name) {
        m->name = name;
        emit changed(this);
    }
}


void Chart::setShowName(bool showName) {
    KSL_PUBLIC(Chart);
    if (m->showName != showName) {
        m->showName = showName;
        emit changed(this);
    }
}


void Chart::setNameColor(const QColor &color) {
    KSL_PUBLIC(Chart);
    if (m->nameColor != color) {
        m->nameColor = color;
        emit changed(this);
    }
}

KSL_END_NAMESPACE
