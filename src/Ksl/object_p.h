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

#ifndef KSL_OBJECT_P_H
#define KSL_OBJECT_P_H

#include <Ksl/global.h>

#define KSL_GET_PUBLIC(Class, instance) \
    (static_cast<Class*>((instance)->getPublic()))

#define KSL_PRIVATE(Class) \
    Class *m = KSL_GET_PUBLIC(Class, this)

// forward declaration
class KslObject;

class KSL_EXPORT KslObjectPrivate
{
public:

    KslObjectPrivate(KslObject *publ)
        : m_publ(publ)
    { }

    virtual ~KslObjectPrivate()
    { }

    inline KslObject* getPublic() const {
        return m_publ;
    }

protected:

    KslObject *const m_publ;
};

#endif // KSL_OBJECT_P_H