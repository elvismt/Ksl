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

#include <QSL/LinearRegressionPrivate.h>

QSL_BEGIN_NAMESPACE

LinearRegression::LinearRegression()
    : QSL::Object(new LinearRegressionPrivate(this))
{ }


LinearRegression::LinearRegression(const Array1D<double> &x,
                                   const Array1D<double> &y)
    : QSL::Object(new LinearRegressionPrivate(this, x, y))
{ }


void LinearRegression::setData(const Array1D<double> &x,
                               const Array1D<double> &y)
{
    QSL_PUBLIC(LinearRegression);
    m->x = x;
    m->y = y;
}


void LinearRegression::solve() {
    QSL_PUBLIC(LinearRegression);
    gsl_fit_linear(
         m->x.begin(), 1,
         m->y.begin(), 1,
         m->x.size(),
         &m->par1, &m->par2,
         &m->cov00, &m->cov01, &m->cov11,
         &m->chiSqr
    );
}


Array1D<double> LinearRegression::solution() const {
    QSL_PUBLIC(const LinearRegression);
   return std::move(Array1D<double>{
        m->par1, m->par2,
        m->cov00, m->cov01, m->cov11,
        m->chiSqr
   });
}

QSL_END_NAMESPACE
