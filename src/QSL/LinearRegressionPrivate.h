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

#ifndef QSL_LINEARREGRESSION_PRIVATE_H
#define QSL_LINEARREGRESSION_PRIVATE_H

#include <QSL/LinearRegression.h>
#include <gsl/gsl_fit.h>

QSL_BEGIN_NAMESPACE

class LinearRegressionPrivate
    : public QSL::ObjectPrivate
{
public:

    LinearRegressionPrivate(LinearRegression *publ)
        : QSL::ObjectPrivate(publ)
    { }

    LinearRegressionPrivate(LinearRegression *publ,
                            const Array1D<double> &ix,
                            const Array1D<double> &iy)
        : QSL::ObjectPrivate(publ)
        , x(ix)
        , y(iy)
    { }


    Array1D<double> x;
    Array1D<double> y;

    double chiSqr;
    double par1, par2;
    double cov00, cov01, cov11;
};

QSL_END_NAMESPACE

#endif // QSL_LINEARREGRESSION_PRIVATE_H
