#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

#define EPSILON 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;

 public:
  S21Matrix() noexcept;
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  bool operator==(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator*(double number) const noexcept;
  friend S21Matrix operator*(double number, const S21Matrix &other) noexcept;
  S21Matrix &operator*=(double number) noexcept;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other);

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const noexcept;
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double &operator()(int row, int col);
  double operator()(int row, int col) const;
  S21Matrix GetMinor(int skip_row, int skip_col) const;
  void Resize(int new_rows, int new_cols);

  int getRows() const { return rows_; }
  int getCols() const { return cols_; }
};

#endif