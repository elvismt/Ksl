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

#ifndef QSL_OBJECT_PRIVATE_H
#define QSL_OBJECT_PRIVATE_H

#include <QSL/Global.h>

#define QSL_GET_PUBLIC(Class, instance) \
    (static_cast<Class*>((instance)->getPublic()))

#define QSL_PRIVATE(Class) \
    auto m = QSL_GET_PUBLIC(Class, this)

QSL_BEGIN_NAMESPACE

// forward declaration
class Object;

class QSL_API ObjectPrivate
{
public:

    ObjectPrivate(Object *publ)
        : mPubl(publ)
    { }

    virtual ~ObjectPrivate() {
        // nothing to do
    }

    Object* getPublic() const {
        return mPubl;
    }

protected:

    Object *const mPubl;
};

QSL_END_NAMESPACE

#endif // QSL_OBJECT_PRIVATE_H
