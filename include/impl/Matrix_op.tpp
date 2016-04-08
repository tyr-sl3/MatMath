// apply is not a MatMath API function
namespace _ {

template <typename T, unsigned H, unsigned W, typename Fun>
inline mat::Matrix<T, H, W> apply(mat::Matrix<T, H, W> const& m1, mat::Matrix<T, H, W> const& m2, Fun f) {
  mat::Matrix<T, H, W> mat;
  for (unsigned j{}; j < mat.height(); j++) {
    for (unsigned i{}; i < mat.width(); i++) {
      mat(j, i) = f(m1(j, i), m2(j, i));
    }
  }
  return mat;
}

} // namespace _

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator+(mat::Matrix<T, H, W> const& m1, mat::Matrix<T, H, W> const& m2) {
  return _::apply(m1, m2, [](T const& a, T const& b) { return a + b; });
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator-(mat::Matrix<T, H, W> const& m1, mat::Matrix<T, H, W> const& m2) {
  return _::apply(m1, m2, [](T const& a, T const& b) { return a - b; });
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator+(mat::Matrix<T, H, W> const& m, T const& val) {
  auto mat = m;
  return (mat += val);
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator-(mat::Matrix<T, H, W> const& m, T const& val) {
  auto mat = m;
  return (mat -= val);
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator*(mat::Matrix<T, H, W> const& m, T const& val) {
  auto mat = m;
  return (mat *= val);
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator/(mat::Matrix<T, H, W> const& m, T const& val) {
  auto mat = m;
  return (mat /= val);
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator+(T const& val, mat::Matrix<T, H, W> const& m) {
  return m + val;
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator-(T const& val, mat::Matrix<T, H, W> const& m) {
  return m - val;
}

template <typename T, unsigned H, unsigned W>
inline mat::Matrix<T, H, W> operator*(T const& val, mat::Matrix<T, H, W> const& m) {
  return m * val;
}

template <typename T, unsigned M, unsigned N, unsigned P>
inline mat::Matrix<T, M, P> operator*(mat::Matrix<T, M, N> const& m1, mat::Matrix<T, N, P> const& m2) {
  mat::Matrix<T, M, P> result;
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
inline mat::Matrix<T, M1, N2> operator*(mat::Matrix<T, M1, N1> const&, mat::Matrix<T, M2, N2> const&) {
  static_assert(N1 == M2, "Invalid matrix size for operator*");
  return mat::Matrix<T, M1, N2>{};
}
