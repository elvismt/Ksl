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

#ifndef KSL_MULTILINEARREGR_P_H
#define KSL_MULTILINEARREGR_P_H

#include <Ksl/MultiLinearRegr.h>
#include <gsl/gsl_multifit.h>


namespace Ksl {

class MultiLinearRegrPrivate
    : public ObjectPrivate
{
public:

    MultiLinearRegrPrivate(MultiLinearRegr *publ)
        : ObjectPrivate(publ)
        , valid(false)
    { }

    ~MultiLinearRegrPrivate();


    bool valid;

    size_t N, M;
    gsl_multifit_linear_workspace *workspace;
    gsl_matrix *X;
    gsl_matrix *cov;

    Array<1> a;
    Array<1> w;
    Array<1> x;
    Array<1> y;
    gsl_vector_view a_view;
    gsl_vector_view w_view;
    gsl_vector_view x_view;
    gsl_vector_view y_view;
};

} // namespace Ksl

#endif // KSL_MULTILINEARREGR_P_H
