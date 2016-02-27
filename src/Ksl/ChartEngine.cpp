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

#include <Ksl/ChartEngine_p.h>
#include <Ksl/ChartScale.h>
#include <Ksl/ChartItem.h>

KSL_BEGIN_NAMESPACE

ChartEngine::ChartEngine(const QString &name, QObject *parent)
    : QObject(parent)
    , Ksl::Object(new ChartEnginePrivate(this,name))
{
    setColorTheme(LightTheme);
}


QList<ChartScale*>& ChartEngine::scaleList() {
    KSL_PUBLIC(ChartEngine);
    return m->scaleList;
}


const QList<ChartScale*>& ChartEngine::scaleList() const {
    KSL_PUBLIC(const ChartEngine);
    return m->scaleList;
}


void ChartEngine::add(ChartScale *scale) {
    KSL_PUBLIC(ChartEngine);
    if (!scale) {
        return;
    }
    if (!m->scaleList.contains(scale)) {
        m->scaleList.append(scale);
        scale->setChartEngine(this);
        scale->setColorTheme(m->colorTheme);
        emit changed(this);
    }
}


void ChartEngine::setColorTheme(ColorTheme theme) {
    KSL_PUBLIC(ChartEngine);
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


void ChartEngine::informError() {
    KSL_PUBLIC(ChartEngine);
    m->onError = true;
    emit errorOccurred(this);
}


void ChartEngine::paint(const QRect &rect, QPainter *painter) {
    KSL_PUBLIC(ChartEngine);
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
        painter->drawText(20, 40, "Ksl::ChartEngine ERROR: NON NUMERIC VALUES");
    }
    painter->restore();
}


void ChartEngine::save(const QString &fileName,
                 const QSize &size, const char *format)
{
    QImage image(size, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(QRect(QPoint(0,0),size), &painter);
    image.save(fileName, format);
}


void ChartEngine::onAppearenceChange(ChartItem *item) {
    Q_UNUSED(item)
    emit changed(this);
}


void ChartEngine::onDataChange(ChartItem *item) {
    item->scale()->rescale();
    emit changed(this);
}


QString ChartEngine::name() const {
    KSL_PUBLIC(const ChartEngine);
    return m->name;
}


bool ChartEngine::showName() const {
    KSL_PUBLIC(const ChartEngine);
    return m->showName;
}


QColor ChartEngine::nameColor() const {
    KSL_PUBLIC(const ChartEngine);
    return m->nameColor;
}


void ChartEngine::setName(const QString &name) {
    KSL_PUBLIC(ChartEngine);
    if (m->name != name) {
        m->name = name;
        emit changed(this);
    }
}


void ChartEngine::setShowName(bool showName) {
    KSL_PUBLIC(ChartEngine);
    if (m->showName != showName) {
        m->showName = showName;
        emit changed(this);
    }
}


void ChartEngine::setNameColor(const QColor &color) {
    KSL_PUBLIC(ChartEngine);
    if (m->nameColor != color) {
        m->nameColor = color;
        emit changed(this);
    }
}

KSL_END_NAMESPACE
