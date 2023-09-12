#ifndef CPP1_S21_MATRIXPLUS_7_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_7_S21_MATRIX_OOP_H

#include <cmath>
#include <cstring>  //for memcpy
#include <iostream>

namespace S21 {
class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(const int rows, const int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  virtual ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  bool operator!=(const S21Matrix &other) const;

  void SumMatrix(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);

  void SubMatrix(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);

  void MulMatrix(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other);

  void MulNumber(const double num) noexcept;
  S21Matrix operator*(const double &x) const;
  friend S21Matrix operator*(const double &x, const S21Matrix &other);
  S21Matrix &operator*=(const double &x) noexcept;

  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  int GetCols() const noexcept;
  int GetRows() const noexcept;
  void SetCols(const int cols);
  void SetRows(const int rows);

  double &operator()(const int &i, const int &j);
  const double &operator()(const int &i, const int &j) const;

  friend std::ostream &operator<<(std::ostream &out, const S21Matrix &other);
  friend std::istream &operator>>(std::istream &in, S21Matrix &other);

 private:
  void CreateMinor(const int skip_i, const int skip_j, const S21Matrix &other);

  int rows_, cols_;
  double **matrix_;
};
}  // namespace S21
#endif
