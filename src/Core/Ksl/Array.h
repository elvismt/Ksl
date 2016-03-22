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
template <size_t D, typename T=double> class Array{};


/*****************************************************
 * This is the 1D (Vector) Array type
 ****************************************************/
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
#ifdef Q_COMPILER_INITIALIZER_LISTS
    Array(std::initializer_list<data_type> initlist);
#endif

    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);

    int size() const { return m_data ? m_data->size : 0; }
    int capacity() const { return m_data ? m_data->maxsize : 0; }

    reference operator[] (size_type index) { return m_data->data[index]; }
    const_reference operator[] (size_type index) const { return m_data->data[index]; }

    pointer c_ptr() { return m_data ? m_data->data : nullptr; }
    const_pointer c_ptr() const { return m_data ? m_data->data : nullptr; }

    iterator begin() { return m_data ? m_data->data : nullptr; }
    iterator end() { return m_data ? m_data->data + m_data->size : nullptr; }
    const_iterator begin() const { return m_data ? m_data->data : nullptr; }
    const_iterator end() const { return m_data ? m_data->data + m_data->size : nullptr; }


    inline void resize(size_type newsize);
    inline void reserve(size_type maxsize);
    inline void append(const data_type &value);
    inline Array& operator<< (const data_type &value) { append(value); return *this; }

    inline void squeeze();


private:

    struct SharedData {
        pointer data;
        size_type size;
        size_type maxsize;
        size_type refc;
    };

    SharedData *m_data;
    inline void _free();
    inline void _alloc(size_type size);
};


template <typename T> inline
void Array<1,T>::_alloc(size_type size)
{
    m_data = (SharedData*) malloc(sizeof(SharedData));
    m_data->data = (pointer) malloc(size * sizeof(data_type));
    m_data->size = size;
    m_data->maxsize = size;
    m_data->refc = 1;
}


template <typename T> inline
void Array<1,T>::_free()
{
    if (m_data) {
        m_data->refc -= 1;
        if (m_data->refc == 0) {
            free(m_data->data);
            free(m_data);
        }
        m_data = nullptr;
    }
}


template <typename T> inline
void Array<1,T>::resize(size_type newsize) {
    if (!m_data) {
        _alloc(newsize);
    }
    else if (newsize <= m_data->maxsize) {
        m_data->size = newsize;
    }
    else {
        reserve(newsize);
        m_data->size = newsize;
    }
}


template <typename T> inline
void Array<1,T>::reserve(size_type maxsize) {
    if (!m_data) {
        _alloc(maxsize);
        m_data->size = 0;
    }
    else if (maxsize > 0 && maxsize > m_data->maxsize) {
        m_data->data = (pointer) realloc(
            m_data->data, maxsize * sizeof(data_type));
        m_data->maxsize = maxsize;
    }
}


template <typename T> inline
void Array<1,T>::append(const data_type &value) {
    if (!m_data)
        reserve(10);
    else if (m_data->maxsize == m_data->size) {
        if (m_data->maxsize < 12)
            reserve(12);
        else
            reserve( 4 * m_data->size / 3 );
    }
    m_data->data[m_data->size] = value;
    m_data->size += 1;
}


template <typename T> inline
void Array<1,T>::squeeze() {
    if (!m_data)
        return;
    if (m_data->maxsize > m_data->size) {
        m_data->data = (pointer) realloc(
            m_data->data, m_data->size * sizeof(data_type));
        m_data->maxsize = m_data->size;
    }
}


template <typename T>
Array<1,T>::Array(size_type n)
{
    if (n <= 0)
        m_data = nullptr;
    else
        _alloc(n);
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


#ifdef Q_COMPILER_INITIALIZER_LISTS
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
#endif


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


/********************************************
 * Utilities for creating 1D number series
 *******************************************/


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


/********************************************
 * These copies data from other containers
 ********************************************/


template <typename T, typename Iterator> inline
Array<1,T> array1D(const Iterator &begin, size_t size)
{
    Array<1,T> ret(size);
    Iterator iter = begin;
    for (auto &elem : ret)
        elem = *iter++;
    return std::move(ret);
}

template <typename T> inline
Array<1,T> array1D(const std::vector<T> &vec)
{ return std::move(array1D<T>(vec.begin(), vec.size())); }

template <typename T> inline
Array<1,T> array1D(const std::list<T> &lst)
{ return std::move(array1D<T>(lst.begin(), lst.size())); }

template <typename T> inline
Array<1,T> array1D(const QVector<T> &qvec)
{ return std::move(array1D<T>(qvec.begin(), qvec.size())); }

template <typename T> inline
Array<1,T> array1D(const QList<T> &qlst)
{ return std::move(array1D<T>(qlst.begin(), qlst.size())); }


/*******************************************************
 * Stream operator for easy text output of 1D Arrays
 ******************************************************/


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


template <typename T> inline
QDebug operator << (QDebug out, const Array<1,T> &array)
{
    out << "[ ";
    for (size_t k=0; k<array.size()-1; ++k) {
        out << array[k] << ", ";
    }
    out << array[array.size()-1] << " ]";
    return out;
}


/**********************************************
 * This is the 2D (Matrix) Array type
 **********************************************/
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
#ifdef Q_COMPILER_INITIALIZER_LISTS
    Array(std::initializer_list<
             std::initializer_list<data_type> >  initlist);
#endif

    ~Array();


    Array& operator= (const Array &that);
    Array& operator= (Array &&that);


    int rows() const { return m_data ? m_data->rows : 0; }
    int cols() const { return m_data ? m_data->cols : 0; }
    int size() const { return m_data ? m_data->rows*m_data->cols : 0; }


    pointer operator[] (size_type index) { return m_data->data[index]; }
    const_pointer operator[] (size_type index) const { return m_data->data[index]; }

    iterator begin() { return m_data ? m_data->data[0] : nullptr; }
    iterator end() { return m_data ? m_data->data[0] + (m_data->rows*m_data->cols) : nullptr; }
    const_iterator begin() const { return m_data ? m_data->data[0] : nullptr; }
    const_iterator end() const { return m_data ? m_data->data[0] + (m_data->rows*m_data->cols) : nullptr; }

    void setcol(size_type j, const data_type &value);
    void setcol(size_type j, const Array<1> &array);
    void coltocol(size_type j, const Array<2> &array, size_type aj);
    void rowtocol(size_type j, const Array<2> &array, size_type aj);

    void setrow(size_type j, const data_type &value);
    void setrow(size_type j, const Array<1> &array);
    void coltorow(size_type j, const Array<2> &array, size_type aj);
    void rowtorow(size_type j, const Array<2> &array, size_type aj);

    Array submat(int i, int j, int rows, int cols);


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
            delete m_data;
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
        m_data = that.m_data;
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


#ifdef Q_COMPILER_INITIALIZER_LISTS
template <typename T>
Array<2,T>::Array(std::initializer_list<
                     std::initializer_list<data_type> > initlist)
{
    // find biggest row provided
    size_type bigrow = 0;
    for (const auto &row : initlist)
        if (row.size() > bigrow) bigrow = row.size();
    // fill matrix with provided rows
    // and padd remaining entries with zeros
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
#endif


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
void Array<2,T>::setcol(size_type j, const Array<1> &array) {
    size_type n = qMin(array.size(), this->rows());
    for (size_type k=0; k<n; ++k)
        (*this)[k][j] = array[k];
}


template <typename T>
void Array<2,T>::setcol(size_type j, const T &value) {
    for (int k=0; k<this->rows(); ++k)
        (*this)[k][j] = value;
}


template <typename T>
void Array<2,T>::coltocol(size_type j, const Array<2> &array, size_type aj) {
    size_type n = qMin(array.rows(), this->rows());

    for (size_type k=0; k<n; ++k)
        (*this)[k][j] = array[k][aj];
}


template <typename T>
void Array<2,T>::rowtocol(size_type j, const Array<2> &array, size_type aj) {
    size_type n = qMin(array.cols(), this->rows());
    for (size_type k=0; k<n; ++k)
        (*this)[k][j] = array[aj][k];
}


template <typename T>
void Array<2,T>::setrow(size_type j, const Array<1> &array) {
    size_type n = qMin(array.size(), this->cols());
    for (size_type k=0; k<n; ++k)
        (*this)[j][k] = array[k];
}


template <typename T>
void Array<2,T>::setrow(size_type j, const T &value) {
    for (size_type k=0; k<this->cols(); ++k)
        (*this)[j][k] = value;
}


template <typename T>
void Array<2,T>::coltorow(size_type j, const Array<2> &array, size_type aj) {
    size_type n = qMin(array.rows(), this->cols());
    for (size_type k=0; k<n; ++k)
        (*this)[j][k] = array[k][aj];
}


template <typename T>
void Array<2,T>::rowtorow(size_type j, const Array<2> &array, size_type aj) {
    size_type n = qMin(array.cols(), this->cols());
    for (size_type k=0; k<n; ++k)
        (*this)[j][k] = array[aj][k];
}


template <typename T>
Array<2,T> Array<2,T>::submat(int i, int j, int rows, int cols) {
    Array<2,T> ret(rows, cols);
    for (int l=0; l<rows; l++)
        for (int m=0; m<cols; m++)
            ret[l][m] = (*this)[l+i][m+j];
    return std::move(ret);
}


/*********************************************************
 * These copy rows or columns of a matrix to an 1D array
 ********************************************************/


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
    for (int j=0; j<array.rows(); ++j)
        ret[j] = array[j][k];
    return std::move(ret);
}


/********************************************
 * Utilities for creating 2D number series
 *******************************************/


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


/**************************************
 * Copies data from other containers
 *************************************/

template <typename T, typename Iterator>
Array<2,T> array2D(size_t m, size_t n, const Iterator &begin)
{
    Array<2,T> ret(m, n);
    Iterator iter = begin;
    for (auto &elem : ret)
        elem = *iter++;
    return std::move(ret);
}

template <typename T>
Array<2,T> array2D(size_t m, size_t n, const Array<1,T> &array)
{ return std::move(array2D<T>(m, n, array.begin())); }

template <typename T>
Array<2,T> array2D(size_t m, size_t n, const std::vector<T> &vec)
{ return std::move(array2D<T>(m, n, vec.begin())); }

template <typename T>
Array<2,T> array2D(size_t m, size_t n, const std::list<T> &lst)
{ return std::move(array2D<T>(m, n, lst.begin())); }

template <typename T>
Array<2,T> array2D(size_t m, size_t n, const QVector<T> &qvec)
{ return std::move(array2D<T>(m, n, qvec.begin())); }

template <typename T>
Array<2,T> array2D(size_t m, size_t n, const QList<T> &qlst)
{ return std::move(array2D<T>(m, n, qlst.begin())); }


/*******************************************************
 * Stream operator for easy text output of 2D Arrays
 ******************************************************/


template <typename T> inline
std::ostream& operator<< (std::ostream &out, const Array<2,T> &array)
{
    for (int i=0; i<array.rows(); ++i) {
        out << "| ";
        for (int j=0; j<array.cols()-1; ++j)
            out << array[i][j]  << ", ";
        out << array[i][array.cols()-1] << " |" << std::endl;
    }
    return out;
}

template <typename T> inline
QTextStream& operator<< (QTextStream &out, const Array<2,T> &array)
{
    for (int i=0; i<array.rows(); ++i) {
        out << "| ";
        for (int j=0; j<array.cols()-1; ++j)
            out << array[i][j]  << ", ";
        out << array[i][array.cols()-1] << " |" << std::endl;
    }
    return out;
}

template <typename T> inline
QDebug operator<< (QDebug out, const Array<2,T> &array)
{
    for (int i=0; i<array.rows(); ++i) {
        out << "| ";
        for (int j=0; j<array.cols()-1; ++j)
            out << array[i][j]  << ", ";
        out << array[i][array.cols()-1] << " |" << '\n';
    }
    return out;
}


/****************************************************************
 * Operations that can be generalized to arrays of any dimension
 ****************************************************************/

/// @brief Returns true if the elements of the arrays are equal
template <size_t D, typename T> inline
bool operator== (const Array<D,T> &array1,
                 const Array<D,T> &array2)
{
    if (array1.size() != array2.size())
        return false;
    if (same(array1,array2))
        return true;

    auto iter = array2.begin();
    for (auto &elem : array1)
        if (elem != (*iter++))
            return false;
    return true;
}

/// @brief Returns false if the elements of the arrays are equal
template <size_t D, typename T> inline
bool operator!= (const Array<D,T> &array1,
                 const Array<D,T> &array2)
{
    return ! (array1 == array2);
}

/// @brief Returns true if the arrays are references to each other
template <size_t D, typename T> inline
bool same(const Array<D,T> &array1,
          const Array<D,T> &array2)
{
    return array1.begin() == array2.begin();
}

/// @brief Creates a new hard copy of array
template <size_t D, typename T> inline
Array<D,T> copy(const Array<D,T> &array)
{
    Array<D,T> ret = samesize(array);
    auto iter = array.begin();
    for (auto &elem : ret)
        elem = *iter++;
    return std::move(ret);
}


/// @brief Apply func to each element of array
template <typename Func, size_t D, typename T> inline
void apply(Func func, Array<D,T> &array)
{
    for (auto &elem : array)
        elem = func(elem);
}


/// @brief Produces a new array as a result of func applied to array
template <typename Func, size_t D, typename T> inline
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
    if (array.size() == 0)
        return T(0);
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
T median(const Array<D,T> &array) {
    size_t k = array.size() / 2;
    if (array.size() % 2 == 0)
        return (array.begin()[k-1] + array.begin()[k]) / T(2);
    return array.begin()[k];
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



template <size_t D, typename T> inline
Array<D,T>& operator+= (Array<D,T> &a1, const Array<D,T> &a2) {
    auto a2iter = a2.begin();
    for (auto &elem : a1)
        elem += (*a2iter++);
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator-= (Array<D,T> &a1, const Array<D,T> &a2) {
    auto a2iter = a2.begin();
    for (auto &elem : a1)
        elem -= (*a2iter++);
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator*= (Array<D,T> &a1, const Array<D,T> &a2) {
    auto a2iter = a2.begin();
    for (auto &elem : a1)
        elem *= (*a2iter++);
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator/= (Array<D,T> &a1, const Array<D,T> &a2) {
    auto a2iter = a2.begin();
    for (auto &elem : a1)
        elem /= (*a2iter++);
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator+= (Array<D,T> &a1, const T&x) {
    for (auto &elem : a1)
        elem += x;
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator-= (Array<D,T> &a1, const T&x) {
    for (auto &elem : a1)
        elem -= x;
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator*= (Array<D,T> &a1, const T&x) {
    for (auto &elem : a1)
        elem *= x;
    return a1;
}



template <size_t D, typename T> inline
Array<D,T>& operator/= (Array<D,T> &a1, const T&x) {
    for (auto &elem : a1)
        elem /= x;
    return a1;
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

} // namespace Ksl 

#endif // KSL_ARRAY_H
