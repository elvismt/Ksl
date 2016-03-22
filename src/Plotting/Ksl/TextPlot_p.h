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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the public Ksl API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed. Do not include it
//
// We mean it.
//

#ifndef KSL_TEXTLABELPLOT_P_H
#define KSL_TEXTLABELPLOT_P_H

#include <Ksl/TextPlot.h>
#include <Ksl/FigureItem_p.h>

namespace Ksl {

class TextPlotPrivate
    : public FigureItemPrivate
{
public:

    TextPlotPrivate(TextPlot *publ)
        : FigureItemPrivate(publ)
    { }


    QString text;
    QPointF pos;
    QPen pen;
    float rotation;
};

} // namespace Ksl

#endif // KSL_TEXTLABELPLOT_P_H
