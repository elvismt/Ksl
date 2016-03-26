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

#include <Ksl/MultiLineRegr_p.h>

namespace Ksl {

MultiLineRegr::MultiLineRegr()
    : Ksl::Object(new MultiLineRegrPrivate(this))
{ }


MultiLineRegr::MultiLineRegr(const Array<2> &X, const Array<1> &y)
    : Ksl::Object(new MultiLineRegrPrivate(this))
{
    fit(X, y);
}


MultiLineRegr::MultiLineRegr(const Array<2> &X, const Array<1> &y,
                             const Array<1> &w)
    : Ksl::Object(new MultiLineRegrPrivate(this))
{
    fit(X, y, w);
}


MultiLineRegr::MultiLineRegr(const Csv &csv, const Array<1,int> &columns,
                             const Array<1> &y)
    : Ksl::Object(new MultiLineRegrPrivate(this))
{
    fit(csv, columns, y);
}


MultiLineRegr::MultiLineRegr(const Csv &csv, const Array<1,int> &columns,
                             int yCol)
    : Ksl::Object(new MultiLineRegrPrivate(this))
{
    fit(csv, columns, yCol);
}


MultiLineRegrPrivate::~MultiLineRegrPrivate() {
    if (workspace)
        gsl_multifit_linear_free(workspace);
}


Array<1> MultiLineRegr::result() const {
    KSL_PUBLIC(const MultiLineRegr);
    return m->a;
}


Array<2> MultiLineRegr::covariance() const {
    KSL_PUBLIC(const MultiLineRegr);
    return m->cov;
}


void MultiLineRegr::fit(const Array<2> &X, const Array<1> &y)
{
    KSL_PUBLIC(MultiLineRegr);
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


void MultiLineRegr::fit(const Array<2> &X, const Array<1> &y,
                        const Array<1> &w)
{
    KSL_PUBLIC(MultiLineRegr);
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


void MultiLineRegr::fit(const Csv &csv, const Array<1,int> &columns,
                        const Array<1> &y)
{
    // File containing data
    auto DATA = csv.matrix();
    int N = DATA.rows();

    // fill matrix with params
    Array<2> X(N, columns.size()+1);
    X.setcol(0, 1.0);
    for (int j=0; j<columns.size(); ++j) {
        X.coltocol(j+1, DATA, columns[j]);
    }

    // Perform regression
    fit(X, y);
}


void MultiLineRegr::fit(const Csv &csv, const Array<1,int> &columns, int yCol)
{
    // File containing data
    auto DATA = csv.matrix();
    int N = DATA.rows();
    auto Y = getcol(DATA, yCol);

    // fill matrix with params
    Array<2> X(N, columns.size()+1);
    X.setcol(0, 1.0);
    for (int j=0; j<columns.size(); ++j) {
        X.coltocol(j+1, DATA, columns[j]);
    }

    // Perform regression
    fit(X, Y);
}


double MultiLineRegr::model(int idx) const {
    KSL_PUBLIC(MultiLineRegr);

    double yk = m->a[0];
    for (int l=1; l<m->a.size(); l++)
        yk += m->a[l] * gsl_matrix_get(&m->X.matrix, idx, l);
    return yk;
}

} // namespace Ksl
