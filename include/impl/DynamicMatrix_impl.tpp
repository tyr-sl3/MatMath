template <typename T>
mat::DynamicMatrix<T>::DynamicMatrix(unsigned height, unsigned width, T value) : width_(width), height_(height), buffer_(width_ * height_) {
  assert(height > 0 && "Matrix height can't be null");
  assert(width > 0 && "Matrix width can't be null");
  std::fill(buffer_.begin(), buffer_.end(), value);
}
template <typename T>
mat::DynamicMatrix<T>& mat::DynamicMatrix<T>::operator=(std::initializer_list<T> const& mat) {
  assert(mat.size() == height_ * width_ && "Invalid matrix size");
  std::copy(mat.begin(), mat.end(), buffer_.begin());
  return *this;
}
template <typename T>
unsigned mat::DynamicMatrix<T>::width() const noexcept {
  return width_;
}
template <typename T>
unsigned mat::DynamicMatrix<T>::height() const noexcept {
  return height_;
}
template <typename T>
T& mat::DynamicMatrix<T>::operator()(unsigned y, unsigned x) noexcept {
  assert(y < height_ && "Out of bounds");
  assert(x < width_ && "Out of bounds");
  return buffer_[y * width_ + x];
}
template <typename T>
T mat::DynamicMatrix<T>::operator()(unsigned y, unsigned x) const noexcept(TYPE_CHECKED) {
  assert(y < height_ && "Out of bounds");
  assert(x < width_ && "Out of bounds");
  return buffer_[y * width_ + x];
}
template <typename T>
void mat::DynamicMatrix<T>::resize(unsigned height, unsigned width) {
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
mat::DynamicMatrix<T>& mat::DynamicMatrix<T>::operator+=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v += val; });
  return *this;
}
template <typename T>
mat::DynamicMatrix<T>& mat::DynamicMatrix<T>::operator-=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v -= val; });
  return *this;
}
template <typename T>
mat::DynamicMatrix<T>& mat::DynamicMatrix<T>::operator*=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v *= val; });
  return *this;
}
template <typename T>
mat::DynamicMatrix<T>& mat::DynamicMatrix<T>::operator/=(T const& val) {
  std::for_each(buffer_.begin(), buffer_.end(), [&](T& v) { v /= val; });
  return *this;
}