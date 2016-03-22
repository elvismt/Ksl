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

#include <Ksl/MultiLinearRegr_p.h>

namespace Ksl {

MultiLinearRegr::MultiLinearRegr()
    : Ksl::Object(new MultiLinearRegrPrivate(this))
{ }


MultiLinearRegr::MultiLinearRegr(const Array<2> &X, const Array<1> &y)
    : Ksl::Object(new MultiLinearRegrPrivate(this))
{
    fit(X, y);
}


MultiLinearRegr::MultiLinearRegr(const Array<2> &X, const Array<1> &y,
                                 const Array<1> &w)
    : Ksl::Object(new MultiLinearRegrPrivate(this))
{
    fit(X, y, w);
}


MultiLinearRegrPrivate::~MultiLinearRegrPrivate() {
    if (workspace)
        gsl_multifit_linear_free(workspace);
}


void MultiLinearRegr::fit(const Array<2> &X, const Array<1> &y)
{
    KSL_PUBLIC(MultiLinearRegr);
    m->N = X.rows();
    m->P = X.cols();

    if (m->workspace)
        gsl_multifit_linear_free(m->workspace);
    m->workspace = gsl_multifit_linear_alloc(m->N, m->P);
    m->X = gsl_matrix_view_array((double*) X.begin(), X.rows(), X.cols());
    m->cov = Array<2>(m->P, m->P);
    m->cov_view = gsl_matrix_view_array((double*) m->cov.begin(), m->P, m->P);
    m->y = y;
    m->y_view = gsl_vector_view_array(m->y.c_ptr(), m->y.size());
    m->a.resize(m->P);
    m->a_view = gsl_vector_view_array(m->a.c_ptr(), m->a.size());

    gsl_multifit_linear(
        &m->X.matrix, &m->y_view.vector,
        &m->a_view.vector, &m->cov_view.matrix, &m->chisq, m->workspace);
}


void MultiLinearRegr::fit(const Array<2> &X, const Array<1> &y,
                          const Array<1> &w)
{
    KSL_PUBLIC(MultiLinearRegr);
    m->N = X.rows();
    m->P = X.cols();

    if (m->workspace)
        gsl_multifit_linear_free(m->workspace);
    m->workspace = gsl_multifit_linear_alloc(m->N, m->P);
    m->X = gsl_matrix_view_array((double*) X.begin(), X.rows(), X.cols());
    m->cov = Array<2>(m->P, m->P);
    m->cov_view = gsl_matrix_view_array((double*) m->cov.begin(), m->P, m->P);
    m->y = y;
    m->y_view = gsl_vector_view_array(m->y.c_ptr(), m->y.size());
    m->a.resize(m->P);
    m->a_view = gsl_vector_view_array(m->a.c_ptr(), m->a.size());
    m->w = (w.size() == y.size()) ? w : Array<1>(m->N, 1.0);
    m->w_view = gsl_vector_view_array(m->w.c_ptr(), m->w.size());

    gsl_multifit_wlinear(
        &m->X.matrix, &m->w_view.vector, &m->y_view.vector,
        &m->a_view.vector, &m->cov_view.matrix, &m->chisq, m->workspace);
}


Array<1> MultiLinearRegr::result() const {
    KSL_PUBLIC(const MultiLinearRegr);
    return m->a;
}


Array<2> MultiLinearRegr::covariance() const {
    KSL_PUBLIC(const MultiLinearRegr);
    return m->cov;
}

} // namespace Ksl
