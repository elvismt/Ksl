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

#ifndef QSL_RANDOMPRIVATE_H
#define QSL_RANDOMPRIVATE_H

#include <QSL/Random.h>
#include <chrono>
#include <random>

QSL_BEGIN_NAMESPACE

class RandomPrivate
    : public ObjectPrivate
{
public:

    RandomPrivate(Random *publ)
        : ObjectPrivate(publ)
        , generator(std::chrono::system_clock::now().time_since_epoch().count())
        , rangeWidth(std::minstd_rand0::max() - std::minstd_rand0::min())
        , rangeMin(std::minstd_rand0::min())
    { }


    std::minstd_rand0 generator;
    quint64 rangeWidth;
    quint64 rangeMin;


    inline quint64 nextUint() {
        return generator();
    }

    inline quint64 nextUint(quint64 max) {
        return qRound(qreal(generator() - rangeMin)/qreal(rangeWidth) * qreal(max));
    }

    inline qreal nextFloat(qreal max) {
        return qreal(generator() - rangeMin)/qreal(rangeWidth) * max;
    }
};

QSL_END_NAMESPACE

#endif // QSL_RANDOMPRIVATE_H
