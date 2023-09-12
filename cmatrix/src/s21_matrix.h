#ifndef _SRC_MATRIX_H_
#define _SRC_MATRIX_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define S21_NULL (void*)0
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATING_ERROR 2

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);;
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void null_the_result(matrix_t *result);
int check_invalidity_of_matrix(matrix_t * suspect);
int mxs_not_valid_for_comparison(matrix_t * suspectA, matrix_t * suspectB);
int check_sub_add_validity(matrix_t * suspectA, matrix_t * suspectB, matrix_t * suspicious_result);
int check_multiplicability_of_matrixes(matrix_t * suspectA, matrix_t * suspectB, matrix_t * suspicious_result);
void minor_of_the_matrix(matrix_t *A, matrix_t * result, int * ith, int * jth, int size);
int s21_calc_complements(matrix_t *A, matrix_t *result);
double find_determinant(matrix_t tmp);
int s21_determinant(matrix_t *A, double *result);
void swap_rows(matrix_t * tmp, int i, int current_start);
void create_minor(int i, int j, matrix_t *tmp, matrix_t * A);



#endif