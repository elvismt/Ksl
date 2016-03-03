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

#ifndef KSL_FIGURESCALE_P_H
#define KSL_FIGURESCALE_P_H

#include <Ksl/FigureScale.h>

namespace Ksl {

class FigureScalePrivate
    : public Ksl::ObjectPrivate
{
public:

    FigureScalePrivate(FigureScale *publ)
        : Ksl::ObjectPrivate(publ)
        , figure(nullptr)
        , visible(true)
        , name("scale")
    { }

    Figure *figure;
    bool visible;
    QString name;
    QList<FigureItem*> itemList;
};

} // namespace Ksl 

#endif // KSL_FIGURESCALE_P_H
