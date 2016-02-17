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
#include <QTextStream>
#include <QVector>
#include <ostream>

KSL_BEGIN_NAMESPACE

// All array types in Ksl are specializations
// this class template
template <size_t D, typename T=double> class Array{};


// This is the 1D array type
template <typename T>
class Array<1,T>
{
public:

    typedef T data_type;
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;


    Array(size_type n=0);
    Array(size_type n, const data_type &value);
    Array(const Array &that);
    Array(Array &&that);

    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);

    size_type size() const { return m_data ? m_data->size : 0; }

    reference operator[] (size_type index) { return m_data->data[index]; }
    const_reference operator[] (size_type index) const { return m_data->data[index]; }

    iterator begin() { return m_data ? m_data->data : nullptr; }
    iterator end() { return m_data ? m_data->data + m_data->size : nullptr; }
    const_iterator begin() const { return m_data ? m_data->data : nullptr; }
    const_iterator end() const { return m_data ? m_data->data + m_data->size : nullptr; }


private:

    struct SharedData {
        pointer data;
        size_type size;
        size_type refc;
    };

    SharedData *m_data;
    inline void _free();
    inline void _alloc(size_type n);
};


template <typename T> inline
void Array<1,T>::_free()
{
    if (m_data) {
        m_data->refc -= 1;
        if (m_data->refc == 0) {
            delete[] m_data->data;
            delete m_data;
        }
        m_data = nullptr;
    }
}


template <typename T> inline
void Array<1,T>::_alloc(size_type n)
{
    m_data = new SharedData();
    m_data->data = new data_type[n];
    m_data->size = n;
    m_data->refc = 1;
}


template <typename T>
Array<1,T>::Array(size_type n)
{
    if (n > 0) {
        _alloc(n);
    }
    else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(size_type n, const data_type &value)
{
    if (n > 0) {
        _alloc(n);
        for (auto &elem : *this) {
            elem = value;
        }
    }
    else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(const Array &that)
{
    if (that.m_data) {
        m_data = that.m_data;
        if (m_data) {
            m_data->refc += 1;
        }
    }
    else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(Array &&that)
{
    if (that.m_data) {
        m_data = that.m_data;
        if (m_data) {
            m_data->refc += 1;
        }
    }
    else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::~Array()
{
    _free();
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (const Array<1,T> &that)
{
    if (m_data != that.m_data) {
        _free();
        m_data = that.m_data;
        if (m_data) {
            m_data->refc += 1;
        }
    }
    return *this;
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (Array<1,T> &&that)
{
    if (m_data != that.m_data) {
        _free();
        m_data = that.m_data;
        if (m_data) {
            m_data->refc += 1;
        }
    }
    return *this;
}


template <typename T> inline
Array<1,T> linspace(T min, T max, T step=T(1))
{
    Array<1,T> ret(int((max-min)/step)+1);
    size_t k = 0;
    for (auto &elem : ret) {
        elem = min + k*step;
        ++k;
    }
    return std::move(ret);
}


template <typename T> inline
Array<1,T> randspace(size_t size, T max=T(1))
{
    Array<1,T> ret(size);
    for (auto &elem : ret) {
        elem = max * T(rand())/RAND_MAX;
    }
    return std::move(ret);
}


template <typename Func, typename T> inline
Array<1,T> apply(Func func, const Array<1,T> &array)
{
    Array<1,T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = func(*iter++);
    }
    return std::move(ret);
}


template <typename T> inline
Array<1,T> copy(const Array<1,T> &array)
{
    Array<1,T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = *iter++;
    }
    return std::move(ret);
}


template <typename T> inline
std::ostream& operator << (std::ostream &out, const Array<1,T> &array)
{
    out << "[ ";
    for (size_t k=0; k<array.size()-1; ++k) {
        out << array[k] << ", ";
    }
    out << array[array.size()-1] << " ]";
    return out;
}

template <typename T> inline
QTextStream& operator << (QTextStream &out, const Array<1,T> &array)
{
    out << "[ ";
    for (size_t k=0; k<array.size()-1; ++k) {
        out << array[k] << ", ";
    }
    out << array[array.size()-1] << " ]";
    return out;
}

KSL_END_NAMESPACE

#endif // KSL_ARRAY_H
