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

#include <Ksl/TextLabelPlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

TextLabelPlot::TextLabelPlot(const QString &text, const QPointF &pos,
                             const QPen &pen, float rotation, QObject *parent)
    : FigureItem(new TextLabelPlotPrivate(this), text, parent)
{
    KSL_PUBLIC(TextLabelPlot);
    m->text = text;
    m->pos = pos;
    m->pen = pen;
    m->rotation = -rotation;
    m->rescalable = false;
}


void TextLabelPlot::setPen(const QPen &pen) {
    KSL_PUBLIC(TextLabelPlot);
    if (m->pen != pen) {
        m->pen = pen;
        emit appearenceChanged(this);
    }
}


void TextLabelPlot::paint(QPainter *painter) {
    KSL_PUBLIC(TextLabelPlot);

    QPoint figurePos = m->scale->map(m->pos);
    painter->setPen(m->pen);

    if (m->rotation != 0.0) {
        painter->save();
        painter->translate(figurePos);
        figurePos = QPoint(0,0);
        painter->rotate(m->rotation);
    }

    painter->drawText(figurePos, m->text);

    if (m->rotation != 0.0) {
        painter->restore();
    }
}

} // namespace Ksl
