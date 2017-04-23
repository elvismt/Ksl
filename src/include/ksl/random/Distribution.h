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

#pragma once
#include <ksl/Object.h>
#include <QVector>
#include <vector>

namespace ksl {
namespace random {

class Distribution: public ksl::Object
{
public:

    virtual double generate() const = 0;

    double operator() () const {
        return generate();
    }

    QVector<double> qVec(int64_t size) const {
        QVector<double> v(size);
        for (auto &x : v)
            x = generate();
        return std::move(v);
    }

    QVector<double> operator() (int64_t size) const {
        return std::move(qVec(size));
    }

    std::vector<double> vec(int64_t size) const {
        std::vector<double> v(size);
        for (auto &x : v)
            x = generate();
        return std::move(v);
    }

protected:

    Distribution(ksl::ObjectPrivate *priv)
        : ksl::Object(priv) {}
};
}}
