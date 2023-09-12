#include "s21_matrix.h"

/*минор матрицы равен детерминанту n-1 матриц */

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!check_invalidity_of_matrix(A) || result == NULL) return 1;
  if (A->rows != A->columns) return 2;
  matrix_t tmp = {0};
  s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->rows; j++) {
      create_minor(i, j, &tmp, A);
      result->matrix[i][j] = find_determinant(tmp) * pow(-1, i + j + 2);
    }
  s21_remove_matrix(&tmp);
  return 0;
}
