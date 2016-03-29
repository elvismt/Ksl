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


void FigureLegend::paint(QPainter *painter) {
    KSL_PUBLIC(FigureLegend);

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(m->pen);
    painter->setBrush(m->brush);

}

} // namespace Ksl
