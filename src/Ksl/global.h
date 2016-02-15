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

#ifndef KSL_GLOBAL_H
#define KSL_GLOBAL_H

#include <QString>
#include <QList>

#define KSL_BEGIN_NAMESPACE namespace Ksl {
#define KSL_END_NAMESPACE } // namespace Ksl

#define KSL_EXPORT
#define KSL_CPP2011

#ifndef KSL_CPP2011
#define nullptr 0
#endif

KSL_BEGIN_NAMESPACE
template <typename T> inline T pow2(const T &x) { return x*x; }
template <typename T> inline T pow3(const T &x) { return x*x*x; }
KSL_END_NAMESPACE

#endif // KSL_GLOBAL_H
