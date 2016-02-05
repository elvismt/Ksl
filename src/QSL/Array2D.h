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

#ifndef QSL_ARRAY2D_H
#define QSL_ARRAY2D_H

#include <QSL/Array1D.h>
#include <ostream>

QSL_BEGIN_NAMESPACE

template <typename T>
class Array2D
{
public:

    typedef T Data;
    typedef T* Pointer;
    typedef const T* ConstPointer;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Iterator;
    typedef const T* ConstIterator;


    Array2D()
        : m_data(nullptr)
        , m_rows(0)
        , m_cols(0)
        , m_view(false)
    { }

    Array2D(quint64 m, quint64 n)
        : m_data(new Data[m*n])
        , m_rows(m)
        , m_cols(n)
        , m_view(false)
    { }

    Array2D(const Array2D &that)
        : m_data(that.m_data)
        , m_rows(that.m_rows)
        , m_cols(that.m_cols)
        , m_view(true)
    { }

    Array2D(Array2D &&that)
        : m_data(that.m_data)
        , m_rows(that.m_rows)
        , m_cols(that.m_cols)
        , m_view(true)
    {
        if (!that.m_view) {
            that.m_view = true;
            this->m_view = false;
        }
    }

    Array2D(std::initializer_list<Array1D<Data>> initlist)
    {
        m_rows = initlist.size();
        m_cols = initlist.begin()->size();
        m_data = new Data[m_rows*m_cols];
        m_view = false;

        auto iter = this->begin();
        for (auto &array : initlist) {
            for (auto &elem : array) {
                *iter++ = elem;
            }
        }
    }


    ~Array2D() {
        if (m_data && !m_view) {
            delete[] m_data;
        }
    }


    quint64 rows() const {
        return m_rows;
    }

    quint64 cols() const {
        return m_cols;
    }

    quint64 count() const {
        return m_rows * m_cols;
    }

    Reference operator() (quint64 row, quint64 col) {
        return m_data[row*m_cols+col];
    }

    ConstReference operator() (quint64 row, quint64 col) const {
        return m_data[row*m_cols+col];
    }

    Iterator begin() {
       return m_data;
    }

    Iterator end() {
       return m_data + (m_rows*m_cols);
    }

    ConstIterator begin() const {
       return m_data;
    }

    ConstIterator end() const {
       return m_data + (m_rows*m_cols);
    }


private:

    Pointer m_data;
    quint64 m_rows;
    quint64 m_cols;
    bool m_view;
};

typedef Array2D<double> array2d;


template <typename T = double>
inline Array2D<T> zeros(quint64 rows, quint64 cols) {
    Array2D<T> array(rows, cols);
    for (quint64 k=0; k<array.count(); k++) {
        array(0,k) = T(0);
    }
    return std::move(array);
}


QSL_END_NAMESPACE


template <typename T>
inline std::ostream& operator << (std::ostream &os, QSL::Array2D<T> &A)
{
    for (quint64 i=0; i<A.rows(); i++) {
        os << "( ";
        for (quint64 j=0; j<A.cols()-1; j++) {
            os << A(i,j) << ", ";
        }
        os << A(i,A.cols()-1) << " )" << std::endl;
    }
    return os;
}

#endif // QSL_ARRAY2D_H
