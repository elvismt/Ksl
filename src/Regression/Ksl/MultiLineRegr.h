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

#ifndef KSL_MULTILINEARREGR_H
#define KSL_MULTILINEARREGR_H

#include <Ksl/Csv.h>

namespace Ksl {

class KSL_EXPORT MultiLineRegr
        : public Ksl::Object
{
public:

    MultiLineRegr();

    MultiLineRegr(const Array<2> &X, const Array<1> &y);

    MultiLineRegr(const Array<2> &X, const Array<1> &y, const Array<1> &w);

    void fit(const Array<2> &X, const Array<1> &y);

    void fit(const Array<2> &X, const Array<1> &y, const Array<1> &w);

    Array<1> result() const;

    Array<2> covariance() const;
};

} // namespace Ksl

#endif // KSL_MULTILINEARREGR_H
