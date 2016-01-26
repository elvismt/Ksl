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

#ifndef QSL_OBJECT_H
#define QSL_OBJECT_H

#include <QSL/ObjectPrivate.h>

#define QSL_GET_PRIVATE(Class, instance) \
    (static_cast<Class##Private*>((instance)->getPrivate()))

#define QSL_PUBLIC(Class) \
    auto m = QSL_GET_PRIVATE(Class, this)

QSL_BEGIN_NAMESPACE

class QSL_API Object
{
public:

    virtual ~Object() {
        if (mPriv != nullptr) {
            delete mPriv;
        }
    }

    ObjectPrivate* getPrivate() const {
        return mPriv;
    }

protected:

    Object(ObjectPrivate *priv)
        : mPriv(priv)
    { }

    ObjectPrivate *const mPriv;
};

QSL_END_NAMESPACE

#endif // QSL_OBJECT_H
