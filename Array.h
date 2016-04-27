#ifndef KSL_ARRAY_H
#define KSL_ARRAY_H

#include <cstdlib>
#include <ostream>
#include <initializer_list>


/***************************************************************************************
 * Base template class for Arrays
 **************************************************************************************/

template<
   int dimension,
   typename element_type=double
>
class Array{ /* dummy */ };


/***************************************************************************************
 * Array view for use with visualization tools
 **************************************************************************************/

template<
   typename element_type=double
>
class ArrayView;


/***************************************************************************************
 * 1D Array (vector) class
 **************************************************************************************/

template <typename _Tp>
class Array<0,_Tp>
{
private:
  
  typedef _Tp           value_type;
  typedef _Tp*          pointer;
  typedef const _Tp*    const_pointer;
  typedef _Tp&          reference;
  typedef const _Tp&    const_reference;
  typedef int           size_type;
  typedef int           index_type;

   friend class Array<1,_Tp>;
   friend class Array<2,_Tp>;
   friend class ArrayView<_Tp>;

   Array(size_type rows, size_type cols);
   
   size_type rows() const { return m_rows; }
   size_type cols() const { return m_cols; }
   size_type size() const { return m_rows*m_cols; }

   reference vec_at(index_type k) { return m_data[k]; }
   const_reference vec_at(index_type k) const { return m_data[k]; }
   
   pointer mat_at(index_type k) { return m_data + k*m_cols; }
   const_pointer mat_at(index_type k) const { return m_data + k*m_cols; }

   void alloc(size_type rows, size_type cols);
   void resize(size_type rows, size_type cols);
   void reserve(size_type size);
   void append(const value_type &value);
   void extend(const Array &that);
   void free();

   Array* ref();
   bool unref();

   size_type m_rows;
   size_type m_cols;
   size_type m_allocSize;
   size_type m_refCount;
   pointer m_data;
};


template <typename T>
Array<0,T>::Array(size_type rows, size_type cols)
{
   alloc(rows, cols);
}


template <typename T>
void Array<0,T>::alloc(size_type rows, size_type cols)
{
   m_rows = rows;
   m_cols = cols;
   m_allocSize = rows*cols;
   m_refCount = 1;
   if (m_allocSize > 0) {
      m_data = (pointer) std::malloc(
            (std::size_t) m_allocSize * sizeof(T));
   } else {
      m_data = nullptr;
      m_allocSize = 0;
   }
}


template <typename T>
void Array<0,T>::resize(size_type rows, size_type cols)
{
   size_type newAlloc = rows*cols;
   if (newAlloc > m_allocSize) {
      m_data = (pointer) std::realloc(
            (void*) m_data,
            (std::size_t) newAlloc * sizeof(T));
      m_allocSize = newAlloc;
   }
   if (newAlloc > 0) {
      m_rows = rows;
      m_cols = cols;
   }
}


template <typename T>
void Array<0,T>::reserve(size_type size)
{
   if (size > m_allocSize) {
      m_data = (pointer) std::realloc(
            (void*) m_data,
            (std::size_t) size * sizeof(T));
      m_allocSize = size;
   }
}


template <typename T>
void Array<0,T>::append(const value_type &value)
{
   if (m_cols == 0) {
      reserve(12);
   }
   if (m_cols == m_allocSize) {
      reserve(4*m_cols/3);
   }
   this->vec_at(m_cols) = value;
   m_cols += 1;
}


template <typename T>
void Array<0,T>::extend(const Array<0,T> &that)
{
   if (that.size() == 0) {
      return;
   }
   index_type s1 = this->size();
   index_type s2 = that.size();
   reserve(s1+s2);
   for (index_type k=0; k<s2; ++k) {
      this->vec_at(s1+k) = that.vec_at(k);
   }
   m_cols += s2;
}


template <typename T>
void Array<0,T>::free()
{
   if (m_data != nullptr) {
      std::free(m_data);
   }
   m_data = nullptr;
   m_rows = 0;
   m_cols = 0;
}


template <typename T>
Array<0,T>* Array<0,T>::ref()
{
   m_refCount += 1;
   return this;
}


template <typename T>
bool Array<0,T>::unref()
{
   m_refCount -= 1;
   if (m_refCount == 0) {
      free();
      return true;
   }
   return false;
}



/***************************************************************************************
 * 1D Array (vector) class
 **************************************************************************************/

template <typename _Tp>
class Array<1,_Tp>
{
public:
  
  typedef typename Array<0,_Tp>::value_type          value_type;
  typedef typename Array<0,_Tp>::pointer             pointer;
  typedef typename Array<0,_Tp>::const_pointer       const_pointer;
  typedef typename Array<0,_Tp>::reference           reference;
  typedef typename Array<0,_Tp>::const_reference     const_reference;
  typedef typename Array<0,_Tp>::size_type           size_type;
  typedef typename Array<0,_Tp>::index_type          index_type;
  typedef typename Array<0,_Tp>::pointer             iterator;
  typedef typename Array<0,_Tp>::const_pointer       const_iterator;


   Array(size_type size=0);
   Array(size_type size, const value_type &init_value);
   Array(const Array &that);
   Array(Array &&that);

   ~Array();

   Array& operator= (const Array &that);
   Array& operator= (Array &&that);

   size_type size() const { return m_data!=nullptr ? m_data->size() : 0; }

   reference operator[] (index_type k) { return m_data->vec_at(k); }
   const_reference operator[] (index_type k) const { return m_data->vec_at(k); }

   reference at(index_type k) { return m_data->vec_at(k); }
   const_reference at(index_type k) const { return m_data->vec_at(k); }

   iterator begin() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   iterator end() { return m_data!=nullptr ? m_data->m_data+size() : nullptr; }

   const_iterator begin() const { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const_iterator end() const { return m_data!=nullptr ? m_data->m_data+size() : nullptr; }

   pointer c_ptr() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const_pointer c_ptr() const { return m_data!=nullptr ? m_data->m_data : nullptr; }

   void append(const value_type &value);
   void extend(const Array &that);


private:

   Array<0,_Tp> *m_data;
};


template <typename T>
Array<1,T>::Array(size_type size)
{
   if (size > 0) {
      m_data = new Array<0,T>(1,size);
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<1,T>::Array(size_type size, const value_type &init_value)
{
   if (size > 0) {
      m_data = new Array<0,T>(1,size);
      for (auto &x : *this) {
         x = init_value;
      }
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<1,T>::Array(const Array<1,T> &that)
{
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
}


template <typename T>
Array<1,T>::Array(Array<1,T> &&that)
{
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
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
Array<1,T>& Array<1,T>::operator= (const Array<1,T> &that)
{
   if (m_data == that.m_data) {
      return *this;
   }
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
   return *this;
}


template <typename T>
Array<1,T>& Array<1,T>::operator= (Array<1,T> &&that)
{
   if (m_data == that.m_data) {
      return *this;
   }
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
   return *this;
}


template <typename T>
void Array<1,T>::append(const value_type &value)
{
   if (m_data == nullptr) {
      m_data = new Array<0,T>(1,0);
   }
   m_data->append(value);
}


template <typename T>
void Array<1,T>::extend(const Array<1,T> &that)
{
   if (that.m_data == nullptr) {
      return;
   }
   if (m_data == nullptr) {
      m_data = new Array<0,T>(1,0);
   }
   m_data->extend(*that.m_data);
}


template <typename T> inline
std::ostream& operator<< (std::ostream &out, const Array<1,T> &v)
{
   typename Array<1,T>::size_type n = v.size() - 1;
   out << '[';
   for (decltype(n) k=0; k<n; ++k) {
      out << v.at(k) << ", ";
   }
   if (n >= 0) out << v.at(n);
   out << ']';
   return out;
}


/***************************************************************************************
 * Functions for 1D array creation
 **************************************************************************************/

template <typename T=double> inline
Array<1,T> zeros(int size)
{
   Array<1,T> ret(size, T(0));
   return std::move(ret);
}


template <typename T=double> inline
Array<1,T> ones(int size)
{
   Array<1,T> ret(size, T(1));
   return std::move(ret);
}


template <typename T=double> inline
Array<1,T> base(int order, int size)
{
   Array<1,T> ret(size, T(0));
   ret[order] = T(1);
   return std::move(ret);
}


template <typename T=double> inline
Array<1,T> linspace(const T &min, const T &max, const T &step=T(1))
{
   Array<1,T> ret(int((max-min)/step)+1);
   for (int k=0; k<ret.size(); ++k) {
      ret[k] = min + k*step;
   }
   return std::move(ret);
}


/***************************************************************************************
 * 1D Array (vector) class
 **************************************************************************************/

template <typename _Tp>
class Array<2,_Tp>
{
public:
  
  typedef typename Array<0,_Tp>::value_type          value_type;
  typedef typename Array<0,_Tp>::pointer             pointer;
  typedef typename Array<0,_Tp>::const_pointer       const_pointer;
  typedef typename Array<0,_Tp>::reference           reference;
  typedef typename Array<0,_Tp>::const_reference     const_reference;
  typedef typename Array<0,_Tp>::size_type           size_type;
  typedef typename Array<0,_Tp>::index_type          index_type;
  typedef typename Array<0,_Tp>::pointer             iterator;
  typedef typename Array<0,_Tp>::const_pointer       const_iterator;


   Array(size_type rows, size_type cols);
   Array(size_type rows, size_type cols, const value_type &init_value);
   Array(const Array &that);
   Array(Array &&that);

   ~Array();

   Array& operator= (const Array &that);
   Array& operator= (Array &&that);

   size_type size() const { return m_data!=nullptr ? m_data->size() : 0; }
   size_type rows() const { return m_data!=nullptr ? m_data->rows() : 0; }
   size_type cols() const { return m_data!=nullptr ? m_data->cols() : 0; }

   pointer operator[] (index_type k) { return m_data->mat_at(k); }
   const_pointer operator[] (index_type k) const { return m_data->mat_at(k); }

   reference at(index_type k) { return m_data->vec_at(k); }
   const_reference at(index_type k) const { return m_data->vec_at(k); }

   iterator begin() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   iterator end() { return m_data!=nullptr ? m_data->m_data+size() : nullptr; }

   const_iterator begin() const { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const_iterator end() const { return m_data!=nullptr ? m_data->m_data+size() : nullptr; }

   pointer c_ptr() { return m_data!=nullptr ? m_data->m_data : nullptr; }
   const_pointer c_ptr() const { return m_data!=nullptr ? m_data->m_data : nullptr; }

   void append(const value_type &value);
   void extend(const Array &that);


private:

   Array<0,_Tp> *m_data;
};


template <typename T>
Array<2,T>::Array(size_type rows, size_type cols)
{
   if (rows > 0 && cols > 0) {
      m_data = new Array<0,T>(rows,cols);
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::Array(size_type rows, size_type cols, const value_type &init_value)
{
   if (rows > 0 && cols > 0) {
      m_data = new Array<0,T>(rows,cols);
      for (auto &x : *this) {
         x = init_value;
      }
   } else {
      m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::Array(const Array<2,T> &that)
{
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
}


template <typename T>
Array<2,T>::Array(Array<2,T> &&that)
{
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
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
   if (m_data == that.m_data) {
      return *this;
   }
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
   return *this;
}


template <typename T>
Array<2,T>& Array<2,T>::operator= (Array<2,T> &&that)
{
   if (m_data == that.m_data) {
      return *this;
   }
   if (m_data != nullptr) {
      if (m_data->unref()) {
         delete m_data;
      }
   }
   if (that.m_data != nullptr) {
      this->m_data = that.m_data->ref();
   } else {
      this->m_data = nullptr;
   }
   return *this;
}


template <typename T> inline
std::ostream& operator<< (std::ostream &out, const Array<2,T> &v)
{
   typename Array<2,T>::size_type m = v.rows();
   typename Array<2,T>::size_type n = v.cols() - 1;

   for (decltype(m) i=0; i<m; ++i) {
      if (i==0) out << "[[";
      else out << " [";
      for (decltype(n) j=0; j<n; ++j) {
         out << v[i][j] << ", ";
      }
      if (i==(m-1)) out << v[i][n] << "]]";
      else out << v[i][n] << ']' << std::endl;
   }
   return out;
}


/***************************************************************************************
 * Functions for 2D array creation
 **************************************************************************************/

template <typename T=double> inline
Array<2,T> zeros(int rows, int cols)
{
   Array<2,T> ret(rows, cols, T(0));
   return std::move(ret);
}


template <typename T=double> inline
Array<2,T> ones(int rows, int cols)
{
   Array<2,T> ret(rows, cols, T(1));
   return std::move(ret);
}


template <typename T=double> inline
Array<2,T> identity(int size)
{
   Array<2,T> ret(size, size, T(0));
   for (int k=0; k<size; ++k) {
      ret[k][k] = T(1);
   }
   return std::move(ret);
}

#endif // KSL_ARRAY_H

