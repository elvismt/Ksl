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

#ifndef KSL_OBJECT_H
#define KSL_OBJECT_H

#include <Ksl/object_p.h>

#define KSL_GET_PRIVATE(Class, instance) \
    (static_cast<Class##Private*>((instance)->getPrivate()))

#define KSL_PUBLIC(Class) \
    Class##Private *m = KSL_GET_PRIVATE(Class, this)


class KSL_EXPORT KslObject
{
public:

    virtual ~KslObject() {
        if (m_priv != 0) {
            delete m_priv;
        }
    }

    inline KslObjectPrivate* getPrivate() const {
        return m_priv;
    }

protected:

    KslObject(KslObjectPrivate *priv)
        : m_priv(priv)
    { }

    KslObjectPrivate *const m_priv;
};

#endif // KSL_OBJECT_H