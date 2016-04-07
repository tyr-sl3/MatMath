#ifndef __IMATRIX_H__
#define __IMATRIX_H__

#include <type_traits> // std::is_arithmetic

#ifndef NO_TYPE_CHECK
constexpr bool TYPE_CHECKED = true;
#else
constexpr bool TYPE_CHECKED = false;
#endif

//! @class IMatrix
//! @brief Interface for matrix classes
template <typename T>
class IMatrix {
  static_assert(!TYPE_CHECKED || std::is_arithmetic<T>::value, "Invalid type: expected arithmetic type");
public:
  using value_type = T;

  //! @brief Default ctor
  IMatrix() = default;

  //! @brief Default dtor (virtual)
  virtual ~IMatrix() = default;

  //! @brief Getter for matrix width
  //! @returns Matrix width
  //! @throws /
  virtual unsigned width() const noexcept = 0;

  //! @brief Getter for matrix height
  //! @returns Matrix height
  //! @throws /
  virtual unsigned height() const noexcept = 0;

  //! @brief Indexer (read / write)
  //! @param y Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @throws /
  virtual T& operator()(unsigned y, unsigned x) noexcept = 0;

  //! @brief Indexer (read only)
  //! @param y Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @throws Nothing as long as NO_TYPE_CHECK is not defined
  virtual T operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) = 0;

  //! @brief Op+=
  //! @param val The value to add to the matrix
  //! @returns Current matrix
  virtual IMatrix& operator+=(T const& val) = 0;

  //! @brief Op-=
  //! @param val The value to substract to the matrix
  //! @returns Current matrix
  virtual IMatrix& operator-=(T const& val) = 0;

  //! @brief Op*=
  //! @param val The value we multiply the matrix by
  //! @returns Current matrix
  virtual IMatrix& operator*=(T const& val) = 0;

  //! @brief Op/=
  //! @param val The value we divide the matrix by
  //! @returns Current matrix
  virtual IMatrix& operator/=(T const& val) = 0;
};

#endif // __IMATRIX_H__
