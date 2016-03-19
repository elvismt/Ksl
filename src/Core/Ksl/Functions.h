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

#ifndef KSL_FUNCTIONS_H
#define KSL_FUNCTIONS_H

#include <Ksl/Array.h>

namespace Ksl {

inline double poly(const Array<1> &a, double x) {
    double f = 0.0;
    double xn = 1.0;
    for (auto ai : a) {
        f += ai * xn;
        xn *= x;
    }
    return f;
}

} // namespace Ksl

#endif // KSL_FUNCTIONS_H
