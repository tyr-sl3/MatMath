template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W>::Matrix(T const& val) {
  std::fill(buffer_.begin(), buffer_.end(), val);
}
template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W>::Matrix(std::initializer_list<T> const& mat) {
  assert(mat.size() == H * W && "Invalid matrix size");
  std::copy(mat.begin(), mat.end(), buffer_.begin());
}
template <typename T, unsigned H, unsigned W>
unsigned mat::Matrix<T, H, W>::width() const noexcept {
  return W;
}
template <typename T, unsigned H, unsigned W>
unsigned mat::Matrix<T, H, W>::height() const noexcept {
  return H;
}
template <typename T, unsigned H, unsigned W>
T& mat::Matrix<T, H, W>::operator()(unsigned y, unsigned x) noexcept {
  assert(y < H && "Out of bounds");
  assert(x < W && "Out of bounds");
  return buffer_[y * W + x];
}
template <typename T, unsigned H, unsigned W>
T mat::Matrix<T, H, W>::operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) {
  assert(y < H && "Out of bounds");
  assert(x < W && "Out of bounds");
  return buffer_[y * W + x];
}
template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W> mat::Matrix<T, H, W>::identity() {
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
mat::Matrix<T, H, W>& mat::Matrix<T, H, W>::operator+=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v += val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W>& mat::Matrix<T, H, W>::operator-=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v -= val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W>& mat::Matrix<T, H, W>::operator*=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v *= val; });
  return *this;
}
template <typename T, unsigned H, unsigned W>
mat::Matrix<T, H, W>& mat::Matrix<T, H, W>::operator/=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v /= val; });
  return *this;
}