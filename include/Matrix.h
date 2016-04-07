#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <IMatrix.h> // IMatrix

#include <algorithm> // std::for_each
#include <array>     // std::array
#include <cassert>   // assert

namespace mat {
	
//! @class Matrix
//! @brief Non-resizable matrix allocated on the stack
//! @see IMatrix
template <typename T, unsigned H, unsigned W>
class Matrix final : public IMatrix<T> {
  static_assert(H > 0, "Matrix height must be superior than 0");
  static_assert(W > 0, "Matrix width must be superior than 0");
public:
  //! @brief Default ctor
  //! @throws Anything std::fill can throw
  explicit Matrix(T const& val = T{});

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
  //! @throws Nothing as long as NO_TYPE_CHECK is not defined
  T operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) override;

  //! @brief Static method returning indentity matrix
  //! @returns Indentity matrix
  //! @code
  //! auto mat = Matrix<int, 3, 3>::identity();
  //! @endcode
  //! @throws Anything Matrix ctor can throw
  static Matrix identity();

  //! @brief Op+=
  //! @param val The value to add to the matrix
  //! @returns Current matrix
  Matrix& operator+=(T const& val) override;

  //! @brief Op-=
  //! @param val The value to substract to the matrix
  //! @returns Current matrix
  Matrix& operator-=(T const& val) override;

  //! @brief Op*=
  //! @param val The value we multiply the matrix by
  //! @returns Current matrix
  Matrix& operator*=(T const& val) override;

  //! @brief Op/=
  //! @param val The value we divide the matrix by
  //! @returns Current matrix
  Matrix& operator/=(T const& val) override;

private:
  std::array<T, H * W> buffer_;
};

} // namespace mat

#include <impl/Matrix_impl.tpp> // Implementation
#include <impl/Matrix_op.tpp>   // Operators


#endif // __MATRIX_H__
