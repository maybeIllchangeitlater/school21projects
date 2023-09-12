#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = 0;
  if (!(columns > 0 && rows > 0 && result != NULL)) {
    status = 1;
  }
  if (!status) {
    result->matrix = NULL;
    result->rows = rows;
    result->columns = columns;
  }
  if (!status)
    if (!(result->matrix = calloc(rows, sizeof(double *)))) {
      status = 1, result->matrix = NULL;
    }
  for (int i = 0; i < rows && !status; i++)
    if (!(result->matrix[i] = calloc(columns, sizeof(double)))) {
      result->rows = i, status = 1;
      s21_remove_matrix(result);
    }
  return status;
}