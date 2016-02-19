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

#include <Ksl/Math.h>
#include <QTextStream>
#include <QVector>
#include <ostream>

KSL_BEGIN_NAMESPACE

// All array types in Ksl are specializations
// this class template
template <size_t D, typename T=double> class Array{};


// This is the 1D (Vector) array type
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
    Array(std::initializer_list<data_type> initlist);

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
    if (n > 0)
        _alloc(n);
    else
        m_data = nullptr;
}


template <typename T>
Array<1,T>::Array(size_type n, const data_type &value)
{
    if (n > 0) {
        _alloc(n);
        for (auto &elem : *this)
            elem = value;
    }
    else
        m_data = nullptr;
}


template <typename T>
Array<1,T>::Array(const Array &that)
{
    if (that.m_data) {
        m_data = that.m_data;
        if (m_data)
            m_data->refc += 1;
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
        if (m_data)
            m_data->refc += 1;
    }
    else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(std::initializer_list<data_type> initlist)
{
   if (initlist.size() > 0) {
      _alloc(initlist.size());
      auto iter = this->begin();
      for (const auto &elem : initlist)
         *iter++ = elem;
   }
   else
      m_data = nullptr;
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
        if (m_data)
            m_data->refc += 1;
    }
    return *this;
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (Array<1,T> &&that)
{
    if (m_data != that.m_data) {
        _free();
        m_data = that.m_data;
        if (m_data)
            m_data->refc += 1;
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


template <typename T>
Array<1,T> samesize(const Array<1,T> &array)
{
    return std::move(Array<1,T>(array.size()));
}


template <typename T>
Array<1,T> minsize(const Array<1,T> &a1, const Array<1,T> &a2)
{
    return std::move(Array<1,T>(qMin(a1.size(), a2.size())));
}


template <typename T>
Array<1,T> maxsize(const Array<1,T> &a1, const Array<1,T> &a2)
{
    return std::move(Array<1,T>(qMax(a1.size(), a2.size())));
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



// This is the 2D (Matrix) array type
template <typename T>
class Array<2,T>
{
public:

    typedef T data_type;
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T** pointer_pointer;
    typedef const T** const_pointer_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;


    Array(size_type m=0, size_type n=0);
    Array(size_type m, size_type n, const data_type &value);
    Array(const Array &that);
    Array(Array &&that);
    Array(std::initializer_list<
             std::initializer_list<data_type> >  initlist);

    ~Array();


    Array& operator= (const Array &that);
    Array& operator= (Array &&that);


    size_type rows() const { return m_data ? m_data->rows : 0; }
    size_type cols() const { return m_data ? m_data->cols : 0; }
    size_type size() const { return m_data ? m_data->rows*m_data->cols : 0; }


    pointer operator[] (size_type index) { return m_data->data[index]; }
    const_pointer operator[] (size_type index) const { return m_data->data[index]; }

    iterator begin() { return m_data ? m_data->data[0] : nullptr; }
    iterator end() { return m_data ? m_data->data[0] + (m_data->rows*m_data->cols) : nullptr; }
    const_iterator begin() const { return m_data ? m_data->data[0] : nullptr; }
    const_iterator end() const { return m_data ? m_data->data[0] + (m_data->rows*m_data->cols) : nullptr; }


private:

    struct SharedData {
        pointer_pointer data;
        size_type rows;
        size_type cols;
        size_type refc;
    };

    SharedData *m_data;
    inline void _free();
    inline void _alloc(size_type m, size_type n);
};


template <typename T> inline
void Array<2,T>::_alloc(size_type m, size_type n)
{
    m_data = new SharedData();
    m_data->data = new pointer[m];
    m_data->data[0] = new data_type[m*n];
    m_data->rows = m;
    m_data->cols = n;
    m_data->refc = 1;
    for (size_type k=1; k<m; ++k)
        m_data->data[k] = m_data->data[k-1] + n;
}


template <typename T> inline
void Array<2,T>::_free()
{
    if (m_data) {
        m_data->refc -= 1;
        if (m_data->refc == 0) {
            delete[] m_data->data[0];
            delete[] m_data->data;
            delete[] m_data;
        }
        m_data = nullptr;
    }
}


template <typename T>
Array<2,T>::Array(size_type m, size_type n)
{
    if (m>0 && n>0)
        _alloc(m,n);
    else
        m_data = 0;
}


template <typename T>
Array<2,T>::Array(size_type m, size_type n, const data_type &value)
{
    if (m>0 && n>0) {
        _alloc(m,n);
        for (auto &elem : *this)
            elem = value;
    }
    else
        m_data = 0;
}


template <typename T>
Array<2,T>::Array(const Array &that)
{
    if (that.m_data) {
        m_data = that.m_dat;
        m_data->refc += 1;
    }
    else
        m_data = nullptr;
}


template <typename T>
Array<2,T>::Array(Array &&that)
{
    if (that.m_data) {
        m_data = that.m_data;
        m_data->refc += 1;
    }
    else
        m_data = nullptr;
}


template <typename T>
Array<2,T>::Array(std::initializer_list<
                     std::initializer_list<data_type> > initlist)
{
    // find biggest row provided
    size_type bigrow = 0;
    for (const auto &row : initlist)
        if (row.size() > bigrow) bigrow = row.size();
    // fill matrix with provided rows and padd remaining entries with zeros
    if (initlist.size() > 0 && bigrow > 0) {
        _alloc(initlist.size(), bigrow);
        size_type j = 0;
        for (const auto &row : initlist) {
           size_type k = 0;
           for (const auto &elem : row)
               (*this)[j][k++] = elem;
           for ( ; k<bigrow; ++k)
               (*this)[j][k] = data_type(0);
           ++j;
        }
    }
    else
       m_data = nullptr;
}


template <typename T>
Array<2,T>::~Array()
{
    _free();
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (const Array &that)
{
    if (m_data != that.m_data) {
        _free();
        m_data = that.m_data;
        if (m_data)
            m_data->refc += 1;
    }
    return *this;
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (Array &&that)
{
    if (m_data != that.m_data) {
        _free();
        m_data = that.m_data;
        if (m_data)
            m_data->refc += 1;
    }
    return *this;
}


template <typename T>
Array<1,T> getrow(const Array<2,T> &array, size_t k)
{
    Array<1,T> ret(array.cols());
    for (size_t j=0; j<array.cols(); ++j)
        ret[j] = array[k][j];
    return std::move(ret);
}


template <typename T>
Array<1,T> getcol(const Array<2,T> &array, size_t k)
{
    Array<1,T> ret(array.rows());
    for (size_t j=0; j<array.rows(); ++j)
        ret[j] = array[j][k];
    return std::move(ret);
}


template <typename T>
Array<2,T> randmat(size_t rows, size_t cols, T max=T(1))
{
    Array<2,T> ret(rows,cols);
    for (auto &elem : ret)
        elem = max * T(rand())/RAND_MAX;
    return std::move(ret);
}


template <typename T>
Array<2,T> unitmat(size_t size, const T &factor=T(1))
{
    Array<2,T> ret(size, size, T(0));
    for (size_t k=0; k<size; ++k)
        ret[k][k] = factor;
    return std::move(ret);
}


template <typename T>
Array<2,T> samesize(const Array<2,T> &array)
{
    return std::move(Array<2,T>(array.rows(), array.cols()));
}


template <typename T>
Array<2,T> minsize(const Array<2,T> &a1, const Array<2,T> &a2)
{
    return std::move(Array<2,T>(qMin(a1.rows(), a2.rows()),
                                qMin(a1.cols(), a2.cols()) ));
}


template <typename T>
Array<2,T> maxsize(const Array<2,T> &a1, const Array<2,T> &a2)
{
    return std::move(Array<2,T>(qMax(a1.rows(), a2.rows()),
                                qMax(a1.cols(), a2.cols()) ));
}


template <typename T> inline
QTextStream& operator<< (QTextStream &out, const Array<2,T> &array)
{
    for (size_t i=0; i<array.rows(); ++i) {
        out << "| ";
        for (size_t j=0; j<array.cols()-1; ++j)
            out << array[i][j]  << ", ";
        out << array[i][array.cols()-1] << " |" << std::endl;
    }
    return out;
}


template <typename T> inline
std::ostream& operator<< (std::ostream &out, const Array<2,T> &array)
{
    for (size_t i=0; i<array.rows(); ++i) {
        out << "| ";
        for (size_t j=0; j<array.cols()-1; ++j)
            out << array[i][j]  << ", ";
        out << array[i][array.cols()-1] << " |" << std::endl;
    }
    return out;
}


/****************************************************************
 * Operations that can be generalized to arrays of any dimension
 ****************************************************************/

/// @brief Creates a new hard copy of array
template <size_t D, typename T>
Array<D,T> copy(const Array<D,T> &array)
{
    Array<D,T> ret = samesize(array);
    auto iter = array.begin();
    for (auto &elem : ret)
        elem = *iter++;
    return std::move(ret);
}


/// @brief Apply func to each element of array
template <typename Func, size_t D, typename T>
void apply(Func func, Array<D,T> &array)
{
    for (auto &elem : array)
        elem = func(elem);
}


/// @brief Produces a new array as a result of func applied to array
template <typename Func, size_t D, typename T>
Array<D,T> applied(Func func, const Array<D,T> &array)
{
    Array<D,T> ret = samesize(array);
    auto iter = array.begin();
    for (auto &elem : ret)
        elem = func(*iter++);
    return std::move(ret);
}


template <size_t D, typename T> inline
T min(const Array<D,T> &array) {
    T ret = *array.begin();
    for (const auto &elem : array)
        if (elem < ret)
            ret = elem;
    return ret;
}


template <size_t D, typename T> inline
T max(const Array<D,T> &array) {
    T ret = *array.begin();
    for (const auto &elem : array)
        if (elem > ret)
            ret = elem;
    return ret;
}


template <size_t D, typename T> inline
T mean(const Array<D,T> &array) {
    T ret = T(0);
    for (const auto &elem : array)
        ret += elem;
    return ret / array.size();
}


template <size_t D, typename T> inline
T sum(const Array<D,T> &array) {
    T ret = T(0);
    for (const auto &elem : array)
        ret += elem;
    return ret;
}


template <size_t D, typename T> inline
void sort(const Array<D,T> &array) {
    std::sort(array.begin(), array.end());
}


template <size_t D, typename T> inline
Array<D,T> sorted(const Array<D,T> &array) {
    auto ret = copy(array);
    std::sort(ret.begin(), ret.end());
    return std::move(ret);
}


/**********************************
 * Element-wise arithmetics
 **********************************/


/// @brief Element-wise sum. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator+ (const Array<D,T> &a1, const Array<D,T> &a2) {
    auto ret = minsize(a1, a2);
    auto a1iter = a1.begin();
    auto a2iter = a2.begin();
    for (auto &elem : ret)
        elem = (*a1iter++) + (*a2iter++);
    return std::move(ret);
}


/// @brief Element-wise subtraction. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator- (const Array<D,T> &a1, const Array<D,T> &a2) {
    auto ret = minsize(a1, a2);
    auto a1iter = a1.begin();
    auto a2iter = a2.begin();
    for (auto &elem : ret)
        elem = (*a1iter++) - (*a2iter++);
    return std::move(ret);
}


/// @brief Element-wise multiplication. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator* (const Array<D,T> &a1, const Array<D,T> &a2) {
    auto ret = minsize(a1, a2);
    auto a1iter = a1.begin();
    auto a2iter = a2.begin();
    for (auto &elem : ret)
        elem = (*a1iter++) * (*a2iter++);
    return std::move(ret);
}


/// @brief Element-wise division. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator/ (const Array<D,T> &a1, const Array<D,T> &a2) {
    auto ret = minsize(a1, a2);
    auto a1iter = a1.begin();
    auto a2iter = a2.begin();
    for (auto &elem : ret)
        elem = (*a1iter++) / (*a2iter++);
    return std::move(ret);
}


/// @brief Element-wise sum to scalar. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator+ (const Array<D,T> &array, const T &x) {
    auto ret = copy(array);
    for (auto &elem : ret)
        elem += x;
    return std::move(ret);
}


/// @brief Element-wise subtraction to scalar. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator- (const Array<D,T> &array, const T &x) {
    auto ret = copy(array);
    for (auto &elem : ret)
        elem -= x;
    return std::move(ret);
}


/// @brief Element-wise multiplication to scalar. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator* (const Array<D,T> &array, const T &x) {
    auto ret = copy(array);
    for (auto &elem : ret)
        elem *= x;
    return std::move(ret);
}


/// @brief Element-wise division to scalar. Produces copy.
template <size_t D, typename T> inline
Array<D,T> operator/ (const Array<D,T> &array, const T &x) {
    auto ret = copy(array);
    for (auto &elem : ret)
        elem /= x;
    return std::move(ret);
}


/********************************************
 * Common math functions applied element-wise
 *******************************************/

/// @brief Apply sin() to each element.
template <size_t D, typename T>
inline Array<D,T> sin(const Array<D,T> &array)
{ return std::move(applied(Math::sin, array)); }

/// @brief Apply cos() to each element.
template <size_t D, typename T>
inline Array<D,T> cos(const Array<D,T> &array)
{ return std::move(applied(Math::cos, array)); }

/// @brief Apply tan() to each element.
template <size_t D, typename T>
inline Array<D,T> tan(const Array<D,T> &array)
{ return std::move(applied(Math::tan, array)); }

/// @brief Apply asin() to each element.
template <size_t D, typename T>
inline Array<D,T> asin(const Array<D,T> &array)
{ return std::move(applied(Math::asin, array)); }

/// @brief Apply acos() to each element.
template <size_t D, typename T>
inline Array<D,T> acos(const Array<D,T> &array)
{ return std::move(applied(Math::acos, array)); }

/// @brief Apply atan() to each element.
template <size_t D, typename T>
inline Array<D,T> atan(const Array<D,T> &array)
{ return std::move(applied(Math::atan, array)); }

/// @brief Apply log() to each element.
template <size_t D, typename T>
inline Array<D,T> log(const Array<D,T> &array)
{ return std::move(applied(Math::log, array)); }

/// @brief Apply log10() to each element.
template <size_t D, typename T>
inline Array<D,T> log10(const Array<D,T> &array)
{ return std::move(applied(Math::log10, array)); }

/// @brief Apply exp() to each element.
template <size_t D, typename T>
inline Array<D,T> exp(const Array<D,T> &array)
{ return std::move(applied(Math::exp, array)); }

KSL_END_NAMESPACE

#endif // KSL_ARRAY_H
