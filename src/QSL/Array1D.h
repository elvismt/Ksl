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

#ifndef QSL_ARRAY1D_H
#define QSL_ARRAY1D_H

#include <QSL/Global.h>
#include <QVector>
#include <ostream>

QSL_BEGIN_NAMESPACE

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

   Array1D(quint64 size)
      : m_data(new Data[size])
      , m_size(size)
      , m_view(false)
   { }

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

   Array1D(QVector<Data> &qvec)
       : m_data(qvec.data())
       , m_size(qvec.size())
       , m_view(true)
   { }


   Array1D& operator= (const Array1D<double> &that) {
      if (this->m_data == that.m_data) {
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

   Array1D& operator= (Array1D<double> &&that) {
      if (!that.m_view) {
         that.m_view = true;
         this->m_view = false;
      }
      else {
         this->m_view = true;
      }
      if (this->m_data == that.m_data) {
         return *this;
      }
      if (m_data && !m_view) {
         delete[] m_data;
      }
      m_data = that.m_data;
      m_size = that.m_size;
      return *this;
   }


   ~Array1D() {
      if (m_data && !m_view) {
         delete[] m_data;
      }
   }


   quint64 size() const {
      return m_size;
   }

   bool empty() const {
      return m_size == 0;
   }


   Reference operator[] (quint64 index) {
      return m_data[index];
   }

   ConstReference operator[] (quint64 index) const {
      return m_data[index];
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


   Array1D operator* (const T &x) const {
       Array1D ret = this->copy();
       for (auto &elem : ret) {
           elem *= x;
       }
       return std::move(ret);
   }


   Array1D operator+ (const T &x) const {
       Array1D ret = this->copy();
       for (auto &elem : ret) {
           elem += x;
       }
       return std::move(ret);
   }


   Array1D& operator+= (const T &x) {
       for (auto &elem : *this) {
           elem += x;
       }
       return *this;
   }


   Array1D& operator*= (const T &x) {
       for (auto &elem : *this) {
           elem *= x;
       }
       return *this;
   }


   Array1D copy() const {
       Array1D array(m_size);
       auto iter = array.begin();
       for (auto &elem : *this) {
           *iter++ = elem;
       }
       return std::move(array);
   }


private:

   Pointer m_data;
   quint64 m_size;
   bool m_view;
};

typedef Array1D<double> array1d;


template <typename T = double>
inline Array1D<T> zeros(quint64 size)
{
   Array1D<T> array(size);
   for (auto &elem : array) {
      elem = T(0);
   }
   return std::move(array);
}


QSL_END_NAMESPACE


template <typename T>
inline std::ostream& operator<< (std::ostream &os,
                                 const QSL::Array1D<T> &array)
{
   auto iter = array.begin();
   auto end = array.end() - 1;
   os << "[ ";
   while (iter != end) {
      os << (*iter++) << ", ";
   }
   os << (*iter++) << " ]";
   return os;
}

#endif // QSL_ARRAY1D_H
