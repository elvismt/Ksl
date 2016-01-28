/*
 * Copyright (C) 2016  Elvis M.Teixeira
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

#ifndef QSL_LINEARSCALE_H
#define QSL_LINEARSCALE_H

#include <QSL/FigureScale.h>
#include <QSL/ChartAxis.h>

QSL_BEGIN_NAMESPACE

class QSL_API LinearScale
    : public FigureScale
{
public:

    typedef QList<ChartAxis*> AxisList;


    LinearScale(const QString &name="LinearScale");

    AxisList& axisList();
    const AxisList& axisList() const;
    ChartAxis* axis(ChartAxis::Position position) const;
    ChartAxis* axis(const QString &label) const;

    virtual QRect figureRect() const;
    virtual QRectF dataRect() const;

    virtual QPoint map(const QPointF &p) const;
    virtual QPointF unmap(const QPoint &p) const;

    virtual void rescale();


protected:

    virtual void paint(const QRect &figureRect, QPainter *painter);

    virtual void setFigure(Figure *figure);

    LinearScale(ObjectPrivate *priv)
        : FigureScale(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_LINEARSCALE_H
