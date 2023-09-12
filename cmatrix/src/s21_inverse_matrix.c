#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!check_invalidity_of_matrix(A) || result == NULL) return 1;
  if (A->rows != A->columns) return 2;
  matrix_t tmp = {0}, tmp2 = {0};
  double determinant = 0.0;
  s21_determinant(A, &determinant);
  if (determinant == 0.0) return 2;
  s21_calc_complements(A, &tmp);
  s21_transpose(&tmp, &tmp2);
  s21_mult_number(&tmp2, 1 / determinant, result);
  s21_remove_matrix(&tmp);
  s21_remove_matrix(&tmp2);
  return 0;
}