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

#ifndef QSL_LINREG_H
#define QSL_LINREG_H

#include <QSL/Array1D.h>

QSL_BEGIN_NAMESPACE

class QSL_API LinReg
{
public:

    LinReg()
    { }

    LinReg(const array1d &x, const array1d &y)
        : m_x(x)
        , m_y(y)
    { }

    void set_data(const array1d &x, const array1d &y) {
        m_x = x;
        m_y = y;
    }

    array1d solution() const {
        return std::move(array1d{
            m_c0, m_c1,
            m_cov00, m_cov01, m_cov11,
            m_chisqr
        });
    }

    void solve();

private:

    array1d m_x;
    array1d m_y;
    double m_chisqr;
    double m_c0, m_c1;
    double m_cov00, m_cov01, m_cov11;
};

inline array1d linreg(const array1d &x, const array1d &y) {
    LinReg lr(x, y);
    lr.solve();
    return std::move(lr.solution());
}

QSL_END_NAMESPACE

#endif // QSL_LINREG_H
