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

#ifndef KSL_CHARTLABEL_H
#define KSL_CHARTLABEL_H

#include <Ksl/ChartItem.h>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT ChartLabel
    : public ChartItem
{
    Q_OBJECT

public:

   ChartLabel(const QString &text, double x, double y,
              const QPen &pen=QPen(Qt::blue), const QBrush &brush=QBrush(Qt::white),
              QObject *parent=0);

   QString text() const;

   virtual QRect chartRect() const;
   
   virtual QRectF dataRect() const;

public slots:

   void setText(const QString &text);

   void setPos(double x, double y);

protected:

   virtual void paint(QPainter *painter);
};

KSL_END_NAMESPACE

#endif // KSL_CHARTLABEL_H
