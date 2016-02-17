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

KSL_BEGIN_NAMESPACE

template <int D, typename T=double> class Array{};


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
    Array(std::initializer_list<data_type> initList);

    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);


    void alloc(size_type n);
    void from(const QVector<data_type> &qvec);
    void from(const std::vector<data_type> &vec);


    size_type size() const { return m!=nullptr ? m->size : size_type(0); }

    reference operator[] (size_type index) { return m->data[index]; }
    const_reference operator[] (size_type index) const { return m->data[index]; }

    iterator begin() { return m!=nullptr ? m->data : nullptr; }
    iterator end() { return m!=nullptr ? m->data+m->size : nullptr; }

    const_iterator begin() const { return m!=nullptr ? m->data : nullptr; }
    const_iterator end() const { return m!=nullptr ? m->data+m->size : nullptr; }


private:

    struct SharedData
    {
        SharedData(size_type n)
            : data(n>0 ? new data_type[n] : nullptr)
            , size(n)
            , refc(1)
        { }

        ~SharedData() {
            if (refc==0 && data!=nullptr) {
                delete[] data;
            }
        }

        pointer data;
        size_type size;
        size_type refc;
    };

    void clean();

    SharedData *m;
};

template <typename T>
Array<1,T>::Array(size_type n)
    : m(n>0 ? new SharedData(n) : nullptr)
{ }

template <typename T>
Array<1,T>::Array(size_type n, const data_type &value)
    : m(n>0 ? new SharedData(n) : nullptr)
{
    for (auto &elem : *this)
        elem = value;
}

template <typename T>
Array<1,T>::Array(const Array &that)
    : m(that.m)
{
    m->refc += 1;
}

template <typename T>
Array<1,T>::Array(Array &&that)
    : m(that.m)
{
    m->refc += 1;
}

template <typename T>
Array<1,T>::Array(std::initializer_list<data_type> initList)
    : m(new SharedData(initList.size()))
{
    auto iter = this->begin();
    for (auto &elem : initList)
        *iter++ = elem;
}

template <typename T>
Array<1,T>::~Array()
{
    clean();
}

template <typename T>
Array<1,T>& Array<1,T>::operator= (const Array &that)
{
    if (m == that.m) {
        return *this;
    }
    clean();
    m = that.m;
    m->refc += 1;
    return *this;
}

template <typename T>
Array<1,T>& Array<1,T>::operator= (Array &&that)
{
    if (m == that.m) {
        return *this;
    }
    clean();
    m = that.m;
    m->refc += 1;
    return *this;
}

template <typename T>
void Array<1,T>::clean()
{
    if (m) {
        m->refc -= 1;
        if (m->refc == 0) {
            delete m;
        }
    }
}

template <typename T>
void Array<1,T>::alloc(size_type n)
{
    if (!m || m->size!=n) {
        clean();
        m = n>0 ? new SharedData(n) : nullptr;
    }
}

template <typename T>
void Array<1,T>::from(const QVector<T> &qvec)
{
    alloc(qvec.size());
    auto iter = begin();
    for (auto elem : qvec) {
        *iter++ = elem;
    }
}

template <typename T>
void Array<1,T>::from(const std::vector<T> &vec)
{
    alloc(vec.size());
    auto iter = begin();
    for (auto elem : vec) {
        *iter++ = elem;
    }
}

template <typename T=double> inline
Array<1,T> copy(const Array<1,T> &array)
{
    Array<1,T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = *iter++;
    }
    return std::move(ret);
}

template <typename T=double> inline
Array<1,T> linspace(T min, T max, T step=T(1))
{
    Array<1,T> ret(int((max-min)/step)+1);
    int k = 0;
    for (auto &elem : ret) {
        elem = min + k*step;
        ++k;
    }
    return std::move(ret);
}

template <typename T=double> inline
Array<1,T> randspace(int size, T max=T(1))
{
    Array<1,T> array(size);
    for (auto &elem : array) {
        elem = max * T(rand())/RAND_MAX;
    }
    return std::move(array);
}

template <typename Func, typename T=double> inline
Array<1,T> applyed(Func func, const Array<1,T> &array)
{
    Array<1,T> ret(array.size());
    auto iter = array.begin();
    for (auto &elem : ret) {
        elem = func(*iter++);
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
