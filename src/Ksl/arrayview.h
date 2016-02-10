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

#ifndef KSL_ARRAYVIEW_H
#define KSL_ARRAYVIEW_H

#include <Ksl/global.h>
#include <QVector>
#include <vector>

template <typename T>
class KslArrayView
{
public:

    typedef T Data;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Iterator;
    typedef const T* ConstIterator;


    KslArrayView()
        : m_data(0)
        , m_size(0)
    { }

    KslArrayView(Pointer data, quint32 size)
        : m_data(data)
        , m_size(size)
    { }

    KslArrayView(QVector<T> &qvec)
        : m_data(qvec.data())
        , m_size(qvec.size())
    { }

    KslArrayView(std::vector<T> &stdvec)
        : m_data(stdvec.data())
        , m_size(stdvec.size())
    { }


    quint32 size() const { return m_size; }

    ConstReference operator[] (quint32 index) const { return m_data[index]; }

    void mirror(const KslArrayView &that) {
        m_data = that.m_data;
        m_size = that.m_size;
    }


private:

    Pointer m_data;
    quint32 m_size;
};

#endif // KSL_ARRAYVIEW_H