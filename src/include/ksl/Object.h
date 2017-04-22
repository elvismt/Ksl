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
#include "ksl/Object_h.h"

#define  KSL_GET_PRIVATE(Class,Instance) \
    static_cast<Class##Private*>((Instance)->__private__())

#define  KSL_PUBLIC(Class) \
    auto m = KSL_GET_PRIVATE(Class,this)

namespace ksl {

class Object
{
public:

    virtual ~Object() {
        delete __privateInstance__;
    }

    ObjectPrivate* __private__() const {
        return __privateInstance__;
    }

protected:

    Object(ObjectPrivate *priv)
        : __privateInstance__(priv) {}

    ObjectPrivate *const __privateInstance__;
};
}
