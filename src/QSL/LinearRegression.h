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

#ifndef QSL_LINEARREGRESSION_H
#define QSL_LINEARREGRESSION_H

#include <QSL/Object.h>
#include <QSL/Array1D.h>

QSL_BEGIN_NAMESPACE

class QSL_API LinearRegression
    : public QSL::Object
{
public:

   LinearRegression();

   LinearRegression(const Array1D<double> &x,
                    const Array1D<double> &y);

   void setData(const Array1D<double> &x,
                const Array1D<double> &y);

   void solve();

   Array1D<double> solution() const;
};

QSL_END_NAMESPACE

#endif // QSL_LINEARREGRESSION_H
