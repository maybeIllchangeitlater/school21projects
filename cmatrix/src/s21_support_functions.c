#include "s21_matrix.h"

void null_the_result(matrix_t *result) {
  result->columns = 0;
  result->rows = 0;
  result->matrix = S21_NULL;
}

int mxs_not_valid_for_comparison(matrix_t *suspectA, matrix_t *suspectB) {
  return !(check_invalidity_of_matrix(suspectA) &&
           check_invalidity_of_matrix(suspectB))
             ? INCORRECT_MATRIX
         : ((suspectA->rows - suspectB->rows) ||
            (suspectA->columns - suspectB->columns))
             ? CALCULATING_ERROR
             : OK;
}
int check_invalidity_of_matrix(matrix_t *suspect) {
  return (suspect && suspect->columns > 0 &&
          suspect->rows > 0);  //возвращает 0 если говно
}

int check_sub_add_validity(matrix_t *suspectA, matrix_t *suspectB,
                           matrix_t *suspicious_result) {
  int status = OK;
  if (!(check_invalidity_of_matrix(suspectA) &&
        check_invalidity_of_matrix(suspectB) && suspicious_result != NULL))
    status = INCORRECT_MATRIX;
  else if (!(suspectA->rows == suspectB->rows &&
             suspectA->columns == suspectB->columns))
    status = CALCULATING_ERROR;
  return status;
}

int check_multiplicability_of_matrixes(matrix_t *suspectA, matrix_t *suspectB,
                                       matrix_t *suspicious_result) {
  int status = OK;
  if (!(check_invalidity_of_matrix(suspectA) &&
        check_invalidity_of_matrix(suspectB) && suspicious_result != NULL))
    status = INCORRECT_MATRIX;
  else if (suspectA->columns != suspectB->rows)
    status = CALCULATING_ERROR;
  return status;
}

void swap_rows(matrix_t *tmp, int i, int current_start) {
  double d = 0.0;
  for (int j = current_start; j < tmp->rows; j++) {
    d = tmp->matrix[i][j];
    tmp->matrix[i][j] = tmp->matrix[current_start][j];
    tmp->matrix[current_start][j] = d;
  }
}

double find_determinant(matrix_t tmp) {
  int current_start = 0;
  double first = 0.0;
  double det = 1.0;
  for (; current_start < tmp.rows; current_start++) {
    int i = current_start;
    if (fabs(tmp.matrix[current_start][current_start]) < 1e-7) {
      for (; i < tmp.rows && fabs(tmp.matrix[i][current_start]) < 1e-7; i++)
        ;
      if (i == tmp.rows)
        return 0.0;
      else {
        det *= -1;
        swap_rows(&tmp, i, current_start);
      }
    }
    det *= tmp.matrix[current_start][current_start];
    for (int row = current_start; row < tmp.rows; row++) {
      first = tmp.matrix[row][current_start];
      for (int col = current_start; col < tmp.columns; col++) {
        if (row == current_start) {
          tmp.matrix[row][col] /= first;
        } else {
          tmp.matrix[row][col] -= tmp.matrix[current_start][col] * first;
        }
      }
    }
  }
  return det;
}

void create_minor(int skipi, int skipj, matrix_t *tmp, matrix_t *A) {
  int x = 0, y = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      if (i != skipi && j != skipj) {
        tmp->matrix[x][y] = A->matrix[i][j];
        y++;
      }
    }
    y = 0;
    if (i != skipi) x++;
  }
}