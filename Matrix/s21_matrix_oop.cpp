#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error("Matrix size is mistake");
  }

  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix copy(other);
    *this = std::move(copy);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix::~S21Matrix() {
  delete[] matrix_;
  matrix_ = nullptr;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool flag = true;

  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    flag = false;
    throw std::length_error("Matrix is nothing");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    flag = false;
    throw std::length_error("Matrix size is nothing");
  } else {
    for (int i = 0; i < rows_ && flag; i++)
      for (int j = 0; j < cols_ && flag; j++)
        if (std::abs(matrix_[i * cols_ + j] - other.matrix_[i * cols_ + j]) >=
            EPSILON)
          flag = false;
  }

  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::length_error("Matrix is nothing");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error("Matrix size is mistake");
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        matrix_[i * cols_ + j] += other.matrix_[i * cols_ + j];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::length_error("Matrix is nothing");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error("Matrix size is mistake");
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        matrix_[i * cols_ + j] -= other.matrix_[i * cols_ + j];
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i * cols_ + j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::length_error("Matrix size is mistake");
  } else {
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < other.cols_; j++)
        for (int k = 0; k < cols_; k++)
          res.matrix_[i * other.cols_ + j] +=
              matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];

    *this = std::move(res);
  }
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      res.matrix_[j * rows_ + i] = matrix_[i * cols_ + j];

  return res;
}

S21Matrix S21Matrix::GetMinor(int skip_row, int skip_col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  int r = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i == skip_row) continue;
    int c = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == skip_col) continue;
      minor(r, c) = (*this)(i, j);
      c++;
    }
    r++;
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::length_error("Matrix size is mistake");
  } else if (rows_ == 1) {
    return (*this)(0, 0);
  } else if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else if (rows_ > 2) {
    double res = 0.0;
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = GetMinor(0, j);
      double cofactor = (j % 2 == 0 ? 1 : -1) * (*this)(0, j);
      res += cofactor * minor.Determinant();
    }
    return res;
  } else {
    return 0;
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::length_error("Matrix size is mistake");
  } else {
    S21Matrix res(rows_, cols_);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = GetMinor(i, j);
        double temp = minor.Determinant();
        res(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * temp;
      }
    }
    return res;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0 || std::abs(det) < 1e-6) {
    throw std::length_error("Determinant bad");
  } else {
    S21Matrix calcMatrix = CalcComplements();

    S21Matrix calcTranspose = calcMatrix.Transpose();

    S21Matrix inverse(rows_, cols_);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) inverse(i, j) = calcTranspose(i, j) / det;

    return inverse;
  }
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::length_error("Incorrect index");

  return matrix_[row * cols_ + col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::length_error("Incorrect index");

  return matrix_[row * cols_ + col];
}

void S21Matrix::Resize(int new_rows, int new_cols) {
  S21Matrix new_matrix(new_rows, new_cols);

  int copy_rows = std::min(rows_, new_rows);
  int copy_cols = std::min(cols_, new_cols);

  for (int i = 0; i < copy_rows; i++) {
    for (int j = 0; j < copy_cols; j++) {
      new_matrix(i, j) = (*this)(i, j);
    }
  }

  *this = std::move(new_matrix);
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(double number) const noexcept {
  S21Matrix res(*this);
  res.MulNumber(number);
  return res;
}

S21Matrix operator*(double number, const S21Matrix &other) noexcept {
  S21Matrix res = other * number;
  return res;
}

S21Matrix &S21Matrix::operator*=(double number) noexcept {
  MulNumber(number);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}