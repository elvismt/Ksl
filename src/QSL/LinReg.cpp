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

#include <QSL/LinReg.h>

QSL_BEGIN_NAMESPACE


// Adapted from GSL, The GNU scientific library.
void LinReg::solve()
{
    double gx = 0, gy = 0, m_dx2 = 0, m_dxdy = 0;

      size_t i;
      size_t n = m_x.size();

      for (i = 0; i < n; i++)
        {
          gx += (m_x[i] - gx) / (i + 1.0);
          gy += (m_y[i] - gy) / (i + 1.0);
        }

      for (i = 0; i < n; i++)
        {
          const double dx = m_x[i] - gx;
          const double dy = m_y[i] - gy;

          m_dx2 += (dx * dx - m_dx2) / (i + 1.0);
          m_dxdy += (dx * dy - m_dxdy) / (i + 1.0);
        }

      /* In terms of y = a + b x */

      {
        double s2 = 0, d2 = 0;
        double b = m_dxdy / m_dx2;
        double a = gy - gx * b;

        m_c0 = a;
        m_c1 = b;

        /* Compute chi^2 = \sum (y_i - (a + b * x_i))^2 */

        for (i = 0; i < n; i++)
          {
            const double dx = m_x[i] - gx;
            const double dy = m_y[i] - gy;
            const double d = dy - b * dx;
            d2 += d * d;
          }

        s2 = d2 / (n - 2.0);        /* chisq per degree of freedom */

        m_cov00 = s2 * (1.0 / n) * (1 + gx * gx / m_dx2);
        m_cov11 = s2 * 1.0 / (n * m_dx2);

        m_cov01 = s2 * (-gx) / (n * m_dx2);

        m_chisqr = d2;
      }
}

QSL_END_NAMESPACE
