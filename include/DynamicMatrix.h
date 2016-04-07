#ifndef __DYNAMIC_MATRIX_H__
#define __DYNAMIC_MATRIX_H__

#include "IMatrix.h" // IMatrix

#include <algorithm> // std::for_each
#include <cassert> // assert
#include <vector>  // std::vector

//! @class DynamicMatrix
//! @brief Resizable matrix allocated on the heap (no exception safety for allocations)
//! @see IMatrix
template <typename T>
class DynamicMatrix final : public IMatrix<T> {
public:
  //! @brief Ctor
  //! @param height Matrix height
  //! @param width  Matrix width
  //! @param value  Default value (optional)
  //! @pre Height and width must be superior than 0
  //! @throws Anything std::fill can throw
  DynamicMatrix(unsigned height, unsigned width, T value = T{});

  //! @brief Op=
  //! @param mat Matrix as initializer_list
  //! @returns Current instance
  //! @throws Anything std::copy can throw
  DynamicMatrix& operator=(std::initializer_list<T> const& mat);

  //! @brief Getter for matrix width
  //! @returns Matrix width
  //! @throws /
  unsigned width() const noexcept override;

  //! @brief Getter for matrix height
  //! @returns Matrix height
  //! @throws /
  unsigned height() const noexcept override;

  //! @brief Indexer (read / write)
  //! @param y Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @pre Y must be inferior than matrix height
  //! @pre X must be inferior than matrix width
  //! @throws /
  T& operator()(unsigned y, unsigned x) noexcept override;

  //! @brief Indexer (read only)
  //! @param y Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @pre Y must be inferior than matrix height
  //! @pre X must be inferior than matrix width
  //! @throws Nothing as long as NO_TYPE_CHECK is not defined
  T operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) override;

  //! @brief Resize the matrix
  //! @param height Matrix height
  //! @param width  Matrix width
  //! @pre Height must be superior than 0
  //! @pre Width must be superior than 0
  //! @throws Anything ctor can throw
  void resize(unsigned height, unsigned width);

  //! @brief Op+=
  //! @param val The value to add to the matrix
  //! @returns Current matrix
  DynamicMatrix& operator+=(T const& val) override;

  //! @brief Op-=
  //! @param val The value to substract to the matrix
  //! @returns Current matrix
  DynamicMatrix& operator-=(T const& val) override;

  //! @brief Op*=
  //! @param val The value we multiply the matrix by
  //! @returns Current matrix
  DynamicMatrix& operator*=(T const& val) override;

  //! @brief Op/=
  //! @param val The value we divide the matrix by
  //! @returns Current matrix
  DynamicMatrix& operator/=(T const& val) override;

private:
  unsigned width_;
  unsigned height_;
  std::vector<T> buffer_;
};

template <typename T>
DynamicMatrix<T>::DynamicMatrix(unsigned height, unsigned width, T value) : width_(width), height_(height), buffer_(width_ * height_) {
  assert(height > 0 && "Matrix height can't be null");
  assert(width > 0 && "Matrix width can't be null");
  std::fill(buffer_.begin(), buffer_.end(), value);
}
template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator=(std::initializer_list<T> const& mat) {
  assert(mat.size() == height_ * width_ && "Invalid matrix size");
  std::copy(mat.begin(), mat.end(), buffer_.begin());
  return *this;
}
template <typename T>
unsigned DynamicMatrix<T>::width() const noexcept {
  return width_;
}
template <typename T>
unsigned DynamicMatrix<T>::height() const noexcept {
  return height_;
}
template <typename T>
T& DynamicMatrix<T>::operator()(unsigned y, unsigned x) noexcept {
  assert(y < height_ && "Out of bounds");
  assert(x < width_ && "Out of bounds");
  return buffer_[y * width_ + x];
}
template <typename T>
T DynamicMatrix<T>::operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) {
  assert(y < height_ && "Out of bounds");
  assert(x < width_ && "Out of bounds");
  return buffer_[y * width_ + x];
}
template <typename T>
void DynamicMatrix<T>::resize(unsigned height, unsigned width) {
  assert(height > 0 && "Matrix height can't be null");
  assert(width > 0 && "Matrix width can't be null");
  DynamicMatrix cpy(height, width);
  const auto min_height = height_ < height ? height_ : height;
  const auto min_width = width_ < width ? width_ : width;
  for (unsigned j{}; j < min_height; j++) {
    for (unsigned i{}; i < min_width; i++) {
      cpy(j, i) = (*this)(j, i);
    }
  }
  *this = std::move(cpy);
}
template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator+=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v += val; });
  return *this;
}
template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator-=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v -= val; });
  return *this;
}
template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator*=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v *= val; });
  return *this;
}
template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator/=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v /= val; });
  return *this;
}

template <typename T, typename Fun>
inline auto apply(IMatrix<T> const& m1, IMatrix<T> const& m2, Fun f) {
  assert(m1.height() == m2.height() && "Invalid size");
  assert(m1.width() == m2.width() && "Invalid size");
  DynamicMatrix<T> mat(m1.height(), m1.width());
  for (unsigned j{}; j < mat.height(); j++) {
    for (unsigned i{}; i < mat.width(); i++) {
       mat(j, i) = f(m1(j, i), m2(j, i));
    }
  }
  return mat;
}

template <typename T>
DynamicMatrix<T> operator+(IMatrix<T> const& m1, IMatrix<T> const& m2) {
  return apply(m1, m2, [](T const& a, T const& b) { return a + b; });
}

template <typename T>
DynamicMatrix<T> operator-(IMatrix<T> const& m1, IMatrix<T> const& m2) {
  return apply(m1, m2, [](T const& a, T const& b) { return a - b; });
}

template <typename T>
DynamicMatrix<T> operator+(DynamicMatrix<T> const& m, T const& val) {
  DynamicMatrix<T> mat = m;
  return (mat += val);
}

template <typename T>
DynamicMatrix<T> operator-(DynamicMatrix<T> const& m, T const& val) {
  DynamicMatrix<T> mat = m;
  return (mat -= val);
}

template <typename T>
DynamicMatrix<T> operator*(DynamicMatrix<T> const& m, T const& val) {
  DynamicMatrix<T> mat = m;
  return (mat *= val);
}

template <typename T>
DynamicMatrix<T> operator/(DynamicMatrix<T> const& m, T const& val) {
  DynamicMatrix<T>  mat = m;
  return (mat /= val);
}

template <typename T>
DynamicMatrix<T> operator+(T const& val, DynamicMatrix<T> const& m) {
  return m + val;
}

template <typename T>
DynamicMatrix<T> operator-(T const& val, DynamicMatrix<T> const& m) {
  return m - val;
}

template <typename T>
DynamicMatrix<T> operator*(T const& val, DynamicMatrix<T> const& m) {
  return m * val;
}

template <typename T>
DynamicMatrix<T> operator*(IMatrix<T> const& m1, IMatrix<T> const& m2) {
  assert(m1.width() == m2.height() && "Invalid matrix size");
  DynamicMatrix<T> result(m1.height(), m2.width());
  for (unsigned j{}; j < m1.height(); j++) {
    for (unsigned i{}; i < m2.width(); i++) {
      for (unsigned inner{}; inner < m1.width(); inner++) {
        result(j, i) += m1(j, inner) * m2(inner, i);
      }
    }
  }
  return result;
}

#endif // __DYNAMIC_MATRIX_H__
