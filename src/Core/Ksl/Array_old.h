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

#ifndef KSL_ARRAY_H
#define KSL_ARRAY_H

#include <Ksl/Global.h>
#include <Ksl/Math.h>
#include <vector>
#include <list>
#include <ostream>
#include <QVector>
#include <QList>
#include <QTextStream>
#include <QDebug>

namespace Ksl {

/*****************************************************
* All array types in Ksl are specializations
* this class template
****************************************************/
template <
    int Dimension,
    typename DataType=double
> class Array{};


/***************************************************
* Storage engine used by public array types
**************************************************/
template <typename T>
class Array<0,T>
{
private:

    friend class Array<1,T>;
    friend class Array<2,T>;
    friend class ArrayView<T>;


    typedef T Scalar;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Pointer;
    typedef const T* ConstPointer;


    Array(int rows, int cols);

    Reference vecAt(int idx) { return m_data[idx]; }
    ConstReference vecAt(int idx) const { return m_data[idx]; }

    Pointer matAt(int row) { return m_data + row*m_cols; }
    ConstPointer matAt(int row) const { return m_data + row*m_cols; }

    void alloc(int rows, int cols);
    void free();

    Array* ref();
    void unref();

    Pointer m_data;
    int m_rows;
    int m_cols;
    int m_refCount;
};


template <typename T>
Array<0,T>::Array(int rows, int cols)
{
    alloc(rows, cols);
}


template <typename T>
void Array<0,T>::alloc(int rows, int cols)
{
    m_data = (T*) std::malloc((std::size_t) rows*cols * sizeof(T));
    m_rows = rows;
    m_cols = cols;
    m_refCount = 1;
}


template <typename T>
void Array<0,T>::free()
{
    std::free(m_data);
}


template <typename T>
Array<0,T>* Array<0,T>::ref()
{
    m_refCount += 1;
    return this;
}


template <typename T>
void Array<0,T>::unref()
{
    m_refCount -= 1;
    if (m_refCount == 0) {
        free();
    }
}


/***************************************************
* Array 1D (vector) class
**************************************************/
template <typename T>
class Array<1,T>
{
public:

    typedef T Scalar;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T* Iterator;
    typedef const T* ConstIterator;


    Array(int size);
    Array(const Array<1,T> &that);

    int size() const { return m_data != nullptr ? m_data->m_cols : 0; }

    Reference operator[] (int idx) { return m_data->vecAt(idx); }
    ConstReference operator[] (int idx) const { return m_data->vecAt(idx); }

    Iterator begin() { return m_data != nullptr ? m_data->m_data : nullptr; }
    Iterator end() { return m_data != nullptr ? m_data->m_data + m_data->m_cols : nullptr; }
    ConstIterator begin() const { return m_data != nullptr ? m_data->m_data : nullptr; }
    ConstIterator end() const { return m_data != nullptr ? m_data->m_data + m_data->m_cols : nullptr; }


private:

    Array<1,T> *m_data;
};


template <typename T>
Array<1,T>::Array(int size)
{
    if (size > 0) {
        m_data = new Array<0,T>(1, size);
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(const Array<1,T> &that)
{
    if (that.m_data != nullptr) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


} // namespace Ksl

#endif // KSL_ARRAY_H
