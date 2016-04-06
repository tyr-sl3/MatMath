#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "IMatrix.h" // IMatrix

#include <algorithm> // std::for_each
#include <array>     // std::array
#include <cassert>   // assert

//! @class Matrix
//! @brief Non-resizable matrix allocated on the stack
//! @see IMatrix
template <typename T, unsigned H, unsigned W>
class Matrix final : public IMatrix<T> {
public:
  //! @brief Default ctor
  //! @throws Anything std::fill can throw
  Matrix();

  //! @brief Ctor
  //! @param mat Matrix as initializer_list
  //! @pre mat.size() must be equal to H * W
  //! @throws Anything std::copy can throw
  Matrix(std::initializer_list<T> const& mat);

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
  //! @throws Anything as long as NO_TYPE_CHECK is not defined
  T operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) override;

  //! @brief Static method returning indentity matrix
  //! @returns Indentity matrix
  //! @code
  //! auto mat = Matrix<int, 3, 3>::identity();
  //! @endcode
  //! @throws Anything Matrix ctor can throw
  static Matrix identity();

  Matrix& operator+=(T const& val) noexcept(TYPE_CHECKED);
  Matrix& operator-=(T const& val) noexcept(TYPE_CHECKED);
  Matrix& operator*=(T const& val) noexcept(TYPE_CHECKED);
  Matrix& operator/=(T const& val) noexcept(TYPE_CHECKED);

private:
  std::array<T, H * W> buffer_;
};

template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>::Matrix() {
  std::fill(buffer_.begin(), buffer_.end(), T{});
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>::Matrix(std::initializer_list<T> const& mat) {
  static_assert(H > 0, "Matrix height must be superior than 0");
  static_assert(W > 0, "Matrix width must be superior than 0");
  assert(mat.size() == H * W && "Invalid matrix size");
  std::copy(mat.begin(), mat.end(), buffer_.begin());
}
template <typename T, unsigned H, unsigned W>
unsigned Matrix<T, H, W>::width() const noexcept {
  return W;
}
template <typename T, unsigned H, unsigned W>
unsigned Matrix<T, H, W>::height() const noexcept {
  return H;
}
template <typename T, unsigned H, unsigned W>
T& Matrix<T, H, W>::operator()(unsigned y, unsigned x) noexcept {
  assert(y < H && "Out of bounds");
  assert(x < W && "Out of bounds");
  return buffer_[y * W + x];
}
template <typename T, unsigned H, unsigned W>
T Matrix<T, H, W>::operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) {
  assert(y < H && "Out of bounds");
  assert(x < W && "Out of bounds");
  return buffer_[y * W + x];
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W> Matrix<T, H, W>::identity() {
  static_assert(H > 0, "Matrix height must be superior than 0");
  static_assert(W > 0, "Matrix width must be superior than 0");
  static_assert(H == W, "Can't get identity matrix with H != W");
  Matrix<T, H, W> mat;
  for (unsigned i{}; i < W; i++) {
    mat(i, i) = 1;
  }
  return mat;
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>& Matrix<T, H, W>::operator+=(T const& val) noexcept(TYPE_CHECKED) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v += val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>& Matrix<T, H, W>::operator-=(T const& val) noexcept(TYPE_CHECKED) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v -= val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>& Matrix<T, H, W>::operator*=(T const& val) noexcept(TYPE_CHECKED) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v *= val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
Matrix<T, H, W>& Matrix<T, H, W>::operator/=(T const& val) noexcept(TYPE_CHECKED) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v /= val; });
  return *this;
}

template <typename T, unsigned H, unsigned W, typename Fun>
inline auto apply(Matrix<T, H, W> const& m1, Matrix<T, H, W> const& m2, Fun f) noexcept(TYPE_CHECKED) {
  Matrix<T, H, W> mat;
  for (unsigned j{}; j < mat.height(); j++) {
    for (unsigned i{}; i < mat.width(); i++) {
       mat(j, i) = f(m1(j, i), m2(j, i));
    }
  }
  return mat;
}

template <typename T, unsigned H, unsigned W>
auto operator+(Matrix<T, H, W> const& m1, Matrix<T, H, W> const& m2) noexcept {
  return apply(m1, m2, [](T const& a, T const& b) { return a + b; });
}

template <typename T, unsigned H, unsigned W>
auto operator-(Matrix<T, H, W> const& m1, Matrix<T, H, W> const& m2) noexcept {
  return apply(m1, m2, [](T const& a, T const& b) { return a - b; });
}

template <typename T, unsigned H, unsigned W>
auto operator+(Matrix<T, H, W> const& m, T const& val) noexcept(TYPE_CHECKED) {
  auto mat = m;
  return (mat += val);
}

template <typename T, unsigned H, unsigned W>
auto operator-(Matrix<T, H, W> const& m, T const& val) noexcept(TYPE_CHECKED) {
  auto mat = m;
  return (mat -= val);
}

template <typename T, unsigned H, unsigned W>
auto operator*(Matrix<T, H, W> const& m, T const& val) noexcept(TYPE_CHECKED) {
  auto mat = m;
  return (mat *= val);
}

template <typename T, unsigned H, unsigned W>
auto operator/(Matrix<T, H, W> const& m, T const& val) noexcept(TYPE_CHECKED) {
  auto mat = m;
  return (mat /= val);
}

template <typename T, unsigned M, unsigned N, unsigned P>
Matrix<T, M, P> operator*(Matrix<T, M, N> const& m1, Matrix<T, N, P> const& m2) noexcept {
  Matrix<T, M, P> result;
  for (unsigned j{}; j < m1.height(); j++) {
    for (unsigned i{}; i < m2.width(); i++) {
      for (unsigned inner{}; inner < m1.width(); inner++) {
        result(j, i) += m1(j, inner) * m2(inner, i);
      }
    }
  }
  return result;
}

template <typename T, unsigned M1, unsigned N1, unsigned M2, unsigned N2>
Matrix<T, M1, N2> operator*(Matrix<T, M1, N1> const&, Matrix<T, M2, N2> const&) noexcept {
  static_assert(N1 == M2, "Invalid matrix size for operator*");
  return Matrix<T, M1, N2>{};
}

#endif // __MATRIX_H__
