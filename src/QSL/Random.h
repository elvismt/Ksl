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


#ifndef QSL_RANDOM_H
#define QSL_RANDOM_H

#include <QSL/Object.h>

QSL_BEGIN_NAMESPACE

class QSL_API Random
    : public QSL::Object
{
public:

    Random();

    quint64 nextUint();

    quint64 nextUint(quint64 max);

    qreal nextFloat(qreal max=1.0);
};

QSL_END_NAMESPACE

#endif // QSL_RANDOM_H
