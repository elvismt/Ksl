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

#ifndef KSL_LINREGR_P_H
#define KSL_LINREGR_P_H

#include <Ksl/LinRegr.h>

namespace Ksl {

class LinRegrPrivate
    : public Ksl::ObjectPrivate
{
public:

    LinRegrPrivate(LinRegr *publ)
        : Ksl::ObjectPrivate(publ)
        , c0(0.0), c1(0.0)
        , cov_00(0.0), cov_01(0.0), cov_11(0.0)
        , sumsq(0.0)
    { }

    // ! BEGIN GSL CODE
    static void gsl_fit_linear(const double *x, const double *y, const size_t n,
                    double *c0, double *c1,
                    double *cov_00, double *cov_01, double *cov_11,
                    double *sumsq);
    // ! END GSL CODE

    double c0, c1;
    double cov_00, cov_01, cov_11;
    double sumsq;
    Array<1> x;
    Array<1> y;
};

} // namespace Ksl

#endif // KSL_LINREGR_P_H
