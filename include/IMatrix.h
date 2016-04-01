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
#ifndef NO_TYPE_CHECK
  static_assert(std::is_arithmetic<T>::value, "Invalid type: expected arithmetic type");
#endif // NO_TYPE_CHECK

public:
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
  //! @param y  Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @throws /
  virtual T& operator()(unsigned y, unsigned x) noexcept = 0;

  //! @brief Indexer (read only)
  //! @param y  Y index
  //! @param x X index
  //! @returns Value at (y, x)
  //! @throws Nothing as long as NO_TYPE_CHECK is not defined
  virtual T operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) = 0;
};

#endif // __IMATRIX_H__
