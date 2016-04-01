# MatMath
C++ API for math operations on matrices.
There's two types of matrices :
- Matrix: Buffer allocated on the stack => Exception safety
- DynamicMatrix: Buffer allocated on the heap => No exception safety

# Code examples
Usage of Matrix:
```cpp
const Matrix<int, 3, 3> mat1 = {
  1, 2, 3,
  4, 5, 6,
  7, 8, 9
};
const Matrix<int, 3, 3> mat2 = {
  3, 2, 1,
  6, 5, 4,
  9, 8, 7
};
const auto product = mat1 * mat2;
const auto identity = Matrix<int, 4, 4>::identity();
```

Usage of DynamicMatrix:
```cpp
DynamicMatrix<int> mat1(3, 3);
mat1 = {
  1, 2, 3,
  4, 5, 6,
  7, 8, 9
};
DynamicMatrix<int> mat2(2, 2);
mat2 = {
  1, 2,
  3, 4
};
mat2.resize(3, 3);
const auto product = mat1 * mat2;
```

# Todo list
- Add comments for Doxygen doc
- Add missing operations (matrix determinant, etc)
