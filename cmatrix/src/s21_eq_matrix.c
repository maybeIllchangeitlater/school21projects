#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if ((mxs_not_valid_for_comparison(A, B)) != 0) return FAILURE;
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1.e-7) result = FAILURE;
  return result;
}