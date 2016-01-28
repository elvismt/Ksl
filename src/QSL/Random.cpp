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


#include <QSL/RandomPrivate.h>

QSL_BEGIN_NAMESPACE

Random::Random()
    : Object(new RandomPrivate(this))
{ }


quint64 Random::nextUint() {
    QSL_PUBLIC(Random);
    return m->nextUint();
}


quint64 Random::nextUint(quint64 max) {
    QSL_PUBLIC(Random);
    return m->nextUintRange(max);
}


qreal Random::nextFloat(qreal max) {
    QSL_PUBLIC(Random);
    return m->nextFloat(max);
}

QSL_END_NAMESPACE
