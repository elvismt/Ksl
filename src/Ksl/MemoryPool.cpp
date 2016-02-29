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

#include <Ksl/MemoryPool_p.h>

KSL_BEGIN_NAMESPACE

MemoryPool::MemoryPool(uint64_t unitSize, uint32_t numUnits)
    : Ksl::Object(new MemoryPoolPrivate(this))
{
    KSL_PUBLIC(MemoryPool);
    m->unitSize = unitSize;
    m->numUnits = numUnits;
    m->unitsUsed = 1;

    m->units = new char*[numUnits];
    m->units[0] = new char[unitSize];
    m->currUnit = m->units[0];
    m->pos = m->currUnit;
}


void* MemoryPool::allocBytes(uint64_t amount) {
    KSL_PUBLIC(MemoryPool);
    void *buffer;

    // MemoryPool can not allocate buffers bigger than unitSize
    if (amount > m->unitSize)
        return nullptr;

    // If there is space in the current unit, just update position
    // of pointer and return the current possition
    uint64_t available = uint64_t(m->currUnit) + m->unitSize - uint64_t(m->pos);
    if (available >= amount) {
        buffer = m->pos;
        m->pos += amount;
        return buffer;
    }

    // If there is not enought space in the current unit but
    // there is other units, allocate the next
    if (m->unitsUsed < m->numUnits) {
        m->units[m->unitsUsed] = new char[m->unitSize];
        m->currUnit = m->units[m->unitsUsed++];
        buffer = m->currUnit;
        m->pos = m->currUnit + amount;
        return buffer;
    }

    // No way to return memory
    return nullptr;
}


void MemoryPool::freeBytes(void *location, uint64_t size) {
    // TODO
    Q_UNUSED(location)
    Q_UNUSED(size)
}

KSL_END_NAMESPACE
