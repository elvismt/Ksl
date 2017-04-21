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

#define  KSL_GET_PUBLIC(Class,Instance) \
    static_cast<Class*>((Instance)->__public__())

#define  KSL_PRIVATE(Class) \
    auto m = KSL_GET_PUBLIC(Class,this)

namespace ksl {

// forward declaration
class Object;

class ObjectPrivate
{
public:

    ObjectPrivate(Object *publ)
        : __publicInstance__(publ) {}

    virtual ~ObjectPrivate() {}

    Object* __public__() const {
        return __publicInstance__;
    }

protected:

    Object *const __publicInstance__;
};
}
