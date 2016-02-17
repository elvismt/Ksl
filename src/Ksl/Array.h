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

template <typename T>
class Array
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

    void alloc(size_type n);

    size_type size() const { return m_size; }

    reference operator[] (size_type index) { return m_data[index]; }
    const_reference operator[] (size_type index) const { return m_data[index]; }

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }

    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }


private:

    pointer m_data;
    size_type m_size;
    bool m_view;

    void _clean();
};

template <typename T>
Array<T>::Array(size_type n)
    : m_data(n>0 ? new data_type[n] : nullptr)
    , m_size(n)
    , m_view(false)
{ }

template <typename T>
Array<T>::Array(size_type n, const data_type &value)
    : m_data(n>0 ? new data_type[n] : nullptr)
    , m_size(n)
    , m_view(false)
{
    for (auto &elem : *this)
        elem = value;
}


template <typename T>
Array<T>::Array(const Array &that)
    : m_data(that.m_data)
    , m_size(that.m_size)
    , m_view(true)
{ }

template <typename T>
Array<T>::Array(Array &&that)
    : m_data(that.m_data)
    , m_size(that.m_size)
    , m_view(true)
{
    if (!that.m_view) {
        that.m_view = true;
        this->m_view = false;
    }
}

template <typename T>
Array<T>::~Array()
{
    _clean();
}

template <typename T>
Array<T>& Array<T>::operator= (const Array &that)
{
    if (m_data == that.m_data) {
        return *this;
    }
    _clean();
    m_data = that.m_data;
    m_size = that.m_size;
    m_view = true;
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator= (Array &&that)
{
    if (m_data == that.m_data) {
        if (!that.m_view) {
            that.m_view = true;
            this->m_view = false;
        }
        return *this;
    }
    _clean();
    m_data = that.m_data;
    m_size = that.m_size;
    m_view = true;
    if (!that.m_view) {
        that.m_view = true;
        this->m_view = false;
    }
    return *this;
}

template <typename T>
void Array<T>::_clean()
{
    if (m_data && !m_view) {
        delete[] m_data;
    }
    m_data = nullptr;
    m_size = 0;
    m_view = false;
}

template <typename T>
void Array<T>::alloc(size_type n)
{
    if (m_size != n || m_view) {
        _clean();
        if (n > 0) {
            m_data = new data_type[n];
            m_size = n;
            m_view = false;
        }
    }
}

template <typename T> inline
Array<T> copy(const Array<T> &array)
{
    Array<T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = *iter++;
    }
    return std::move(ret);
}

template <typename T> inline
Array<T> linspace(T min, T max, T step=T(1))
{
    Array<T> ret(int((max-min)/step)+1);
    int k = 0;
    for (auto &elem : ret) {
        elem = min + k*step;
        ++k;
    }
    return std::move(ret);
}

template <typename T> inline
Array<T> randspace(int size, T max=T(1))
{
    Array<T> array(size);
    for (auto &elem : array) {
        elem = max * T(rand())/RAND_MAX;
    }
    return std::move(array);
}

template <typename Func, typename T> inline
Array<T> applyed(Func func, const Array<T> &array)
{
    Array<T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = func(*iter++);
    }
    return std::move(ret);
}

template <typename T> inline
std::ostream& operator << (std::ostream &out, const Array<T> &array)
{
    out << "[ ";
    for (size_t k=0; k<array.size()-1; ++k) {
        out << array[k] << ", ";
    }
    out << array[array.size()-1] << " ]";
    return out;
}

template <typename T> inline
QTextStream& operator << (QTextStream &out, const Array<T> &array)
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
