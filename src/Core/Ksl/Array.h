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
template <int D, typename T=double> class Array{};
template <typename T> class ArrayView;


/***************************************************
* Storage engine used by public array types
**************************************************/
template <typename T>
class Array<0,T>
{
private:
   
   friend class Array<1,T>;
   friend class Array<2,T>;
   friend class ArrayView<T>;
   
   enum Type {
      RowVector     = 0x00000001,
      ColumnVector     = 0x00000002,
      Matrix         = 0x00000004,
      IsView        = 0x00000008
   };
   
   
   Array(int rows, int cols, int type);
   
   
   int size() const { return m_rows*m_cols; }
   
   T& vec_at(int idx);
   const T& vec_at(int idx) const;
   
   T* mat_at(int idx);
   const T* mat_at(int idx) const;
   
   
   void resize(int rows, int cols);
   void reserve(int nalloc);
   void append(const T &value);
   void free();
   Array* ref();
   bool unref();
   
   
   int m_type;
   int m_rows;
   int m_cols;
   int m_nalloc;
   int m_refs;
   T *m_data;
};


template <typename T>
Array<0,T>::Array(int rows, int cols, int type)
{
   m_type = type;
   m_refs = 1;
   m_rows = 0;
   m_cols = 0;
   m_data = nullptr;
   resize(rows, cols);
}


template <typename T>
T& Array<0,T>::vec_at(int idx)
{
   return m_data[idx];
}


template <typename T>
const T& Array<0,T>::vec_at(int idx) const
{
   return m_data[idx];
}


template <typename T>
T* Array<0,T>::mat_at(int idx)
{
   return m_data + idx*m_cols;
}


template <typename T>
const T* Array<0,T>::mat_at(int idx) const
{
   return m_data + idx*m_cols;
}


template <typename T>
void Array<0,T>::resize(int rows, int cols)
{
   if (m_type & IsView) {
      return;
   }
   if (rows != m_rows || cols != m_cols) {
      m_rows = rows;
      m_cols = cols;
      m_nalloc = rows*cols;
      if (m_nalloc > 0) {
         if (m_data == nullptr) {
            m_data = (T*) std::malloc((std::size_t) m_nalloc*sizeof(T));
         } else {
            m_data = (T*) std::realloc(
               (void*) m_data,
               (std::size_t) m_nalloc*sizeof(T));
         }
      } else {
         free();
      }
   }
}


template <typename T>
void Array<0,T>::reserve(int nalloc)
{
   if (m_type & IsView) {
      return;
   }
   if (nalloc > 0 && nalloc > m_nalloc) {
      m_nalloc = nalloc;
      if (m_data == nullptr) {
         m_data = (T*) std::malloc((std::size_t) m_nalloc*sizeof(T));
      } else {
         m_data = (T*) std::realloc(
            (void*) m_data,
            (std::size_t) m_nalloc*sizeof(T));
      }
   }
}


template <typename T>
void Array<0,T>::append(const T &value)
{
   if (m_type & IsView) {
      return;
   }
   if (m_type & RowVector) {
      if (m_nalloc < 12) {
         reserve(12);
      } else if (m_nalloc == m_cols) {
         reserve(4*m_cols/3);
      }
      m_data[m_cols] = value;
      m_cols += 1;
   }
}


template <typename T>
void Array<0,T>::free()
{
   if (m_type & IsView) {
      return;
   }
   if (m_data != nullptr) {
      std::free(m_data);
      m_data = nullptr;
   }
}


template <typename T>
Array<0,T>* Array<0,T>::ref()
{
   m_refs += 1;
   return this;
}


template <typename T>
bool Array<0,T>::unref()
{
   m_refs -= 1;
   if (m_refs == 0) {
      free();
      return true;
   }
   return false;
}



/******************************************************
* Array 1D (vector)
******************************************************/


template <typename T>
class Array<1,T>
{
public:
   
   
   Array(int size=0);
   Array(int size, const T &value);
   Array(const Array &that);
   Array(Array &&that);
   
   ~Array();
   
   Array& operator= (const Array &that);
   Array& operator= (Array &&that);
   
   
   int size() const { return m_data!=nullptr ? m_data->size() : 0; }
   
   T& operator[] (int idx) { return m_data->vec_at(idx); }
   const T& operator[] (int idx) const { return m_data->vec_at(idx); }
   
   T& at(int idx) { return m_data->vec_at(idx); }
   const T& at(int idx) const { return m_data->vec_at(idx); }
   
   T* begin() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const T* begin() const { return m_data!=nullptr ? m_data->m_data : nullptr; }
   
   T* end() { return m_data!=nullptr ? m_data->m_data+m_data->size() : nullptr; }
   const T* end() const { return m_data!=nullptr ? m_data->m_data+m_data->size() : nullptr; }
   
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
      m_data = new Array<0,T>(1, size, Array<0,T>::RowVector);
      for (auto &x : *this) {
         x = value;
      }
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<1,T>::Array(const Array<1,T> &that)
{
   if (that.m_data != nullptr) {
      m_data = that.m_data->ref();
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<1,T>::~Array()
{
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
}


template <typename T>
Array<1,T>::Array(Array<1,T> &&that)
{
   if (that.m_data != nullptr) {
      m_data = that.m_data->ref();
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (const Array<1,T> &that)
{
   if (m_data != that.m_data) {
      if (m_data != nullptr) {
         if (m_data->unref()) {
            delete m_data;
         }
      }
      if (that.m_data != nullptr) {
         m_data = that.m_data->ref();
      } else {
         m_data = nullptr;
      }
   }
   return *this;
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (Array<1,T> &&that)
{
   if (m_data != that.m_data) {
      if (m_data != nullptr) {
         if (m_data->unref()) {
            delete m_data;
         }
      }
      if (that.m_data != nullptr) {
         m_data = that.m_data->ref();
      } else {
         m_data = nullptr;
      }
   }
   return *this;
}


template <typename T> inline std::ostream&
operator<< (std::ostream &out, const Array<1,T> &v)
{
   int n = v.size() - 1;
   out << '[';
   for (int k=0; k<n; ++k) {
      out << v[k] << ", ";
   }
   if (n >= 0) out << v[n];
   out << ']';
   return out;
}


template <typename T>
void Array<1,T>::append(const T &value)
{
   if (m_data == nullptr) {
      m_data = new Array<0,T>(1, 1, Array<0,T>::RowVector);
      m_data->m_data[0] = value;
   } else {
      m_data->append(value);
   }
}


template <typename T=double>
Array<1,T> zeros(int size)
{
   Array<1,T> ret(size, T(0));
   return std::move(ret);
}


template <typename T=double>
Array<1,T> ones(int size)
{
   Array<1,T> ret(size, T(1));
   return std::move(ret);
}


template <typename T=double>
Array<1,T> linspace(const T &min, const T &max, const T &step=T(1))
{
   Array<1,T> ret(int((max-min)/step) + 1);
   for (int k=0; k<ret.size(); ++k) {
      ret[k] = k*step;
   }
   return std::move(ret);
}


template <typename T=double>
Array<1,T> randspace(int size, const T &factor=T(1))
{
   Array<1,T> ret(size);
   for (int k=0; k<ret.size(); ++k) {
      ret[k] = T(factor * double(rand())/RAND_MAX);
   }
   return std::move(ret);
}


template <typename T>
Array<1,T> samesize(const Array<1,T> &v)
{
   Array<1,T> ret(v.size());
   return std::move(ret);
}


/******************************************************
* Array 2D (matrix)
******************************************************/


template <typename T>
class Array<2,T>
{
public:
   
   Array(int rows=0, int cols=0);
   Array(int rows, int cols, const T &value);
   Array(const Array<2,T> &that);
   Array(Array<2,T> &&that);
   
   ~Array();
   
   Array& operator= (const Array<2,T> &that);
   Array& operator= (Array<2,T> &&that);
   
   
   int size() const { return m_data!=nullptr ? m_data->size() : 0; }
   int rows() const { return m_data!=nullptr ? m_data->m_rows : 0; }
   int cols() const { return m_data!=nullptr ? m_data->m_cols : 0; }
   
   T* operator[] (int idx) { return m_data->mat_at(idx); }
   const T* operator[] (int idx) const { return m_data->mat_at(idx); }
   
   T& at(int idx) { return m_data->vec_at(idx); }
   const T& at(int idx) const { return m_data->vec_at(idx); }
   
   T* begin() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const T* begin() const { return m_data!=nullptr ? m_data->m_data : nullptr; }
   
   T* end() { return m_data!=nullptr ? m_data->m_data+m_data->size() : nullptr; }
   const T* end() const { return m_data!=nullptr ? m_data->m_data+m_data->size() : nullptr; }
   
   
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
      for (auto &x : *this) {
         x = value;
      }
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::Array(const Array<2,T> &that)
{
   if (that.m_data != nullptr) {
      m_data = that.m_data->ref();
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::Array(Array<2,T> &&that)
{
   if (that.m_data != nullptr) {
      m_data = that.m_data->ref();
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::~Array()
{
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (const Array<2,T> &that)
{
   if (m_data != that.m_data) {
      if (m_data != nullptr) {
         if (m_data->unref()) {
            delete m_data;
         }
      }
      if (that.m_data != nullptr) {
         m_data = that.m_data->ref();
      } else {
         m_data = nullptr;
      }
   }
   return *this;
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (Array<2,T> &&that)
{
   if (m_data != that.m_data) {
      if (m_data != nullptr) {
         if (m_data->unref()) {
            delete m_data;
         }
      }
      if (that.m_data != nullptr) {
         m_data = that.m_data->ref();
      } else {
         m_data = nullptr;
      }
   }
   return *this;
}


template <typename T> inline std::ostream&
operator<< (std::ostream &out, const Array<2,T> &v)
{
   int m = v.rows();
   int n = v.cols() - 1;
   
   if (m <= 0 || n < 0) {
      out << "[[]]";
      return out;
   }
   
   for (int i=0; i<m; ++i) {
      if (i == 0) out << "[[";
      else out << " [";
      for (int j=0; j<n; ++j) {
         out << v[i][j] << ", ";
      }
      if (i == m-1) out << v[i][n] << "]]";
      else out << v[i][n] << ']' << std::endl;
   }
   return out;
}


template <typename T=double>
Array<2,T> zeros(int rows, int cols)
{
   Array<2,T> ret(rows, cols, T(0));
   return std::move(ret);
}


template <typename T=double>
Array<2,T> ones(int rows, int cols)
{
   Array<2,T> ret(rows, cols, T(1));
   return std::move(ret);
}


template <typename T=double>
Array<2,T> identity(int size, const T &factor=T(1))
{
   Array<2,T> ret(size, size);
   for (int i=0; i<size; ++i) {
      for (int j=0; j<size; ++j) {
         ret[i][j] = (i==j) ? factor : T(0);
      }
   }
   return std::move(ret);
}


template <typename T>
Array<2,T> samesize(const Array<2,T> &v)
{
   Array<2,T> ret(v.rows(), v.cols());
   return std::move(ret);
}


template <typename T=double>
Array<2,T> row_stack(std::initializer_list<Array<1,T>> init_list)
{
   int k = 0;
   for (auto &row : init_list) {
      if (row.size() > k) {
         k = row.size();
      }
   }
   
   Array<2,T> ret(init_list.size(), k);
   k = 0;
   for (auto &row : init_list) {
      int j = 0;
      for (const auto &x : row) {
         ret[k][j] = x;
         j += 1;
      }
      k += 1;
   }
   return std::move(ret);
}


template <typename T=double>
Array<2,T> column_stack(std::initializer_list<Array<1,T>> init_list)
{
   int k = 0;
   for (auto &col : init_list) {
      if (col.size() > k) {
         k = col.size();
      }
   }
   
   Array<2,T> ret(k, init_list.size());
   k = 0;
   for (auto &col : init_list) {
      int j = 0;
      for (const auto &x : col) {
         ret[j][k] = x;
         j += 1;
      }
      k += 1;
   }
   return std::move(ret);
}


/*****************************************************************
* Functions that can be applied to arrays of any dimension
****************************************************************/


template <int D, typename T>
inline Array<D,T> copy(const Array<D,T> &v)
{
   auto ret = samesize(v);
   for (int k=0; k<ret.size(); ++k) {
      ret.at(k) = v.at(k);
   }
   return std::move(ret);
}


template <typename Func, int D, typename T>
inline void apply(Func func, const Array<D,T> &v)
{
   for (int k=0; k<v.size(); ++k) {
      v[k] = func(v[k]);
   }
}


template <typename Func, int D, typename T>
inline Array<D,T> applied(Func func, const Array<D,T> &v)
{
   auto y = samesize(v);
   for (int k=0; k<v.size(); ++k) {
      y[k] = func(v[k]);
   }
   return std::move(y);
}


template <int D, typename T>
inline Array<D,T> sin(const Array<D,T> &v)
{ return applied(Math::sin, v); }


template <int D, typename T>
inline Array<D,T> cos(const Array<D,T> &v)
{ return applied(Math::cos, v); }

} // namespace Ksl

#endif // KSL_ARRAY_H
