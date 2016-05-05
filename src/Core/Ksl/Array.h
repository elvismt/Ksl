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
#include <ostream>
#include <initializer_list>
#include <cstdlib>

namespace Ksl {

/***************************************************
 * All array types in Ksl are specializations
 * of this template class
 **************************************************/
template <int D, typename T=double> class Array{};


/*********************************************
 * This is a reference counting storage engine 
 * for the other array types
 *********************************************/
template <typename Tp>
class Array<0,Tp>
{
public:
    
    Array(int rows, int cols);
    Array(int rows, int cols, const Tp &initValue);
    ~Array();
    
    int rows() const { return m_rows; }
    int cols() const { return m_cols; }
    int size() const { return m_rows*m_cols; }
    int capacity() const { return m_allocSize; }

    Tp& valueAt(int idx) { return m_data[idx]; }
    const Tp& valueAt(int idx) const { return m_data[idx]; }

    Tp* rowAt(int idx) { return m_data + (idx*m_cols); }
    const Tp* rowAt(int idx) const { return m_data + (idx*m_cols); }

    Tp* begin() { return m_data; }
    const Tp* begin() const { return m_data; }
    
    Tp* end() { return m_data + m_rows*m_cols; }
    const Tp* end() const { return m_data + m_rows*m_cols; }

    void alloc(int rows, int cols);
    void resize(int rows, int cols);
    void reserve(int size);
    void free();
    
    void append(const Tp &value);
    
    Array* ref();
    bool unref();


private:

    int m_rows;
    int m_cols;
    int m_allocSize;
    int m_refCount;
    Tp *m_data;
};


template <typename Tp>
Array<0,Tp>::Array(int rows, int cols) {
    alloc(rows, cols);
    m_refCount = 1;
}


template <typename Tp>
Array<0,Tp>::Array(int rows, int cols, const Tp &initValue) {
    alloc(rows, cols);
    m_refCount = 1;
    for (auto &x : *this) {
        x = initValue;
    }
}


template <typename Tp>
Array<0,Tp>::~Array() {
    free();
}


template <typename Tp>
void Array<0,Tp>::alloc(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        m_rows = rows;
        m_cols = cols;
        m_allocSize = rows*cols;
        m_data = (Tp*) std::malloc(
            (std::size_t) m_allocSize *sizeof(Tp));
    } else {
        m_rows = 0;
        m_cols = 0;
        m_allocSize = 0;
        m_data = nullptr;
    }
}


template <typename Tp>
void Array<0,Tp>::resize(int rows, int cols) {
    if (rows >= 0 && cols >= 0) {
        m_rows = rows;
        m_cols = cols;
        if (rows*cols > m_allocSize) {
            m_allocSize = rows*cols;
            m_data = (Tp*) std::realloc(
                (void*) m_data,
                (std::size_t) m_allocSize *sizeof(Tp));
        }
    }
}


template <typename Tp>
void Array<0,Tp>::reserve(int size) {
    if (size > m_allocSize) {
        if (m_rows == 0) m_rows = 1;
        m_allocSize = size;
        m_data = (Tp*) std::realloc(
            (void*) m_data,
            (std::size_t) m_allocSize *sizeof(Tp));
    }
}


template <typename Tp>
void Array<0,Tp>::append(const Tp &value) {
    if (m_allocSize == 0) {
        reserve(12);
    } else if (m_allocSize == size()) {
        reserve(4*size()/3);
    }
    valueAt(size()) = value;
    m_cols += 1;
}


template <typename Tp>
void Array<0,Tp>::free() {
    if (m_data) {
        std::free(m_data);
    }
    m_data = nullptr;
    m_rows = 0;
    m_cols = 0;
    m_allocSize = 0;
}


template <typename Tp>
Array<0,Tp>* Array<0,Tp>::ref() {
    m_refCount += 1;
    return this;
}


template <typename Tp>
bool Array<0,Tp>::unref() {
    m_refCount -= 1;
    return (m_refCount == 0);
}


template <typename Tp> inline bool
operator== (const Array<0,Tp> &v1, const Array<0,Tp> &v2) {
    if (v1.rows() != v2.rows() ||
        v1.cols() != v2.cols())
    {
        return false;
    }
    for (int k=0; k<v1.size(); ++k) {
        if (v1.valueAt(k) != v2.valueAt(k)) {
            return false;
        }
    }
    return true;
}


/*********************************************
 * This the 1D (vector) array
 *********************************************/
template <typename Tp>
class Array<1,Tp>
{
public:
    
    Array(int size=0);
    Array(int size, const Tp &initValue);
    Array(const Array &that);
    Array(Array &&that);
    Array(std::initializer_list<Tp> initList);
    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);
    
    int size() const { return m_data ? m_data->cols() : 0; }
    int capacity() const { return m_data ? m_data->capacity() : 0; }
    
    Tp& operator[] (int idx) { return m_data->valueAt(idx); }
    const Tp& operator[] (int idx) const { return m_data->valueAt(idx); }
    
    Tp& at(int idx) { return m_data->valueAt(idx); }
    const Tp& at(int idx) const { return m_data->valueAt(idx); }
    
    Tp* begin() { return m_data ? m_data->begin() : nullptr; }
    const Tp* begin() const { return m_data ? m_data->begin() : nullptr; }
    
    Tp* end() { return m_data ? m_data->end() : nullptr; }
    const Tp* end() const { return m_data ? m_data->end() : nullptr; }
    
    Array<0,Tp>* storage() { return m_data; }
    const Array<0,Tp>* storage() const { return m_data; }
    
    void append(const Tp &value);
    void push(const Tp &value);
    void pop();

private:
    
    Array<0,Tp> *m_data;
};


template <typename Tp>
Array<1,Tp>::Array(int size) {
    if (size > 0) {
        m_data = new Array<0,Tp>(1, size);
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<1,Tp>::Array(int size, const Tp &initValue) {
    if (size > 0) {
        m_data = new Array<0,Tp>(1, size, initValue);
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<1,Tp>::Array(const Array<1,Tp> &that) {
    if (that.m_data) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<1,Tp>::Array(Array<1,Tp> &&that) {
    if (that.m_data) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<1,Tp>::Array(std::initializer_list<Tp> initList) {
    if (initList.size() > 0) {
        m_data = new Array<0,Tp>(1, initList.size());
        auto iter = begin();
        for (auto &x : initList) {
            *iter++ = x;
        }
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<1,Tp>::~Array() {
    if (m_data) {
        if (m_data->unref()) {
            delete m_data;
        }
    }
}


template <typename Tp> Array<1,Tp>&
Array<1,Tp>::operator= (const Array<1,Tp> &that) {
    if (m_data != that.m_data) {
        if (m_data) {
            if (m_data->unref()) {
                delete m_data;
            }
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        } else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename Tp> Array<1,Tp>&
Array<1,Tp>::operator= (Array<1,Tp> &&that) {
    if (m_data != that.m_data) {
        if (m_data) {
            if (m_data->unref()) {
                delete m_data;
            }
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        } else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename Tp>
void Array<1,Tp>::append(const Tp &value) {
    if (!m_data) {
        m_data = new Array<0,Tp>(0,0);
    }
    m_data->append(value);
}


template <typename Tp>
void Array<1,Tp>::push(const Tp &value) {
    append(value);
}


template <typename Tp>
void Array<1,Tp>::pop() {
    if (m_data) {
        m_data->resize(1, size()-1);
    }
}


template <typename Tp> inline std::ostream&
operator<< (std::ostream &out, const Array<1,Tp> &array) {
    int n = array.size() - 1;
    out << '[';
    for (int k=0; k<n; ++k) {
        out << array[k] << ", ";
    }
    if (n >= 0) out << array[n] << ']';
    else out << ']';
    return out;
}


/*********************************************
 * 1D array creation functions
 *********************************************/


template <typename Tp=double>
inline Array<1,Tp> zeros(int size) {
    return std::move(Array<1,Tp>(size, Tp(0)));
}


template <typename Tp=double>
inline Array<1,Tp> ones(int size) {
    return std::move(Array<1,Tp>(size, Tp(1)));
}


template <typename Tp=double> inline Array<1,Tp>
linspace(const Tp &start, const Tp &stop, int num) {
    Array<1,Tp> ret(num);
    auto step = (stop-start) / num;
    for (int k=0; k<num; ++k) {
        ret[k] = k * step;
    }
    return std::move(ret);
}


template <typename Tp=double> inline Array<1,Tp>
arange(const Tp &start, const Tp &stop, const Tp &step=Tp(1)) {
    int num = int((stop - start) / step) + 1;
    Array<1,Tp> ret(num);
    for (int k=0; k<num; ++k) {
        ret[k] = k * step;
    }
    return std::move(ret);
}


template <typename Tp=double> inline
Array<1,Tp> randspace(int size, const Tp &max=Tp(1)) {
    Array<1,Tp> ret(size);
    for (int k=0; k<size; ++k) {
        ret[k] = Tp(max * double(std::rand())/RAND_MAX);
    }
    return std::move(ret);
}


template <typename Tp> inline
Array<1,Tp> samesize(const Array<1,Tp> &other) {
    return std::move(Array<1,Tp>(other.size()));
}


/*********************************************
 * This the 2D (matrix) array
 *********************************************/
template <typename Tp>
class Array<2,Tp>
{
public:
    
    Array(int rows=0, int cols=0);
    Array(int rows, int cols, const Tp &initValue);
    Array(const Array &that);
    Array(Array &&that);
    ~Array();

    Array& operator= (const Array &that);
    Array& operator= (Array &&that);
    
    int rows() const { return m_data ? m_data->rows() : 0; }
    int cols() const { return m_data ? m_data->cols() : 0; }
    int size() const { return m_data ? m_data->size() : 0; }
    
    Tp* operator[] (int idx) { return m_data->rowAt(idx); }
    const Tp* operator[] (int idx) const { return m_data->rowAt(idx); }
    
    Tp& at(int idx) { return m_data->valueAt(idx); }
    const Tp& at(int idx) const { return m_data->valueAt(idx); }
    
    Tp* begin() { return m_data ? m_data->begin() : nullptr; }
    const Tp* begin() const { return m_data ? m_data->begin() : nullptr; }
    
    Tp* end() { return m_data ? m_data->end() : nullptr; }
    const Tp* end() const { return m_data ? m_data->end() : nullptr; }
    
    Array<0,Tp>* storage() { return m_data; }
    const Array<0,Tp>* storage() const { return m_data; }


private:
    
    Array<0,Tp> *m_data;
};


template <typename Tp>
Array<2,Tp>::Array(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        m_data = new Array<0,Tp>(rows, cols);
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<2,Tp>::Array(int rows, int cols, const Tp &initValue) {
    if (rows > 0 && cols > 0) {
        m_data = new Array<0,Tp>(rows, cols, initValue);
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<2,Tp>::Array(const Array<2,Tp> &that) {
    if (that.m_data) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<2,Tp>::Array(Array<2,Tp> &&that) {
    if (that.m_data) {
        m_data = that.m_data->ref();
    } else {
        m_data = nullptr;
    }
}


template <typename Tp>
Array<2,Tp>::~Array() {
    if (m_data) {
        if (m_data->unref()) {
            delete m_data;
        }
    }
}


template <typename Tp> Array<2,Tp>&
Array<2,Tp>::operator= (const Array<2,Tp> &that) {
    if (m_data != that.m_data) {
        if (m_data) {
            if (m_data->unref()) {
                delete m_data;
            }
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        } else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename Tp> Array<2,Tp>&
Array<2,Tp>::operator= (Array<2,Tp> &&that) {
    if (m_data != that.m_data) {
        if (m_data) {
            if (m_data->unref()) {
                delete m_data;
            }
        }
        if (that.m_data) {
            m_data = that.m_data->ref();
        } else {
            m_data = nullptr;
        }
    }
    return *this;
}


template <typename Tp> inline std::ostream&
operator<< (std::ostream &out, const Array<2,Tp> &array) {
    int m = array.rows();
    int n = array.cols() - 1;
    out << "[[";
    for (int i=0; i<m; ++i) {
        if (i != 0) out << " [";
        for (int j=0; j<n; ++j) {
            out << array[i][j] << ", ";
        }
        if (n >= 0) out << array[i][n];
        if (i < (m-1)) out << ']' << std::endl;
    }
    out << "]]";
    return out;
}


/*********************************************
 * 2D array creation functions
 *********************************************/


template <typename Tp=double>
inline Array<2,Tp> zeros(int rows, int cols) {
    return std::move(Array<2,Tp>(rows, cols, Tp(0)));
}


template <typename Tp=double>
inline Array<2,Tp> ones(int rows, int cols) {
    return std::move(Array<2,Tp>(rows, cols, Tp(1)));
}


template <typename Tp=double>
inline Array<2,Tp> identity(int rows, const Tp &factor) {
    Array<2,Tp> ret(rows, rows, Tp(0));
    for (int k=0; k<rows; ++k) {
        ret[k][k] = factor;
    }
    return std::move(ret);
}


template <typename Tp>
inline Array<2,Tp> samesize(const Array<2,Tp> &other) {
    return std::move(Array<2,Tp>(other.rows(), other.cols()));
}


template <typename Tp=double> inline
Array<2,Tp> row_stack(std::initializer_list<Array<1,Tp>> initList) {
    int k = 0;
    for (auto &row : initList) {
        if (row.size() > k) {
            k = row.size();
        }
    }
    Array<2,Tp> ret(initList.size(), k, Tp(0));
    k = 0;
    for (auto &row : initList) {
        for (int i=0; i<row.size(); ++i) {
            ret[k][i] = row[i];
        }
        k += 1;
    }
    return std::move(ret);
}


template <typename Tp=double> inline
Array<2,Tp> column_stack(std::initializer_list<Array<1,Tp>> initList) {
    int k = 0;
    for (auto &column : initList) {
        if (column.size() > k) {
            k = column.size();
        }
    }
    Array<2,Tp> ret(k, initList.size(), Tp(0));
    k = 0;
    for (auto &column : initList) {
        for (int i=0; i<column.size(); ++i) {
            ret[i][k] = column[i];
        }
        k += 1;
    }
    return std::move(ret);
}


/****************************************************
 * This array view is used by visualization tools to
 * hold a reference to the data they must show
 ****************************************************/
template <typename Tp>
class ArrayView
{
public:

    enum Type {
        RowView,
        ColumnView
    };


    ArrayView();
    ArrayView(const ArrayView &that);
    ArrayView(const Array<1,Tp> &rowVector);
    ArrayView(const Array<0,Tp> *storage, int type, int rowOrCol);

    ArrayView& operator= (const Array<1,Tp> &rowVector);
    ArrayView& operator= (const ArrayView<Tp> &that);

    ~ArrayView();

    int size() const;

    const Tp& operator[] (int idx) const;


private:

    Array<0,Tp> *m_storage;
    int m_type;
    int m_rowOrCol;
};


template <typename Tp>
ArrayView<Tp>::ArrayView() {
    m_storage = nullptr;
}


template <typename Tp>
ArrayView<Tp>::ArrayView(const ArrayView<Tp> &that) {
    if (that.m_storage) {
        m_storage = const_cast<Array<0,Tp>*>
            (that.m_storage)->ref();
    } else {
        m_storage = nullptr;
    }
    m_type = that.m_type;
    m_rowOrCol = that.m_rowOrCol;
}


template <typename Tp>
ArrayView<Tp>::ArrayView(const Array<1,Tp> &rowVector) {
    if (rowVector.storage()) {
        m_storage = const_cast<Array<0,Tp>*>
            (rowVector.storage())->ref();
    } else {
        m_storage = nullptr;
    }
    m_type = RowView;
    m_rowOrCol = 0;
}


template <typename Tp>
ArrayView<Tp>::ArrayView(const Array<0,Tp> *storage,
                         int type, int rowOrCol)
{
    if (storage) {
        m_storage = const_cast<Array<0,Tp>*>
            (storage)->ref();
    } else {
        m_storage = nullptr;
    }
    m_type = type;
    m_rowOrCol = rowOrCol;
}


template <typename Tp>
ArrayView<Tp>& ArrayView<Tp>::operator= (const Array<1,Tp> &rowVector) {
    if (m_storage != rowVector.storage()) {
        if (m_storage) {
            if (const_cast<Array<0,Tp>*>
                (m_storage)->unref())
            {
                delete m_storage;
            }
        }
        if (rowVector.storage()) {
            m_storage = const_cast<Array<0,Tp>*>
                (rowVector.storage())->ref();
        } else {
            m_storage = nullptr;
        }
        m_type = RowView;
        m_rowOrCol = 0;
    }
    return *this;
}


template <typename Tp>
ArrayView<Tp>& ArrayView<Tp>::operator= (const ArrayView<Tp> &that) {
    if (m_storage != that.m_storage) {
        if (m_storage) {
            if (const_cast<Array<0,Tp>*>
                (m_storage)->unref())
            {
                delete m_storage;
            }
        }
        if (that.m_storage) {
            m_storage = const_cast<Array<0,Tp>*>
                (that.m_storage)->ref();
        } else {
            m_storage = nullptr;
        }
        m_type = that.m_type;
        m_rowOrCol = that.m_rowOrCol;
    }
    return *this;
}


template <typename Tp>
ArrayView<Tp>::~ArrayView() {
    if (m_storage) {
        if (const_cast<Array<0,Tp>*>
            (m_storage)->unref())
        {
            delete m_storage;
        }
    }
}


template <typename Tp>
int ArrayView<Tp>::size() const {
    if (!m_storage) {
        return 0;
    }
    if (m_type == RowView) {
        return m_storage->cols();
    } // else: m_type == ColumnView
    return m_storage->rows();
}


template <typename Tp>
const Tp& ArrayView<Tp>::operator[] (int idx) const {
    if (m_type == RowView) {
        return m_storage->valueAt(m_rowOrCol*m_storage->cols() + idx);
    } // else: m_type == ColumnView
    return m_storage->valueAt(m_rowOrCol + idx*m_storage->cols());
}


template <typename Tp> inline
ArrayView<Tp> row(const Array<2,Tp> &matrix, int idx) {
    return ArrayView<Tp>(
        matrix.storage(),
        ArrayView<Tp>::RowView,
        idx);
}


template <typename Tp> inline
ArrayView<Tp> col(const Array<2,Tp> &matrix, int idx) {
    return ArrayView<Tp>(
        matrix.storage(),
        ArrayView<Tp>::ColumnView,
        idx);
}


/*********************************************
 * Functions that can be applyed to arrays
 * of any dimension
 *********************************************/


template <int D, typename Tp>
inline Array<D,Tp> copy(const Array<D,Tp> &other) {
    auto ret = samesize(other);
    for (int k=0; k<ret.size(); ++k) {
        ret.at(k) = other.at(k);
    }
    return std::move(ret);
}


template <int D, typename Tp> inline bool
operator== (const Array<D,Tp> &v1, const Array<D,Tp> &v2) {
    if (v1.storage() == v2.storage()) {
        return true;
    }
    return (*v1.storage()) == (*v1.storage());
}


template <int D, typename Tp> inline bool
operator!= (const Array<D,Tp> &v1, const Array<D,Tp> &v2) {
    if (v1.storage() == v2.storage()) {
        return false;
    }
    return !((*v1.storage()) == (*v1.storage()));
}

} // namespace Ksl

#endif // KSL_ARRAY_H
