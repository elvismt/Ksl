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

#ifndef KSL_MEMORYPOOL_H
#define KSL_MEMORYPOOL_H

#include <Ksl/Object.h>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT MemoryPool
    : public Ksl::Object
{
public:

    MemoryPool(uint64_t unitSize=1024, uint32_t numUnits=32);


    void* allocBytes(uint64_t amount);

    void freeBytes(void *location, uint64_t size);


    template <typename T, typename... Args>
    inline T* alloc(Args... args) {
        return new (allocBytes(sizeof(T))) T(args...);
    }

    template <typename T>
    inline T* allocArray(uint64_t size) {
        return (T*) allocBytes(size*sizeof(T));
    }

    template <typename T>
    inline void free(T *ptr) {
        freeBytes(ptr, sizeof(T));
    }

    template <typename T>
    inline void freeArray(T *ptr, uint64_t size) {
        freeBytes(ptr, size*sizeof(T));
    }
};

KSL_END_NAMESPACE

#endif // KSL_MEMORYPOOL_H
