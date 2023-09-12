#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum operation_errors { OK, INCORRECT_MATRIX, CALCULATION_ERROR };
enum axis { OX, OY, OZ };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/**
 * @brief Creates a matrix with the specified number of rows and columns.
 *
 * This function dynamically allocates memory for a matrix with the specified
 * number of rows and columns. The resulting matrix is stored in the provided
 * matrix_t structure.
 *
 * @param rows The number of rows in the matrix.
 * @param columns The number of columns in the matrix.
 * @param result A pointer to the matrix_t structure to store the created
 * matrix.
 * @return 0 if the matrix creation is successful, -1 otherwise.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);
/**
 * @brief Removes a matrix and frees the allocated memory.
 *
 * This function frees the memory allocated for a matrix represented by the
 * provided matrix_t structure. It should be called to release the memory when
 * the matrix is no longer needed.
 *
 * @param A A pointer to the matrix_t structure representing the matrix to
 * remove.
 */
void s21_remove_matrix(matrix_t *A);
/**
 * @brief Checks if two matrices are equal.
 *
 * This function compares two matrices represented by the provided matrix_t
 * structures and determines if they are equal. Matrices are considered equal if
 * they have the same dimensions and corresponding elements are equal.
 *
 * @param A A pointer to the first matrix_t structure to compare.
 * @param B A pointer to the second matrix_t structure to compare.
 * @return 1 if the matrices are equal, 0 otherwise.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);
/**
 * @brief Multiplies a matrix by a scalar number.
 *
 * This function multiplies a matrix represented by the provided matrix_t
 * structure by a scalar number. The resulting matrix is stored in the provided
 * matrix_t structure.
 *
 * @param A A pointer to the matrix_t structure representing the matrix to
 * multiply.
 * @param number The scalar number to multiply the matrix by.
 * @param result A pointer to the matrix_t structure to store the result of the
 * multiplication.
 * @return 0 if the multiplication is successful, -1 otherwise.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
/**
 * @brief Rotates a model represented by a matrix around a specified axis.
 *
 * This function rotates a model represented by the provided matrix_t structure
 * around the specified axis by the given angle. The resulting matrix represents
 * the rotated model.
 *
 * @param matrix A pointer to the matrix_t structure representing the model
 * matrix.
 * @param axis The axis of rotation (enum axis).
 * @param angle The angle of rotation in degrees.
 * @return 0 if the rotation is successful, -1 otherwise.
 */
int rotate_model(matrix_t *matrix, enum axis axis, double angle);
/**
 * @brief Moves a model represented by a matrix by a specified vector.
 *
 * This function moves a model represented by the provided matrix_t structure
 * by a vector represented by another matrix. The resulting matrix represents
 * the moved model.
 *
 * @param model A pointer to the matrix_t structure representing the model
 * matrix.
 * @param vector A pointer to the matrix_t structure representing the vector for
 * translation.
 * @return 0 if the movement is successful, -1 otherwise.
 */
int move_model(matrix_t *model, matrix_t *vector);
