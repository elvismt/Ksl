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

#include <Ksl/ChartLabel_p.h>
#include <Ksl/ChartScale.h>

KSL_BEGIN_NAMESPACE

ChartLabel::ChartLabel(const QString &text, double x, double y,
                       const QPen &pen, const QBrush &brush,
                       QObject *parent)
   : ChartItem(new ChartLabelPrivate(this, text, pen, brush), parent)
{
   KSL_PUBLIC(ChartLabel);
   m->x = x;
   m->y = y;
}

QRect ChartLabel::chartRect() const {
   KSL_PUBLIC(const ChartLabel);
   if (m->scale)
      return QRect(m->scale->map(QPointF(m->x, m->y)), QSize(0,0));
   return QRect();
}
   
QRectF ChartLabel::dataRect() const {
   KSL_PUBLIC(const ChartLabel);
   return QRectF(m->x, m->y, 0.0, 0.0);
}

void ChartLabel::setText(const QString &text) {
   KSL_PUBLIC(ChartLabel);
   m->text = text;
}

void ChartLabel::setPos(double x, double y) {
   KSL_PUBLIC(ChartLabel);
   m->x = x;
   m->y = y;
}

void ChartLabel::paint(QPainter *painter) {
   KSL_PUBLIC(ChartLabel);
   painter->setRenderHint(QPainter::Antialiasing, false);
   painter->setPen(m->pen);
   painter->setBrush(m->brush);

   if (m->paintRect) {
      auto fontMetrics = painter->fontMetrics();
      auto pos = m->scale->map(QPointF(m->x, m->y));
      int txtHei = fontMetrics.height();
      int txtWid = fontMetrics.width(m->text);
      painter->drawRect(pos.x(), pos.y()-txtHei-6, txtWid+6, txtHei+6);
      painter->drawText(pos.x()+3, pos.y()-fontMetrics.descent()-3, m->text);
   }
   else
      painter->drawText(m->scale->map(QPointF(m->x, m->y)), m->text);
}

KSL_END_NAMESPACE

