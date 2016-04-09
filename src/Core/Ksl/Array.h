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
 *****************************************************/
template <int D, typename T=double> class Array{};
template <typename T> class ArrayIterator;


/*****************************************************
 * This is the Storage base for vectors and matrices
 *****************************************************/
template <typename T>
class Array<0,T>
{
private:

    friend class Array<1,T>;
    friend class Array<2,T>;
    friend class ArrayIterator<T>;
    template <typename H> friend Array<1,H> row(const Array<2,H>&, int);
    template <typename H> friend Array<1,H> col(const Array<2,H>&, int);


    enum Type {
        Matrix         = 0x00000001,
        RowVector      = 0x00000002,
        ColumnVector   = 0x00000004,
        IsView         = 0x00000008
    };


    Array(int rows, int cols, int type);

    int size() const;
    int rows() const;
    int cols() const;

    T& vec_at(int k);
    const T& vec_at(int k) const;

    T* mat_at(int k);
    const T* mat_at(int k) const;

    T* c_ptr();
    const T* c_ptr() const;

    void alloc(int rows, int cols, int type);
    void reserve(int size);
    void free();
    Array<0,T> * ref();
    void unref();

    void append(const T &value);


    int m_type;
    int m_rows;
    int m_cols;
    int m_refs;
    int m_nalloc;
    T *m_data;
};


template <typename T>
Array<0,T>::Array(int rows, int cols, int type)
{
    alloc(rows, cols, type);
}


template <typename T>
int Array<0,T>::size() const
{
    if (m_type & Matrix) {
        return m_rows*m_cols;
    }
    if (m_type & ColumnVector) {
        return m_rows;
    }
    return m_cols;
}


template <typename T>
int Array<0,T>::rows() const
{
    return m_rows;
}


template <typename T>
int Array<0,T>::cols() const
{
    return m_cols;
}


template <typename T>
T& Array<0,T>::vec_at(int k)
{
    if (m_type & ColumnVector) {
        return m_data[k*m_cols];
    }
    return m_data[k];
}


template <typename T>
const T& Array<0,T>::vec_at(int k) const
{
    if (m_type & ColumnVector) {
        return m_data[k*m_cols];
    }
    return m_data[k];
}


template <typename T>
T* Array<0,T>::mat_at(int k)
{
    return (m_data + int(k*m_rows));
}


template <typename T>
const T* Array<0,T>::mat_at(int k) const
{
    return (m_data + int(k*m_rows));
}


template <typename T>
T* Array<0,T>::c_ptr()
{
    return m_data;
}


template <typename T>
const T* Array<0,T>::c_ptr() const
{
    return m_data;
}


template <typename T>
void Array<0,T>::alloc(int rows, int cols, int type)
{
    m_type = type;
    m_rows = rows;
    m_cols = cols;
    m_nalloc = rows*cols;
    m_refs = 1;

    if ((type & Matrix) && !(type & IsView)) {
        m_data = (T*) std::malloc(
            (std::size_t) rows*cols*sizeof(T));
    }
    else if ((type & RowVector) && !(type & IsView)) {
        m_data = (T*) std::malloc(
            (std::size_t) cols*sizeof(T));
    }
}


template <typename T>
void Array<0,T>::reserve(int size)
{
    if (size > m_nalloc) {
        m_nalloc = size;
        m_data = (T*) std::realloc(
            (void*) m_data,
            (std::size_t) size*sizeof(T));
    }
}


template <typename T>
void Array<0,T>::append(const T &value)
{
    if (m_type & RowVector) {
        if (m_nalloc < 12) {
            reserve(12);
        }
        if (m_nalloc == m_cols) {
            reserve(4 * m_cols / 3);
        }
        this->vec_at(m_cols) = value;
        m_cols += 1;
    }
}


template <typename T>
void Array<0,T>::free()
{
    if (!(m_type & IsView)) {
        std::free(m_data);
    }
}


template <typename T>
Array<0,T>* Array<0,T>::ref()
{
    m_refs += 1;
    return this;
}


template <typename T>
void Array<0,T>::unref()
{
    m_refs -= 1;
    if (m_refs == 0) {
        free();
    }
}


/*****************************************************
 * This is a Vector iterator, may be used to iterate
 * 1D arrays as well as rows or columns of matrices
 *****************************************************/


template <typename T>
class ArrayIterator
{
public:

    typedef T value_type;
    typedef T* pointer_type;
    typedef T& reference_type;

    ArrayIterator(Array<0,T> *data, int pos);


    T* operator->();
    const T* operator->() const;

    T& operator*();
    const T& operator*() const;

    ArrayIterator& operator++();
    ArrayIterator& operator--();

    bool operator== (const ArrayIterator& that) const;
    bool operator!= (const ArrayIterator& that) const;

    int operator- (const ArrayIterator& that) const;

    ArrayIterator operator+ (int n) const;
    ArrayIterator operator- (int n) const;


private:

    Array<0,T> *m_data;
    int m_pos;
};


template <typename T>
ArrayIterator<T>::ArrayIterator(Array<0,T> *data, int pos)
    : m_data(data)
    , m_pos(pos)
{ }


template <typename T>
T* ArrayIterator<T>::operator->()
{
    return & (m_data->vec_at(m_pos));
}


template <typename T>
const T* ArrayIterator<T>::operator->() const
{
    return & (m_data->vec_at(m_pos));
}


template <typename T>
T& ArrayIterator<T>::operator*()
{
    return m_data->vec_at(m_pos);
}


template <typename T>
const T& ArrayIterator<T>::operator*() const
{
    return m_data->vec_at(m_pos);
}


template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator++()
{
    m_pos += 1;
    return *this;
}


template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator--()
{
    m_pos += 1;
    return *this;
}


template <typename T>
bool ArrayIterator<T>::operator== (const ArrayIterator<T>& that) const
{
    return m_data == that.m_data &&
           m_pos == that.m_pos;
}


template <typename T>
bool ArrayIterator<T>::operator!=(const ArrayIterator<T>& that) const
{
    return m_data != that.m_data ||
           m_pos != that.m_pos;
}


template <typename T>
int ArrayIterator<T>::operator- (const ArrayIterator& that) const
{
    if (!m_data) return 0;
    return m_data->m_type & Array<0,T>::ColumnVector ?
                (m_data->m_data - that.m_data->m_data) / m_data->m_cols :
                m_data->m_data - that.m_data->m_data;
}


template <typename T>
ArrayIterator<T> ArrayIterator<T>::operator+ (int n) const
{
    return ArrayIterator<T>(m_data, m_pos+n);
}


template <typename T>
ArrayIterator<T> ArrayIterator<T>::operator- (int n) const
{
    return ArrayIterator<T>(m_data, m_pos-n);
}


/*****************************************************
 * This is the 1D (Vector) Array type
 *****************************************************/


template <typename T>
class Array<1,T>
{
public:

    template <typename H> friend Array<1,H> row(const Array<2,H>&, int);
    template <typename H> friend Array<1,H> col(const Array<2,H>&, int);


    typedef T Scalar;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef ArrayIterator<T> Iterator;
    typedef ArrayIterator<const T> ConstIterator;


    Array(int size=0);
    Array(int size, const T &value);
    Array(const Array &that);
    Array(Array &&that);

    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);

    int size() const { return m_data!=nullptr ? m_data->size() : 0; }

    Reference operator[] (int k) { return m_data->vec_at(k); }
    ConstReference operator[] (int k) const { return m_data->vec_at(k); }
    Reference at(int k) { return m_data->vec_at(k); }
    ConstReference at(int k) const { return m_data->vec_at(k); }

    Pointer c_ptr() { return m_data!=nullptr ? m_data->c_ptr() : nullptr; }
    ConstPointer c_ptr() const { return m_data!=nullptr ? m_data->c_ptr() : nullptr; }

    Iterator begin() { return Iterator(m_data, 0); }
    Iterator end() { return Iterator(m_data, this->size()); }

    ConstIterator begin() const { return ConstIterator(m_data, 0); }
    ConstIterator end() const { return ConstIterator(m_data, this->size()); }

    void append(const T &value);


private:

    Array<0,T> *m_data;
};


template <typename T>
Array<1,T>::Array(int size)
{
    if (size > 0) {
        m_data = new Array<0,T>(1, size, Array<0,T>::RowVector);
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(int size, const T &value)
{
    if (size > 0) {
        m_data = new Array<0,T>(0, size, Array<0,T>::RowVector);
        for (int k=0; k<this->size(); ++k) {
            m_data->vec_at(k) = value;
        }
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(const Array &that)
{
    if (that.m_data !=  nullptr) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::Array(Array &&that)
{
    if (that.m_data !=  nullptr) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<1,T>::~Array()
{
    if (m_data) {
        m_data->unref();
    }
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (const Array<1,T> &that)
{
    if (m_data != that.m_data) {
        if (m_data) {
            m_data->unref();
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        }
        else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (Array<1,T> &&that)
{
    if (m_data != that.m_data) {
        if (m_data) {
            m_data->unref();
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        }
        else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename T>
void Array<1,T>::append(const T &value)
{
    if (m_data) {
        m_data->append(value);
    } else {
        m_data = new Array<0,T>(1, 1, Array<0,T>::RowVector);
        m_data->vec_at(0) = value;
    }
}


template <typename T> inline std::ostream&
operator << (std::ostream &out, const Array<1,T> &vec)
{
    int n = vec.size() - 1;
    out << '[';
    for (int k=0; k<n; ++k) {
        out << vec[k] << ", ";
    }
    if (n>=0) out << vec[n] << ']';
    else out << ']';
    return out;
}


/*****************************************************
 * Functions for vector creation
 *****************************************************/


template <typename T=double> inline
Array<1,T> zeros(int size)
{
    return std::move(Array<1,T>(size, T(0)));
}


template <typename T=double> inline
Array<1,T> ones(int size)
{
    return std::move(Array<1,T>(size, T(1)));
}


template <typename T=double> inline
Array<1,T> base(int size, int k)
{
    Array<1,T> ret(size, T(0));
    ret[k] = T(1);
    return std::move(ret);
}


template <typename T=double> inline
Array<1,T> linspace(const T &min, const T &max, const T &step=T(1))
{
    Array<1,T> ret(int((max-min)/step) + 1);
    for (int k=0; k<ret.size(); ++k) {
        ret[k] = min + k*step;
    }
    return std::move(ret);
}


template <typename T=double> inline
Array<1,T> randspace(int size, const T &factor=T(1))
{
    Array<1,T> ret(size);
    for (int k=0; k<size; ++k) {
        ret[k] = T(factor * double(rand())/RAND_MAX);
    }
    return std::move(ret);
}


template <typename T> inline
Array<1,T> samesize(const Array<1,T> &vec)
{
    return std::move(Array<1,T>(vec.size()));
}


template <typename T> inline
Array<1,T> minsize(const Array<1,T> &vec1, const Array<1,T> &vec2)
{
    return std::move(Array<1,T>(
        qMin(vec1.size(), vec2.size())));
}


template <typename T> inline
Array<1,T> maxsize(const Array<1,T> &vec1, const Array<1,T> &vec2)
{
    return std::move(Array<1,T>(
        qMax(vec1.size(), vec2.size())));
}


/*****************************************************
 * This is the 2D (Matrix) Array type
 *****************************************************/


template <typename T>
class Array<2,T>
{
public:
    
    typedef T Scalar;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T& Reference;
    typedef const T& ConstReference;
    
    
    Array(int rows=0, int cols=0);
    Array(int rows, int cols, const T &value);
    Array(const Array &that);
    Array(Array &&that);

    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);

    int size() const { return m_data!=nullptr ? m_data->size() : 0; }
    int rows() const { return m_data!=nullptr ? m_data->rows() : 0; }
    int cols() const { return m_data!=nullptr ? m_data->cols() : 0; }

    Pointer operator[] (int k) { return m_data->mat_at(k); }
    ConstPointer operator[] (int k) const { return m_data->mat_at(k); }
    Reference at(int k) { return m_data->vec_at(k); }
    ConstReference at(int k) const { return m_data->vec_at(k); }

    Pointer c_ptr() { return m_data!=nullptr ? m_data->c_ptr() : nullptr; }
    ConstPointer c_ptr() const { return m_data!=nullptr ? m_data->c_ptr() : nullptr; }


private:
    
    Array<0,T> *m_data;
};


template <typename T>
Array<2,T>::Array(int rows, int cols)
{
    if (rows > 0 && cols > 0) {
        m_data = new Array<0,T>(rows, cols, Array<0,T>::Matrix);
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<2,T>::Array(int rows, int cols, const T &value)
{
    if (rows > 0 && cols > 0) {
        m_data = new Array<0,T>(rows, cols, Array<0,T>::Matrix);
        for (int k=0; k<this->size(); ++k) {
            m_data->vec_at(k) = value;
        }
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<2,T>::Array(const Array<2,T> &that)
{
    if (that.m_data !=  nullptr) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<2,T>::Array(Array<2,T> &&that)
{
    if (that.m_data !=  nullptr) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename T>
Array<2,T>::~Array()
{
    if (m_data) {
        m_data->unref();
    }
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (const Array<2,T> &that)
{
    if (m_data != that.m_data) {
        if (m_data) {
            m_data->unref();
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        }
        else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (Array<2,T> &&that)
{
    if (m_data != that.m_data) {
        if (m_data) {
            m_data->unref();
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        }
        else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename T> inline std::ostream&
operator << (std::ostream &out, const Array<2,T> &mat)
{
    int m = mat.rows();
    int n = mat.cols() - 1;

    out << "[[";
    if (n >= 0) {
        for (int i=0; i<m; ++i) {
            if (i > 0) out << " [";
            for (int j=0; j<n; ++j) {
                out << mat[i][j] << ", ";
            }
            if (i < m-1) out << mat[i][n] << ']' << std::endl;
            else out << mat[i][n];
        }
    }
    out << "]]";
    return out;
}


/*****************************************************
 * Functions for matrix creation
 *****************************************************/


template <typename T=double> inline
Array<2,T> zeros(int rows, int cols)
{
    return std::move(Array<2,T>(rows, cols, T(0)));
}


template <typename T=double> inline
Array<2,T> ones(int rows, int cols)
{
    return std::move(Array<2,T>(rows, cols, T(1)));
}


template <typename T=double> inline
Array<2,T> randmat(int rows, int cols, const T &factor=T(1))
{
    Array<2,T> ret(rows, cols);
    for (int k=0; k<ret.size(); ++k) {
        ret.at(k) = T(factor * double(rand())/RAND_MAX);
    }
    return ret;
}


template <typename T> inline
Array<2,T> samesize(const Array<2,T> &mat)
{
    return std::move(Array<2,T>(mat.rows(), mat.cols()));
}


template <typename T> inline
Array<2,T> minsize(const Array<2,T> &mat1, const Array<2,T> &mat2)
{
    return std::move(Array<2,T>(
        qMin(mat1.rows(), mat2.rows()),
        qMin(mat1.cols(), mat2.cols())));
}


template <typename T> inline
Array<2,T> maxsize(const Array<2,T> &mat1, const Array<2,T> &mat2)
{
    return std::move(Array<2,T>(
        qMax(mat1.rows(), mat2.rows()),
        qMax(mat1.cols(), mat2.cols())));
}


/*****************************************************
 * Get array-like views of rows and columns
 *****************************************************/


template <typename T> inline
Array<1,T> row(const Array<2,T> &mat, int k)
{
    Array<1,T> ret;
    ret.m_data = new Array<0,T>(
        mat.rows(), mat.cols(),
        Array<0,T>::RowVector|Array<0,T>::IsView);
    ret.m_data->m_data = (T*) mat.c_ptr() + k*mat.rows();
    return std::move(ret);
}


template <typename T> inline
Array<1,T> col(const Array<2,T> &mat, int k)
{
    Array<1,T> ret;
    ret.m_data = new Array<0,T>(
        mat.rows(), mat.cols(),
        Array<0,T>::ColumnVector|Array<0,T>::IsView);
    ret.m_data->m_data = (T*) mat.c_ptr() + k;
    return std::move(ret);
}


/*****************************************************
 * Functions that apply to arrays of any size
 *****************************************************/


template <typename Func, int D, typename T> inline
void apply(Func func, Array<D,T> &array)
{
    for (int k=0; k<array.size(); ++k) {
        array.at(k) = func(array.at(k));
    }
}


template <typename Func, int D, typename T> inline
Array<D,T> applied(Func func, const Array<D,T> &array)
{
    Array<D,T> ret = samesize(array);
    for (int k=0; k<ret.size(); ++k) {
        ret.at(k) = func(array.at(k));
    }
    return std::move(ret);
}


template <int D, typename T> inline
Array<D,T> copy(const Array<D,T> &arr)
{
    Array<D,T> ret = samesize(arr);
    for (int k=0; k<ret.size(); ++k) {
        ret.at(k) = arr.at(k);
    }
    return std::move(ret);
}



/********************************************
 * Common math functions applied element-wise
 *******************************************/

/// @brief Apply sin() to each element.
template <int D, typename T>
inline Array<D,T> sin(const Array<D,T> &array)
{ return std::move(applied(Math::sin, array)); }

/// @brief Apply cos() to each element.
template <int D, typename T>
inline Array<D,T> cos(const Array<D,T> &array)
{ return std::move(applied(Math::cos, array)); }

/// @brief Apply tan() to each element.
template <int D, typename T>
inline Array<D,T> tan(const Array<D,T> &array)
{ return std::move(applied(Math::tan, array)); }

/// @brief Apply asin() to each element.
template <int D, typename T>
inline Array<D,T> asin(const Array<D,T> &array)
{ return std::move(applied(Math::asin, array)); }

/// @brief Apply acos() to each element.
template <int D, typename T>
inline Array<D,T> acos(const Array<D,T> &array)
{ return std::move(applied(Math::acos, array)); }

/// @brief Apply atan() to each element.
template <int D, typename T>
inline Array<D,T> atan(const Array<D,T> &array)
{ return std::move(applied(Math::atan, array)); }

/// @brief Apply log() to each element.
template <int D, typename T>
inline Array<D,T> log(const Array<D,T> &array)
{ return std::move(applied(Math::log, array)); }

/// @brief Apply log10() to each element.
template <int D, typename T>
inline Array<D,T> log10(const Array<D,T> &array)
{ return std::move(applied(Math::log10, array)); }

/// @brief Apply exp() to each element.
template <int D, typename T>
inline Array<D,T> exp(const Array<D,T> &array)
{ return std::move(applied(Math::exp, array)); }

} // namespace Ksl

#endif // KSL_ARRAY_H
