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

#ifndef KSL_PLOT_H
#define KSL_PLOT_H

#include <Ksl/BasePlot.h>

namespace Ksl {

class KSL_EXPORT Plot
    : public BasePlot
{
    Q_OBJECT

public:

    Plot(const Array<1> &x, const Array<1> &y,
         const char *style="kor", const QString &name="",
         QObject *parent=0);


    virtual void setData(const Array<1> &x, const Array<1> &y);
};

} // namespace Ksl

#endif // KSL_PLOT_H
