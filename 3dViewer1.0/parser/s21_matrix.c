#include "s21_matrix.h"

int allocate_dynamic_matrix(matrix_t *result);
int s21_check_matrix_is_correct(matrix_t *A);

int s21_check_equal_size(matrix_t *A, matrix_t *B) {
  return (A->columns == B->columns) && (A->rows == B->rows);
}

int s21_check_matrix_is_correct(matrix_t *A) {
  int ret = (A != NULL);
  if (ret) {
    ret &= (A->columns == 3) && (A->rows > 0) && (A->matrix != NULL);
  }
  return ret;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret;
  if (columns > 0 && rows > 0 && result) {
    result->columns = columns;
    result->rows = rows;
    ret = allocate_dynamic_matrix(result);
  } else if (result) {
    ret = INCORRECT_MATRIX;
    result->matrix = NULL;
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    free(A->matrix);
    A->matrix = NULL;
  }
  A->columns = 0;
  A->rows = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = s21_check_matrix_is_correct(A) && s21_check_matrix_is_correct(B);
  if (ret == SUCCESS) {
    ret &= s21_check_equal_size(A, B);
  }
  for (int row_index = 0; (ret == SUCCESS) && (row_index < A->rows);
       row_index++) {
    for (int col_index = 0; (col_index < A->columns) && (ret == SUCCESS);
         col_index++) {
      double curr_el_a = A->matrix[row_index][col_index];
      double curr_el_b = B->matrix[row_index][col_index];
      ret &= (fabs(curr_el_a - curr_el_b) < 1e-7);
    }
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = !s21_check_matrix_is_correct(A);
  if (ret == OK) {
    ret = s21_create_matrix(A->rows, A->columns, result);
  }
  for (int row = 0; (ret == OK) && (row < A->rows); row++) {
    for (int col = 0; col < A->columns; col++) {
      result->matrix[row][col] = number * A->matrix[row][col];
    }
  }
  return ret;
}

int allocate_dynamic_matrix(matrix_t *result) {
  int ret = OK;
  int rows = result->rows;
  int cols = result->columns;
  double **matrix = (double **)malloc((rows) * (cols) * sizeof(double) +
                                      (rows) * sizeof(double *));
  if (matrix) {
    double *ptr = (double *)((matrix) + rows);
    for (int row_index = 0; row_index < rows; row_index++) {
      matrix[row_index] = ptr + (cols)*row_index;
      for (int col_index = 0; col_index < cols; col_index++) {
        matrix[row_index][col_index] = 0;
      }
    }
    result->matrix = matrix;
  } else {
    result->matrix = NULL;
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

int rotate_model(matrix_t *matrix, enum axis axis, double angle) {
  double temp_x;
  double temp_y;
  double temp_z;
  double angle_cos = cos(angle);
  double angle_sin = sin(angle);
  int res = OK;
  if (!s21_check_matrix_is_correct(matrix)) {
    res = INCORRECT_MATRIX;
  } else if (axis == OX) {
    for (int i = 0; (i < matrix->rows); i++) {
      temp_y = matrix->matrix[i][1];
      temp_z = matrix->matrix[i][2];

      matrix->matrix[i][1] = angle_cos * temp_y - angle_sin * temp_z;
      matrix->matrix[i][2] = angle_sin * temp_y + angle_cos * temp_z;
    }
  } else if (axis == OY) {
    for (int i = 0; (i < matrix->rows); i++) {
      temp_x = matrix->matrix[i][0];
      temp_z = matrix->matrix[i][2];

      matrix->matrix[i][0] = angle_cos * temp_x + angle_sin * temp_z;
      matrix->matrix[i][2] = -angle_sin * temp_x + angle_cos * temp_z;
    }
  } else if (axis == OZ) {
    for (int i = 0; (i < matrix->rows); i++) {
      temp_x = matrix->matrix[i][0];
      temp_y = matrix->matrix[i][1];

      matrix->matrix[i][0] = angle_cos * temp_x - angle_sin * temp_y;
      matrix->matrix[i][1] = angle_sin * temp_x + angle_cos * temp_y;
    }
  }
  return res;
}

int move_model(matrix_t *model, matrix_t *vector) {
  int ret = !(s21_check_matrix_is_correct(model) &&
              s21_check_matrix_is_correct(vector));
  for (int row = 0; (ret == OK) && (row < model->rows); row++) {
    for (int col = 0; col < model->columns; col++) {
      model->matrix[row][col] =
          model->matrix[row][col] + vector->matrix[0][col];
    }
  }
  return ret;
}
