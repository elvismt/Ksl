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

#include <QObject>

#define KSL_BEGIN_NAMESPACE namespace Ksl {
#define KSL_END_NAMESPACE } // namespace Ksl
#define KSL_BEGIN_MATH_NAMESPACE namespace Ksl { namespace Math {
#define KSL_END_MATH_NAMESPACE }} // namespace Ksl::Math
#define KSL_BEGIN_PLOT_NAMESPACE namespace Ksl { namespace Plot {
#define KSL_END_PLOT_NAMESPACE }} // namespace Ksl::Plot

#define KSL_EXPORT

#endif // KSL_GLOBAL_H
