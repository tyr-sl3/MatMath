// apply is not a MatMath API function
namespace _ {

template <typename T, typename Fun>
inline auto apply(mat::IMatrix<T> const& m1, mat::IMatrix<T> const& m2, Fun f) {
  assert(m1.height() == m2.height() && "Invalid size");
  assert(m1.width() == m2.width() && "Invalid size");
  mat::DynamicMatrix<T> mat(m1.height(), m1.width());
  for (unsigned j{}; j < mat.height(); j++) {
    for (unsigned i{}; i < mat.width(); i++) {
       mat(j, i) = f(m1(j, i), m2(j, i));
    }
  }
  return mat;
}

} // namespace _

template <typename T>
inline mat::DynamicMatrix<T> operator+(mat::IMatrix<T> const& m1, mat::IMatrix<T> const& m2) {
  return _::apply(m1, m2, [](T const& a, T const& b) { return a + b; });
}

template <typename T>
inline mat::DynamicMatrix<T> operator-(mat::IMatrix<T> const& m1, mat::IMatrix<T> const& m2) {
  return _::apply(m1, m2, [](T const& a, T const& b) { return a - b; });
}

template <typename T>
inline mat::DynamicMatrix<T> operator+(mat::DynamicMatrix<T> const& m, T const& val) {
  mat::DynamicMatrix<T> mat = m;
  return (mat += val);
}

template <typename T>
inline mat::DynamicMatrix<T> operator-(mat::DynamicMatrix<T> const& m, T const& val) {
  mat::DynamicMatrix<T> mat = m;
  return (mat -= val);
}

template <typename T>
inline mat::DynamicMatrix<T> operator*(mat::DynamicMatrix<T> const& m, T const& val) {
  mat::DynamicMatrix<T> mat = m;
  return (mat *= val);
}

template <typename T>
inline mat::DynamicMatrix<T> operator/(mat::DynamicMatrix<T> const& m, T const& val) {
  mat::DynamicMatrix<T>  mat = m;
  return (mat /= val);
}

template <typename T>
inline mat::DynamicMatrix<T> operator+(T const& val, mat::DynamicMatrix<T> const& m) {
  return m + val;
}

template <typename T>
inline mat::DynamicMatrix<T> operator-(T const& val, mat::DynamicMatrix<T> const& m) {
  return m - val;
}

template <typename T>
inline mat::DynamicMatrix<T> operator*(T const& val, mat::DynamicMatrix<T> const& m) {
  return m * val;
}

template <typename T>
inline mat::DynamicMatrix<T> operator*(mat::IMatrix<T> const& m1, mat::IMatrix<T> const& m2) {
  assert(m1.width() == m2.height() && "Invalid matrix size");
  mat::DynamicMatrix<T> result(m1.height(), m2.width());
  for (unsigned j{}; j < m1.height(); j++) {
    for (unsigned i{}; i < m2.width(); i++) {
      for (unsigned inner{}; inner < m1.width(); inner++) {
        result(j, i) += m1(j, inner) * m2(inner, i);
      }
    }
  }
  return result;
}