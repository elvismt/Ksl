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

#ifndef QSL_ARRAY1D_H
#define QSL_ARRAY1D_H

#include <QSL/Global.h>
#include <QVector>

QSL_BEGIN_NAMESPACE

template <typename T>
class Array1D
{
public:

    typedef T* Iterator;
    typedef const T* ConstIterator;


    Array1D()
        : m_data(nullptr)
        , m_size(0)
        , m_view(false)
    { }

    Array1D(quint32 size)
        : m_data(new T[size])
        , m_size(size)
        , m_view(false)
    { }

    Array1D(const Array1D &that)
        : m_data(that.m_data)
        , m_size(that.m_size)
        , m_view(true)
    { }

    Array1D(const QVector<T> &qvec)
        : m_data(const_cast<T*>(qvec.data()))
        , m_size(qvec.size())
        , m_view(true)
    { }


    ~Array1D() {
        if (m_data && !m_view) {
            delete[] m_data;
        }
    }


    quint32 size() const {
        return m_size;
    }


    T& operator[] (quint32 index) {
        return m_data[index];
    }

    const T& operator[] (quint32 index) const {
        return m_data[index];
    }


    Iterator begin() {
        return m_data;
    }

    Iterator end() {
        return m_data + m_size;
    }


    void setView(const Array1D &that) {
        if (m_data == that.m_data) {
            return;
        }
        if (m_data && !m_view) {
            delete[] m_data;
        }
        m_data = that.m_data;
        m_size = that.m_size;
        m_view = true;
    }


private:

    T *m_data;
    quint32 m_size;
    bool m_view;
};

QSL_END_NAMESPACE

#endif // QSL_ARRAY1D_H
