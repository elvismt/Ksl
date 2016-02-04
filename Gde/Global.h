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

#ifndef GDE_GLOBAL_H
#define GDE_GLOBAL_H

#include <cstdint>
#include <string>

#define GDE_BEGIN_NAMESPACE namespace Gde {
#define GDE_END_NAMESPACE } // namespace Gde

#define GDE_EXPORT

GDE_BEGIN_NAMESPACE
typedef double real;
typedef int32_t    integ;
typedef size_t     index;
GDE_END_NAMESPACE

#endif // GDE_GLOBAL_H
