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
#include <gsl/gsl_fit.h>

namespace Ksl {

LineRegr::LineRegr()
    : Ksl::Object(new LineRegrPrivate(this))
{ }


LineRegr::LineRegr(const Array<1> &x, const Array<1> &y)
    : Ksl::Object(new LineRegrPrivate(this))
{
    fit(x, y);
}


LineRegr::LineRegr(const Array<1> &x, const Array<1> &y,
                   const Array<1> &w)
    : Ksl::Object(new LineRegrPrivate(this))
{
    fit(x, y, w);
}


Array<1> LineRegr::result() const {
    KSL_PUBLIC(const LineRegr);
    return m->result;
}


void LineRegr::fit(const Array<1> &x, const Array<1> &y) {
    KSL_PUBLIC(LineRegr);
    m->x = x;
    m->y = y;
    gsl_fit_linear(
        m->x.c_ptr(), 1, m->y.c_ptr(), 1, qMin(m->x.size(), m->y.size()),
        &m->result[0], &m->result[1], &m->result[2], &m->result[3],
        &m->result[4], &m->result[5]);
}


void LineRegr::fit(const Array<1> &x, const Array<1> &y,
                   const Array<1> &w)
{
    KSL_PUBLIC(LineRegr);
    m->x = x;
    m->y = y;
    gsl_fit_wlinear(
        m->x.c_ptr(), 1, w.c_ptr(), 1, m->y.c_ptr(), 1, qMin(m->x.size(), m->y.size()),
        &m->result[0], &m->result[1], &m->result[2], &m->result[3],
        &m->result[4], &m->result[5]);
}

} // namespace Ksl
