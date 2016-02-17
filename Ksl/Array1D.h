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

#ifndef KSL_ARRAY1D_H
#define KSL_ARRAY1D_H

#include <Ksl/Global.h>
#include <QVector>

KSL_BEGIN_NAMESPACE

template <typename T>
class Array1D
{
public:

    typedef T Data;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Iterator;
    typedef const T* ConstIterator;


    Array1D()
        : m_data(nullptr)
        , m_size(0)
        , m_view(false)
    { }

    Array1D(int size)
        : m_data(new Data[size])
        , m_size(size)
        , m_view(false)
    { }

    Array1D(const Array1D &that)
        : m_data(that.m_data)
        , m_size(that.m_size)
        , m_view(true)
    { }

    Array1D(Array1D &&that)
        : m_data(that.m_data)
        , m_size(that.m_size)
        , m_view(true)
    {
        if (!that.m_view) {
            that.m_view = true;
            this->m_view = false;
        }
    }

    Array1D(std::initializer_list<Data> initlist)
        : m_data(new Data[initlist.size()])
        , m_size(initlist.size())
        , m_view(false)
    {
        Iterator iter = this->begin();
        for (auto &elem : initlist) {
            *iter++ = elem;
        }
    }
    
    Array1D(std::vector<Data> &vec)
        : m_data(vec.data())
        , m_size(vec.size())
        , m_view(true)
    { }

    Array1D(QVector<Data> &qvec)
        : m_data(qvec.data())
        , m_size(qvec.size())
        , m_view(true)
    { }

    ~Array1D() {
        if (m_data && !m_view) {
            delete[] m_data;
        }
    }

    Array1D& operator= (const Array1D &that) {
        if (m_data == that.m_data) {
            return *this;
        }
        if (m_data && !m_view) {
            delete[] m_data;
        }
        m_data = that.m_data;
        m_size = that.m_size;
        m_view = true;
        return *this;
    }

    Array1D& operator= (Array1D &&that) {
        if (m_data == that.m_data) {
            if (!that.m_view) {
                that.m_view = true;
                this->m_view = false;
            }
            return *this;
        }
        if (m_data && !m_view) {
            delete[] m_data;
        }
        m_data = that.m_data;
        m_size = that.m_size;
        if (!that.m_view) {
            that.m_view = true;
            this->m_view = false;
            return *this;
        }
        m_view = true;
        return *this;
    }


    int size() const {
        return m_size;
    }

    Reference operator[] (int index) {
        return m_data[index];
    }
    
    ConstReference operator[] (int index) const {
        return m_data[index];
    }
    
    Pointer c_ptr() {
        return m_data;
    }

    ConstPointer c_ptr() const {
        return m_data;
    }

    Iterator begin() {
        return m_data;
    }
    
    Iterator end() {
        return m_data + m_size;
    }
    
    ConstIterator begin() const {
        return m_data;
    }
    
    ConstIterator end() const {
        return m_data + m_size;
    }


private:
    
    Pointer m_data;
    int m_size;
    bool m_view;
};


typedef Array1D<double> Array;
typedef Array1D<int>    IArray;


template <typename T = double>
inline Array1D<T> zeros(int size)
{
    Array1D<T> array(size);
    for (auto &elem : array) {
        elem = T(0);
    }
    return std::move(array);
}

template <typename T = double>
inline Array1D<T> linspace(T min, T max, T step=T(1))
{
    Array1D<T> array(int((max-min)/step)+1);
    int k = 0;
    for (auto &elem : array) {
        elem = min + k*step;
        ++k;
    }
    return std::move(array);
}

template <typename T = double>
inline Array1D<T> randspace(int size, T max=T(1))
{
    Array1D<T> array(size);
    for (auto &elem : array) {
        elem = max * T(rand())/RAND_MAX;
    }
    return std::move(array);
}

template <typename T = double>
inline Array1D<T> copy(const Array1D<T> &array)
{
    Array1D<T> tmp(array.size());
    auto iter = array.begin();
    for (auto &elem : tmp) {
        elem = *iter++;
    }
    return std::move(tmp);
}

template <typename Functor, typename T = double>
inline Array1D<T> applied(Functor func, const Array1D<T> &array)
{
    Array1D<T> tmp(array.size());
    auto iter = array.begin();
    for (auto &elem : tmp) {
        elem = func(*iter++);
    }
    return std::move(tmp);
}

template <typename T>
inline std::ostream& operator<< (std::ostream &os,
                                 const Array1D<T> &array)
{
    os << "[ ";
    for (int k=0; k<array.size()-1; ++k) {
        os << array[k] << ", ";
    }
    os << array[array.size()-1] << " ]";
    return os;
}

KSL_END_NAMESPACE

#endif // KSL_ARRAY1D_H
