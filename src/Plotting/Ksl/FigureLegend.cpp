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

#include <Ksl/FigureLegend_p.h>
#include <Ksl/Figure.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

FigureLegend::FigureLegend(QObject *parent)
    : FigureItem(new FigureLegendPrivate(this), "legend", parent)
{ }


void FigureLegend::setPosition(PositionPolicy policy) {
    KSL_PUBLIC(FigureLegend);
    m->positionPolicy = policy;
}


void FigureLegend::setPosition(double x, double y) {
    KSL_PUBLIC(FigureLegend);
    m->positionPolicy = CustomPosition;
    m->position.setX(x);
    m->position.setY(y);
}


void FigureLegend::setPosition(const QPointF &pos) {
    KSL_PUBLIC(FigureLegend);
    m->positionPolicy = CustomPosition;
    m->position = pos;
}


void FigureLegendPrivate::evalRect(const QFontMetrics &fm) {
    QRect scaleRect = scale->figureRect();
    int x, y;
    int width = 0;
    int height = 0;
    int txtHeight = fm.height();
    int txtWidth;

    for (auto scale : figure->scaleList()) {
        for (auto item : scale->itemList()) {

            if (!item->visible() ||
                !item->hasThumb() ||
                item->name().isEmpty())
                    continue;

            height += txtHeight;
            txtWidth = fm.width(item->name());
            if (txtWidth > width)
                width = txtWidth;
        }
    }

    if (height == 0) {
        hasEntries = false;
        return;
    } else {
        hasEntries = true;
    }

    width = width + 45;
    height = height + fm.descent() + 3;

    switch (positionPolicy) {
        case FigureLegend::CustomPosition: {
            QPoint pos = scale->map(position);
            x = pos.x();
            y = pos.y();
            break;
        }
        case FigureLegend::BottomLeftInside:
            x = scaleRect.right() - width - 55;
            y = scaleRect.bottom() - rect.height() - 10;
            break;
        case FigureLegend::Below:
            x = (scaleRect.left() + scaleRect.right() - rect.width()) / 2;
            y = scaleRect.bottom() + 3*txtHeight;
            break;
        default:
            x = scaleRect.right() - width - 10;
            y = scaleRect.top() + 10;
            break;
    }
    rect = QRect(x, y, width, height);
}


void FigureLegend::paint(QPainter *painter) {
    KSL_PUBLIC(FigureLegend);

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(m->pen);
    painter->setBrush(m->brush);

    QFontMetrics fm = painter->fontMetrics();
    m->evalRect(fm);
    if (m->hasEntries == false) {
        return;
    }

    painter->drawRect(m->rect);

    int txtHeight = fm.height();
    int x = m->rect.left();
    int y = m->rect.top() + txtHeight;

    for (auto scale : m->figure->scaleList()) {
        if (m->rect.height() == 0)
            break;

        for (auto item : scale->itemList())
        {
            if (!item->visible() ||
                !item->hasThumb() ||
                item->name().isEmpty())
                    continue;

            item->paintThumb(QPoint(x+20, y-txtHeight/3), painter);

            painter->setPen(m->pen);
            painter->setBrush(m->brush);
            painter->drawText(x+40, y, item->name());
            y += txtHeight;
        }
    }
}

} // namespace Ksl
