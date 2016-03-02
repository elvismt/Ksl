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

#ifndef KSL_REGRESSION_LINEAR_H
#define KSL_REGRESSION_LINEAR_H

#include <Ksl/Object.h>
#include <Ksl/Array.h>

namespace Ksl {
namespace Regression {

class KSL_EXPORT LinRegr
        : public Ksl::Object
{
public:

    LinRegr(const Array<1> x, const Array<1> &y);

    Array<1> result() const;

    void solve();
};

}} // namespace Ksl::Regression

#endif // KSL_REGRESSION_LINEAR_H
