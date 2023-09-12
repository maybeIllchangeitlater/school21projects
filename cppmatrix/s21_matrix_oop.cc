#include "s21_matrix_oop.h"

namespace S21 {
S21Matrix::S21Matrix() : rows_(5), cols_(5) {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

S21Matrix::S21Matrix(const int rows, const int cols)
    : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) throw std::length_error("Invalid Matrix size");
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (other.matrix_ == nullptr)
    matrix_ = nullptr;
  else {
    matrix_ = new double *[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
      std::memcpy(matrix_[i], other.matrix_[i], sizeof(double) * cols_);
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  cols_ = other.cols_;
  rows_ = other.rows_;
  if (other.matrix_ == nullptr)
    matrix_ = nullptr;
  else {
    matrix_ = new double *[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
      std::memcpy(matrix_[i], other.matrix_[i], sizeof(double) * cols_);
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  bool result = true;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1.e-7)
        result = false;
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices should have the same size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
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

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices should have the same size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
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

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Amount of columns of the first matrix should be equal to amount of "
        "rows of the second matrix");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < other.rows_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  *this = std::move(result);
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

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

S21Matrix S21Matrix::operator*(const double &x) const {
  S21Matrix res(*this);
  res.MulNumber(x);
  return res;
}
S21Matrix operator*(const double &x, const S21Matrix &other) {
  S21Matrix res(other);
  res.MulNumber(x);
  return res;
}

S21Matrix &S21Matrix::operator*=(const double &x) noexcept {
  MulNumber(x);
  return *this;
}

S21Matrix S21Matrix::Transpose() const {
  if (matrix_ == nullptr) throw std::invalid_argument("Matrix is NULL");
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[j][i] = matrix_[i][j];
  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::logic_error("The matrix is not square");
  if (rows_ == 1) return matrix_[0][0];
  int current_start = 0;
  double first = 0.0;
  double det = 1.0;
  S21Matrix tmp(*this);
  for (; current_start < tmp.rows_ && det != 0.0; current_start++) {
    int i = current_start;
    if (fabs(tmp.matrix_[current_start][current_start]) < 1e-7) {
      for (; i < tmp.rows_ && fabs(tmp.matrix_[i][current_start]) < 1e-7; i++)
        ;
      i == tmp.rows_ ? det = 0.0 : det *= -1,
                       std::swap(tmp.matrix_[current_start], tmp.matrix_[i]);
    }
    det *= tmp.matrix_[current_start][current_start];
    for (int row = current_start; row < tmp.rows_; row++) {
      first = tmp.matrix_[row][current_start];
      for (int col = current_start; col < tmp.cols_; col++) {
        row == current_start
            ? tmp.matrix_[row][col] /= first
            : tmp.matrix_[row][col] -= tmp.matrix_[current_start][col] * first;
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::logic_error("The matrix is not square");
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1;
    return res;
  }
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < rows_; j++) {
      tmp.CreateMinor(i, j, *this);
      res.matrix_[i][j] = tmp.Determinant() * pow(-1, i + j + 2);
    }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = this->Determinant();
  if (determinant == 0.0) throw std::logic_error("Matrix determinant is 0");
  S21Matrix tmp;
  S21Matrix res;
  tmp = this->CalcComplements();
  res = tmp.Transpose();
  res *= 1.0 / determinant;
  return res;
}

int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

void S21Matrix::SetCols(const int cols) {
  if (cols == cols_) return;
  if (cols <= 0) throw std::length_error("Invalid Matrix size");
  S21Matrix tmp(rows_, cols);
  for (int i = 0; i < rows_; i++)
    std::memcpy(
        tmp.matrix_[i], matrix_[i],
        cols_ < cols ? cols_ * sizeof(double *) : cols * sizeof(double *));
  *this = std::move(tmp);
}

void S21Matrix::SetRows(const int rows) {
  if (rows == rows_) return;
  if (rows <= 0) throw std::length_error("Invalid Matrix size");
  S21Matrix tmp(rows, cols_);
  for (int i = 0; i < rows_ && i < rows; i++)
    std::memcpy(tmp.matrix_[i], matrix_[i], cols_ * sizeof(double *));
  *this = std::move(tmp);
}

double &S21Matrix::operator()(const int &i, const int &j) {
  if (matrix_ == nullptr) throw std::invalid_argument("Matrix is NULL");
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::out_of_range("Out of Matrix bounds");
  return matrix_[i][j];
}

const double &S21Matrix::operator()(const int &i, const int &j) const {
  if (matrix_ == nullptr) throw std::invalid_argument("Matrix is NULL");
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::out_of_range("Out of Matrix bounds");
  return matrix_[i][j];
}

std::ostream &operator<<(std::ostream &out, const S21Matrix &other) {
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) out << other(i, j) << " ";
    out << std::endl;
  }
  return out;
}

std::istream &operator>>(std::istream &in, S21Matrix &other) {
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) in >> other(i, j);
  }
  return in;
}

void S21Matrix::CreateMinor(const int skip_i, const int skip_j,
                            const S21Matrix &other) {
  int x = 0, y = 0;
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.rows_; j++) {
      if (i != skip_i && j != skip_j) {
        matrix_[x][y] = other.matrix_[i][j];
        y++;
      }
    }
    y = 0;
    if (i != skip_i) x++;
  }
}
}  // namespace S21
