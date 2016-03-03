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

// A shortcut for fast integer powers
template <typename T> inline T pow2(const T& x) { return x*x; }
template <typename T> inline T pow3(const T& x) { return x*x*x; }
template <typename T> inline T pow4(const T& x) { T p2=x*x; return p2*p2; }
template <typename T> inline T pow5(const T& x) { T p2=x*x; return p2*p2*x; }
template <typename T> inline T pow6(const T& x) { T p2=x*x; return p2*p2*p2; }
template <typename T> inline T pow7(const T& x) { T p2=x*x; return p2*p2*p2*x; }
template <typename T> inline T pow8(const T& x) { T p2=x*x; T p4=p2*p2; return p4*p4; }
template <typename T> inline T pow9(const T& x) { T p3=x*x*x; return p3*p3*p3; }
template <typename T> inline T pow10(const T& x) { T p2=x*x; T p4=p2*p2; return p4*p4*p2; }
template <typename T> inline T pow11(const T& x) { T p3=x*x*x; T p4=p3*x; return p4*p4*p3; }
template <typename T> inline T pow12(const T& x) { T p3=x*x*x; T p6=p3*p3; return p6*p6; }


// Under some condition the compiler fails to identify the
// standard functions for functor templates, such as in applying
// Array<D,T> apply(func, array)
inline double sin(double x) { return std::sin(x); }
inline double cos(double x) { return std::cos(x); }
inline double tan(double x) { return std::tan(x); }
inline double log(double x) { return std::log(x); }
inline double log10(double x) { return std::log10(x); }
inline double exp(double x) { return std::exp(x); }
inline double asin(double x) { return std::asin(x); }
inline double acos(double x) { return std::acos(x); }
inline double atan(double x) { return std::atan(x); }


KSL_END_MATH_NAMESPACE


// Make sure the BSD library constants are present.
// Visual studio for example does not define them.
// Extracted from GSL
#ifndef M_E
#define M_E        2.71828182845904523536028747135      /* e */
#endif

#ifndef M_LOG2E
#define M_LOG2E    1.44269504088896340735992468100      /* log_2 (e) */
#endif

#ifndef M_LOG10E
#define M_LOG10E   0.43429448190325182765112891892      /* log_10 (e) */
#endif

#ifndef M_SQRT2
#define M_SQRT2    1.41421356237309504880168872421      /* sqrt(2) */
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2  0.70710678118654752440084436210      /* sqrt(1/2) */
#endif


#ifndef M_SQRT3
#define M_SQRT3    1.73205080756887729352744634151      /* sqrt(3) */
#endif

#ifndef M_PI
#define M_PI       3.14159265358979323846264338328      /* pi */
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923132169164      /* pi/2 */
#endif

#ifndef M_PI_4
#define M_PI_4     0.78539816339744830961566084582     /* pi/4 */
#endif

#ifndef M_SQRTPI
#define M_SQRTPI   1.77245385090551602729816748334      /* sqrt(pi) */
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257389615890312      /* 2/sqrt(pi) */
#endif

#ifndef M_1_PI
#define M_1_PI     0.31830988618379067153776752675      /* 1/pi */
#endif

#ifndef M_2_PI
#define M_2_PI     0.63661977236758134307553505349      /* 2/pi */
#endif

#ifndef M_LN10
#define M_LN10     2.30258509299404568401799145468      /* ln(10) */
#endif

#ifndef M_LN2
#define M_LN2      0.69314718055994530941723212146      /* ln(2) */
#endif

#ifndef M_LNPI
#define M_LNPI     1.14472988584940017414342735135      /* ln(pi) */
#endif

#ifndef M_EULER
#define M_EULER    0.57721566490153286060651209008      /* Euler constant */
#endif

#endif // KSL_MATH_H
