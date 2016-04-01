#include <iostream> // std::cout, std::cin, std::ostream

#include "Matrix.h"        // Matrix
#include "DynamicMatrix.h" // DynamicMatrix

template <typename T>
std::ostream& operator<<(std::ostream& stream, IMatrix<T> const& mat) {
  for (unsigned j{}; j < mat.height(); j++) {
    for (unsigned i{}; i < mat.width(); i++) {
      stream << mat(j, i) << " ";
    }
    stream << "\n";
  }
  return stream;
}

template <typename T>
using Mat33 = Matrix<T, 3, 3>;

int main() {
  Mat33<int> mat1 = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  std::cout << "mat1:\n" << mat1 << "\n";
  Mat33<int> mat2 = {
    3, 2, 1,
    6, 5, 4,
    9, 8, 7
  };
  std::cout << "mat2:\n" << mat2 << "\n";
  DynamicMatrix<int> mat3(3, 3);
  mat3 = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  std::cout << "mat3:\n" << mat3 << "\n";
  // We can multiply Matrix<T, H, W> by DynamicMatrix<T> if their dimensions are equal
  const auto product = mat1 * mat3;
  mat3.resize(5, 5);
  /*
  mat3:
  1, 2, 3, 0, 0,
  4, 5, 6, 0, 0,
  7, 8, 9, 0, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
  */
  std::cin.get();
}
