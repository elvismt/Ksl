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

#include <Ksl/LineRegr_p.h>

namespace Ksl {

LineRegr::LineRegr(const Array<1> &x, const Array<1> &y)
    : Ksl::Object(new LineRegrPrivate(this))
{
    KSL_PUBLIC(LineRegr);
    m->x = x;
    m->y = y;
}


Array<1> LineRegr::result() const {
    KSL_PUBLIC(const LineRegr);
    Array<1> ret(6);
    ret[0] = m->c0;
    ret[1] = m->c1;
    ret[2] = m->cov_00;
    ret[3] = m->cov_01;
    ret[4] = m->cov_11;
    ret[5] = m->sumsq;
    return std::move(ret);
}


void LineRegr::solve() {
    KSL_PUBLIC(LineRegr);
    LineRegrPrivate::gsl_fit_linear(
        m->x.begin(), m->y.begin(), qMin(m->x.size(), m->y.size()),
        &m->c0, &m->c1, &m->cov_00, &m->cov_01, &m->cov_11, &m->sumsq);
}


// ! BEGIN GSL_CODE
void
LineRegrPrivate::gsl_fit_linear (const double *x,
                                const double *y,
                                const size_t n,
                                double *c0, double *c1,
                                double *cov_00, double *cov_01, double *cov_11,
                                double *sumsq)
{
  double m_x = 0, m_y = 0, m_dx2 = 0, m_dxdy = 0;

  size_t i;

  for (i = 0; i < n; i++)
    {
      m_x += (x[i] - m_x) / (i + 1.0);
      m_y += (y[i] - m_y) / (i + 1.0);
    }

  for (i = 0; i < n; i++)
    {
      const double dx = x[i] - m_x;
      const double dy = y[i] - m_y;

      m_dx2 += (dx * dx - m_dx2) / (i + 1.0);
      m_dxdy += (dx * dy - m_dxdy) / (i + 1.0);
    }

  /* In terms of y = a + b x */

  {
    double s2 = 0, d2 = 0;
    double b = m_dxdy / m_dx2;
    double a = m_y - m_x * b;

    *c0 = a;
    *c1 = b;

    /* Compute chi^2 = \sum (y_i - (a + b * x_i))^2 */

    for (i = 0; i < n; i++)
      {
        const double dx = x[i] - m_x;
        const double dy = y[i] - m_y;
        const double d = dy - b * dx;
        d2 += d * d;
      }

    s2 = d2 / (n - 2.0);        /* chisq per degree of freedom */

    *cov_00 = s2 * (1.0 / n) * (1 + m_x * m_x / m_dx2);
    *cov_11 = s2 * 1.0 / (n * m_dx2);

    *cov_01 = s2 * (-m_x) / (n * m_dx2);

    *sumsq = d2;
  }
}
// ! END GSL CODE

} // namespace Ksl
