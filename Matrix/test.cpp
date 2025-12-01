#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;

  EXPECT_EQ(mat.getRows(), 0);
  EXPECT_EQ(mat.getCols(), 0);
}

TEST(S21MatrixTest, ConstructorWithParams) {
  S21Matrix mat(3, 3);

  EXPECT_EQ(mat.getRows(), 3);
  EXPECT_EQ(mat.getCols(), 3);
}

TEST(S21MatrixTest, ConstructorWithInvalidParams) {
  EXPECT_THROW(S21Matrix mat(-1, 3), std::length_error);
  EXPECT_THROW(S21Matrix mat(3, -1), std::length_error);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2 = mat1;

  EXPECT_EQ(mat2.getRows(), mat1.getRows());
  EXPECT_EQ(mat2.getCols(), mat1.getCols());

  for (int i = 0; i < mat1.getRows(); ++i) {
    for (int j = 0; j < mat1.getCols(); ++j) {
      EXPECT_EQ(mat1(i, j), mat2(i, j));
    }
  }
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2 = std::move(mat1);

  EXPECT_EQ(mat2.getRows(), 3);
  EXPECT_EQ(mat2.getCols(), 3);
  EXPECT_EQ(mat1.getRows(), 0);
  EXPECT_EQ(mat1.getCols(), 0);
}

TEST(S21MatrixTest, CopyAssignmentOperator) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(2, 2);
  mat2 = mat1;

  EXPECT_EQ(mat2.getRows(), mat1.getRows());
  EXPECT_EQ(mat2.getCols(), mat1.getCols());

  for (int i = 0; i < mat1.getRows(); ++i) {
    for (int j = 0; j < mat1.getCols(); ++j) {
      EXPECT_EQ(mat1(i, j), mat2(i, j));
    }
  }
}

TEST(S21MatrixTest, MoveAssignmentOperator) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 1;
  mat1(1, 1) = 2;
  mat1(2, 2) = 3;

  S21Matrix mat2(2, 2);
  mat2 = std::move(mat1);

  EXPECT_EQ(mat2(0, 0), 1);
  EXPECT_EQ(mat2(1, 1), 2);
  EXPECT_EQ(mat2(2, 2), 3);

  EXPECT_EQ(mat1(0, 0), 0);
}

TEST(S21MatrixTest, Destructor) {
  EXPECT_NO_THROW({ S21Matrix mat(3, 3); });
}

TEST(S21MatrixTest, EqMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 1.0;
  mat2(0, 1) = 2.0;
  mat2(1, 0) = 3.0;
  mat2(1, 1) = 4.0;

  EXPECT_TRUE(mat1.EqMatrix(mat2));

  mat2(0, 0) = 5.0;
  EXPECT_FALSE(mat1.EqMatrix(mat2));

  S21Matrix mat3(3, 3);
  EXPECT_THROW(mat1.EqMatrix(mat3), std::length_error);

  S21Matrix mat4(0, 0);
  EXPECT_THROW(mat1.SumMatrix(mat4), std::length_error);
}

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1.SumMatrix(mat2);

  EXPECT_EQ(mat1(0, 0), 6.0);
  EXPECT_EQ(mat1(0, 1), 8.0);
  EXPECT_EQ(mat1(1, 0), 10.0);
  EXPECT_EQ(mat1(1, 1), 12.0);

  S21Matrix mat3(0, 0);
  EXPECT_THROW(mat1.SumMatrix(mat3), std::length_error);

  S21Matrix mat4(5, 5);
  EXPECT_THROW(mat1.SumMatrix(mat4), std::length_error);
}

TEST(S21MatrixTest, SubMatrix) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(2, 2);

  mat1(0, 0) = 5;
  mat1(0, 1) = 6;
  mat1(1, 0) = 7;
  mat1(1, 1) = 8;

  mat2(0, 0) = 1;
  mat2(0, 1) = 2;
  mat2(1, 0) = 3;
  mat2(1, 1) = 4;

  mat1.SubMatrix(mat2);

  EXPECT_EQ(mat1(0, 0), 4);
  EXPECT_EQ(mat1(0, 1), 4);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 4);

  S21Matrix mat3(0, 0);
  EXPECT_THROW(mat1.SubMatrix(mat3), std::length_error);

  S21Matrix mat4(5, 5);
  EXPECT_THROW(mat1.SumMatrix(mat4), std::length_error);
}

TEST(S21MatrixTest, MulNumberPositiveMultiplier) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  mat.MulNumber(2.5);

  EXPECT_DOUBLE_EQ(mat(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(mat(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(mat(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(mat(1, 1), 10.0);
}

TEST(S21MatrixTest, MulNumberNegativeMultiplier) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  mat.MulNumber(-1.0);

  EXPECT_DOUBLE_EQ(mat(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(mat(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(mat(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(mat(1, 1), -4.0);
}

TEST(S21MatrixTest, MulNumberZeroMultiplier) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  mat.MulNumber(0.0);

  EXPECT_DOUBLE_EQ(mat(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(mat(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(mat(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(mat(1, 1), 0.0);
}

TEST(S21MatrixTest, MulNumberEmptyMatrix) {
  S21Matrix mat(0, 0);
  EXPECT_NO_THROW(mat.MulNumber(5.0));
}

TEST(S21MatrixTest, MulMatrixValidDimensions) {
  S21Matrix mat1(2, 3);
  mat1(0, 0) = 1;
  mat1(0, 1) = 2;
  mat1(0, 2) = 3;
  mat1(1, 0) = 4;
  mat1(1, 1) = 5;
  mat1(1, 2) = 6;

  S21Matrix mat2(3, 2);
  mat2(0, 0) = 7;
  mat2(0, 1) = 8;
  mat2(1, 0) = 9;
  mat2(1, 1) = 10;
  mat2(2, 0) = 11;
  mat2(2, 1) = 12;

  mat1.MulMatrix(mat2);

  EXPECT_DOUBLE_EQ(mat1(0, 0), 58);
  EXPECT_DOUBLE_EQ(mat1(0, 1), 64);
  EXPECT_DOUBLE_EQ(mat1(1, 0), 139);
  EXPECT_DOUBLE_EQ(mat1(1, 1), 154);
}

TEST(S21MatrixTest, MulMatrixInvalidDimensions) {
  S21Matrix mat1(2, 3);
  S21Matrix mat2(2, 3);

  EXPECT_THROW(mat1.MulMatrix(mat2), std::length_error);
}

TEST(S21MatrixTest, MulMatrixIdentityMatrix) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;

  S21Matrix identity(3, 3);
  identity(0, 0) = 1;
  identity(1, 1) = 1;
  identity(2, 2) = 1;

  mat.MulMatrix(identity);

  EXPECT_DOUBLE_EQ(mat(0, 0), 1);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(0, 2), 3);
  EXPECT_DOUBLE_EQ(mat(1, 0), 4);
  EXPECT_DOUBLE_EQ(mat(1, 1), 5);
  EXPECT_DOUBLE_EQ(mat(1, 2), 6);
  EXPECT_DOUBLE_EQ(mat(2, 0), 7);
  EXPECT_DOUBLE_EQ(mat(2, 1), 8);
  EXPECT_DOUBLE_EQ(mat(2, 2), 9);
}

TEST(S21MatrixTest, TransposeSquareMatrix) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  S21Matrix res = mat.Transpose();

  EXPECT_DOUBLE_EQ(res(0, 0), 1);
  EXPECT_DOUBLE_EQ(res(0, 1), 3);
  EXPECT_DOUBLE_EQ(res(1, 0), 2);
  EXPECT_DOUBLE_EQ(res(1, 1), 4);
}

TEST(S21MatrixTest, TransposeRectangleMatrix) {
  S21Matrix mat(2, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;

  S21Matrix res = mat.Transpose();

  EXPECT_EQ(res.getRows(), 3);
  EXPECT_EQ(res.getCols(), 2);
  EXPECT_DOUBLE_EQ(res(0, 0), 1);
  EXPECT_DOUBLE_EQ(res(0, 1), 4);
  EXPECT_DOUBLE_EQ(res(1, 0), 2);
  EXPECT_DOUBLE_EQ(res(1, 1), 5);
  EXPECT_DOUBLE_EQ(res(2, 0), 3);
  EXPECT_DOUBLE_EQ(res(2, 1), 6);
}

TEST(S21MatrixTest, GetMinorValidIndexes) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;

  S21Matrix minor = mat.GetMinor(1, 1);

  EXPECT_DOUBLE_EQ(minor(0, 0), 1);
  EXPECT_DOUBLE_EQ(minor(0, 1), 3);
  EXPECT_DOUBLE_EQ(minor(1, 0), 7);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9);
}

TEST(S21MatrixTest, Determinant1x1) {
  S21Matrix mat(1, 1);
  mat(0, 0) = 5;

  EXPECT_DOUBLE_EQ(mat.Determinant(), 5);
}

TEST(S21MatrixTest, Determinant2x2) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  EXPECT_DOUBLE_EQ(mat.Determinant(), -2);
}

TEST(S21MatrixTest, Determinant3x3) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 2;
  mat(0, 1) = 4;
  mat(0, 2) = 1;
  mat(1, 0) = 0;
  mat(1, 1) = 3;
  mat(1, 2) = 5;
  mat(2, 0) = 1;
  mat(2, 1) = 2;
  mat(2, 2) = 0;

  EXPECT_DOUBLE_EQ(mat.Determinant(), -3);
}

TEST(S21MatrixTest, DeterminantNonSquare) {
  S21Matrix mat(2, 3);

  EXPECT_THROW(mat.Determinant(), std::length_error);
}

TEST(S21MatrixTest, CalcComplements3x3) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 0;
  mat(1, 1) = 4;
  mat(1, 2) = 2;
  mat(2, 0) = 5;
  mat(2, 1) = 2;
  mat(2, 2) = 1;

  S21Matrix res = mat.CalcComplements();

  EXPECT_DOUBLE_EQ(res(0, 0), 0);
  EXPECT_DOUBLE_EQ(res(0, 1), 10);
  EXPECT_DOUBLE_EQ(res(0, 2), -20);
  EXPECT_DOUBLE_EQ(res(1, 0), 4);
  EXPECT_DOUBLE_EQ(res(1, 1), -14);
  EXPECT_DOUBLE_EQ(res(1, 2), 8);
  EXPECT_DOUBLE_EQ(res(2, 0), -8);
  EXPECT_DOUBLE_EQ(res(2, 1), -2);
  EXPECT_DOUBLE_EQ(res(2, 2), 4);
}

TEST(S21MatrixTest, InverseMatrixValid) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 4;
  mat(0, 1) = 7;
  mat(1, 0) = 2;
  mat(1, 1) = 6;

  S21Matrix inv = mat.InverseMatrix();

  EXPECT_NEAR(inv(0, 0), 0.6, 1e-6);
  EXPECT_NEAR(inv(0, 1), -0.7, 1e-6);
  EXPECT_NEAR(inv(1, 0), -0.2, 1e-6);
  EXPECT_NEAR(inv(1, 1), 0.4, 1e-6);
}

TEST(S21MatrixTest, InverseMatrixSingular) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 2;
  mat(1, 1) = 4;

  EXPECT_THROW(mat.InverseMatrix(), std::length_error);
}

TEST(S21MatrixTest, OperatorAccessValid) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.5;
  mat(1, 1) = 2.5;

  EXPECT_DOUBLE_EQ(mat(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(mat(1, 1), 2.5);

  const S21Matrix& const_mat = mat;
  EXPECT_DOUBLE_EQ(const_mat(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(const_mat(1, 1), 2.5);
}

TEST(S21MatrixTest, OperatorAccessInvalid) {
  S21Matrix mat(2, 2);

  EXPECT_THROW(mat(-1, 0), std::length_error);
  EXPECT_THROW(mat(0, -1), std::length_error);
  EXPECT_THROW(mat(2, 0), std::length_error);
  EXPECT_THROW(mat(0, 2), std::length_error);

  const S21Matrix& const_mat = mat;
  EXPECT_THROW(const_mat(-1, 0), std::length_error);
  EXPECT_THROW(const_mat(0, -1), std::length_error);
  EXPECT_THROW(const_mat(2, 0), std::length_error);
  EXPECT_THROW(const_mat(0, 2), std::length_error);
}

TEST(S21MatrixTest, ResizeToLarger) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  mat.Resize(3, 3);

  EXPECT_EQ(mat.getRows(), 3);
  EXPECT_EQ(mat.getCols(), 3);
  EXPECT_DOUBLE_EQ(mat(0, 0), 1);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(1, 0), 3);
  EXPECT_DOUBLE_EQ(mat(1, 1), 4);
  EXPECT_DOUBLE_EQ(mat(0, 2), 0);
  EXPECT_DOUBLE_EQ(mat(2, 0), 0);
}

TEST(S21MatrixTest, ResizeToSmaller) {
  S21Matrix mat(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat(i, j) = i * 3 + j + 1;
    }
  }

  mat.Resize(2, 2);

  EXPECT_EQ(mat.getRows(), 2);
  EXPECT_EQ(mat.getCols(), 2);
  EXPECT_DOUBLE_EQ(mat(0, 0), 1);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(1, 0), 4);
  EXPECT_DOUBLE_EQ(mat(1, 1), 5);
}

TEST(S21MatrixTest, ResizeToZero) {
  S21Matrix mat(2, 2);
  mat.Resize(0, 0);

  EXPECT_EQ(mat.getRows(), 0);
  EXPECT_EQ(mat.getCols(), 0);
}

TEST(S21MatrixTest, ResizeInvalidDimensions) {
  S21Matrix mat(2, 2);

  EXPECT_THROW(mat.Resize(-1, 2), std::length_error);
  EXPECT_THROW(mat.Resize(2, -1), std::length_error);
  EXPECT_THROW(mat.Resize(-1, -1), std::length_error);
}

TEST(S21MatrixTest, ResizePartialDataPreservation) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  mat.Resize(3, 3);

  EXPECT_DOUBLE_EQ(mat(0, 0), 1);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(1, 0), 3);
  EXPECT_DOUBLE_EQ(mat(1, 1), 4);
  EXPECT_DOUBLE_EQ(mat(0, 2), 0);
}

TEST(S21MatrixTest, OperatorAssignmentThroughAccess) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1.5;
  mat(1, 1) = 2.5;

  mat(0, 1) = mat(1, 1);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2.5);

  (mat(1, 0) = 3.5) = 4.5;
  EXPECT_DOUBLE_EQ(mat(1, 0), 4.5);
}

TEST(S21MatrixTest, EqualityOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  S21Matrix m3(2, 2);
  m3(0, 0) = 1;
  m3(0, 1) = 2;
  m3(1, 0) = 3;
  m3(1, 1) = 5;

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
}

TEST(S21MatrixTest, AdditionOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  S21Matrix res = m1 + m2;

  EXPECT_DOUBLE_EQ(res(0, 0), 6);
  EXPECT_DOUBLE_EQ(res(0, 1), 8);
  EXPECT_DOUBLE_EQ(res(1, 0), 10);
  EXPECT_DOUBLE_EQ(res(1, 1), 12);
}

TEST(S21MatrixTest, AdditionAssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;

  S21Matrix m2(2, 2);
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(1, 0) = 7;
  m2(1, 1) = 8;

  m1 += m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 6);
  EXPECT_DOUBLE_EQ(m1(0, 1), 8);
  EXPECT_DOUBLE_EQ(m1(1, 0), 10);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12);
}

TEST(S21MatrixTest, SubtractionOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 5;
  m1(0, 1) = 6;
  m1(1, 0) = 7;
  m1(1, 1) = 8;

  S21Matrix m2(2, 2);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  S21Matrix res = m1 - m2;

  EXPECT_DOUBLE_EQ(res(0, 0), 4);
  EXPECT_DOUBLE_EQ(res(0, 1), 4);
  EXPECT_DOUBLE_EQ(res(1, 0), 4);
  EXPECT_DOUBLE_EQ(res(1, 1), 4);
}

TEST(S21MatrixTest, SubtractionAssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 5;
  m1(0, 1) = 6;
  m1(1, 0) = 7;
  m1(1, 1) = 8;

  S21Matrix m2(2, 2);
  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  m1 -= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 4);
  EXPECT_DOUBLE_EQ(m1(0, 1), 4);
  EXPECT_DOUBLE_EQ(m1(1, 0), 4);
  EXPECT_DOUBLE_EQ(m1(1, 1), 4);
}

TEST(S21MatrixTest, ScalarMultiplicationOperator) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  S21Matrix res1 = m * 2.5;
  EXPECT_DOUBLE_EQ(res1(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(res1(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(res1(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(res1(1, 1), 10.0);

  S21Matrix res2 = 2.5 * m;
  EXPECT_TRUE(res1 == res2);
}

TEST(S21MatrixTest, ScalarMultiplicationAssignmentOperator) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m *= 2.5;

  EXPECT_DOUBLE_EQ(m(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(m(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 7.5);
  EXPECT_DOUBLE_EQ(m(1, 1), 10.0);
}

TEST(S21MatrixTest, MatrixMultiplicationOperator) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix m2(3, 2);
  m2(0, 0) = 7;
  m2(0, 1) = 8;
  m2(1, 0) = 9;
  m2(1, 1) = 10;
  m2(2, 0) = 11;
  m2(2, 1) = 12;

  S21Matrix res = m1 * m2;

  EXPECT_DOUBLE_EQ(res(0, 0), 58);
  EXPECT_DOUBLE_EQ(res(0, 1), 64);
  EXPECT_DOUBLE_EQ(res(1, 0), 139);
  EXPECT_DOUBLE_EQ(res(1, 1), 154);
}

TEST(S21MatrixTest, MatrixMultiplicationAssignmentOperator) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;

  S21Matrix m2(3, 2);
  m2(0, 0) = 7;
  m2(0, 1) = 8;
  m2(1, 0) = 9;
  m2(1, 1) = 10;
  m2(2, 0) = 11;
  m2(2, 1) = 12;

  m1 *= m2;

  EXPECT_DOUBLE_EQ(m1(0, 0), 58);
  EXPECT_DOUBLE_EQ(m1(0, 1), 64);
  EXPECT_DOUBLE_EQ(m1(1, 0), 139);
  EXPECT_DOUBLE_EQ(m1(1, 1), 154);
}

TEST(S21MatrixTest, OperatorInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_THROW(m1 + m2, std::length_error);
  EXPECT_THROW(m1 - m2, std::length_error);
  EXPECT_THROW(m1 * m2, std::length_error);
  EXPECT_THROW(m1 += m2, std::length_error);
  EXPECT_THROW(m1 -= m2, std::length_error);
  EXPECT_THROW(m1 *= m2, std::length_error);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}