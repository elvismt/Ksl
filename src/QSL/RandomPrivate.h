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

#ifndef QSL_RANDOM_PRIVATE_H
#define QSL_RANDOM_PRIVATE_H

#include <QSL/Random.h>
#include <QTime>
#include <random>

QSL_BEGIN_NAMESPACE

class RandomPrivate
    : public ObjectPrivate
{
public:

    RandomPrivate(Random *publ)
        : ObjectPrivate(publ)
        , device()
        , intGenerator(QTime(0,0,0).secsTo(QTime::currentTime()))
        , intRangeWidth(std::minstd_rand0::max() - std::minstd_rand0::min())
        , intRangeMin(std::minstd_rand0::min())
        , realGenerator(device())
        , realRangeWidth(std::mt19937::max() - std::mt19937::min())
        , realRangeMin(std::mt19937::min())
    { }


    std::random_device device;
    std::minstd_rand0 intGenerator;
    quint64 intRangeWidth;
    quint64 intRangeMin;

    std::mt19937 realGenerator;
    double realRangeWidth;
    double realRangeMin;



    inline quint64 nextUint() {
        return intGenerator();
    }

    inline quint64 nextUint(quint64 max) {
        // TODO: There must be a better way
        return qRound(qreal(intGenerator() - intRangeMin)/qreal(intRangeWidth) * qreal(max));
    }

    inline double nextFloat() {
        return realGenerator();
    }

    inline double nextFloat(double max) {
        // TODO: Check if there is a better way
        return (realGenerator() - realRangeMin)/realRangeWidth * max;
    }
};

QSL_END_NAMESPACE

#endif // QSL_RANDOM_PRIVATE_H
