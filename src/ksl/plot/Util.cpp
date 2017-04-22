/*
 * Copyright (C) 2017  Elvis Teixeira
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

#include <ksl/plot/Util.h>

namespace ksl {
namespace plot {
namespace Util {

QColor parseColor(char c) {
    switch (c) {
        case 'r': return Qt::red;
        case 'g': return Qt::green;
        case 'b': return Qt::blue;
        case 'k': return Qt::black;
        case 'w': return Qt::white;
    }
    return Qt::black;
}
}}}
