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

#ifndef KSL_MATH_H
#define KSL_MATH_H

#include <Ksl/Global.h>
#include <cmath>

KSL_BEGIN_MATH_NAMESPACE

template <typename T> inline T pow2(const T& x) { return x*x; }
template <typename T> inline T pow3(const T& x) { return x*x*x; }

inline double sin(double x) { return std::sin(x); }
inline double cos(double x) { return std::cos(x); }
inline double tan(double x) { return std::tan(x); }
inline double log(double x) { return std::log(x); }
inline double exp(double x) { return std::exp(x); }

extern const double Pi;
extern const double E;

KSL_END_MATH_NAMESPACE

#endif // KSL_MATH_H
