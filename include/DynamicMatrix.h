#ifndef __DYNAMIC_MATRIX_H__
#define __DYNAMIC_MATRIX_H__

#include <IMatrix.h> // IMatrix 

#include <algorithm> // std::for_each
#include <cassert>   // assert
#include <vector>    // std::vector

namespace mat {

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

} // namespace mat

#include <impl/DynamicMatrix_impl.tpp> // Implementation 
#include <impl/DynamicMatrix_op.tpp>   // Operators 

#endif // __DYNAMIC_MATRIX_H__
