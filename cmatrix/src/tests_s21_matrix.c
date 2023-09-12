#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test_1) {
  int rows = 4, columns = 4;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  int rows = -1, columns = -1;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(A.matrix == NULL, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_3) {
  int rows = 0, columns = 0;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(A.matrix == NULL, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_4) {
  int rows = 1, columns = 0;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(A.matrix == NULL, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_5) {
  int rows = 0, columns = 1;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(A.matrix == NULL, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_6) {
  int rows = 1, columns = 1;
  matrix_t A = {0};
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, columns);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_int_eq(A.matrix == NULL, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_7) {
  int rows = 25, cols = 5;
  int ret_val = s21_create_matrix(rows, cols, NULL);
  ck_assert_int_eq(ret_val, INCORRECT_MATRIX);
}
END_TEST

START_TEST(equal_test_1) {
  int rows1 = 2, cols1 = 3;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows1, cols1, &B);
  A.matrix[0][0] = -565.0;
  A.matrix[0][1] = 336.0;
  A.matrix[0][2] = 387.0;
  A.matrix[1][0] = -571.0;
  A.matrix[1][1] = -625.0;
  A.matrix[1][2] = 659.0;
  B.matrix[0][0] = -564.9999999425665;
  B.matrix[0][1] = 336.00000009840676;
  B.matrix[0][2] = 386.99999991639265;
  B.matrix[1][0] = -571.0000000294291;
  B.matrix[1][1] = -624.9999999675878;
  B.matrix[1][2] = 658.9999999752287;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_test_2) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows1, cols1, &B);
  A.matrix[0][0] = 89.0;
  A.matrix[0][1] = 15.0;
  A.matrix[0][2] = -73.0;
  A.matrix[0][3] = 84.0;
  A.matrix[0][4] = 48.0;
  A.matrix[1][0] = -48.0;
  A.matrix[1][1] = 98.0;
  A.matrix[1][2] = -37.0;
  A.matrix[1][3] = -15.0;
  A.matrix[1][4] = 75.0;
  A.matrix[2][0] = -65.0;
  A.matrix[2][1] = 9.0;
  A.matrix[2][2] = 65.0;
  A.matrix[2][3] = -39.0;
  A.matrix[2][4] = -23.0;
  A.matrix[3][0] = 98.0;
  A.matrix[3][1] = -76.0;
  A.matrix[3][2] = -36.0;
  A.matrix[3][3] = -80.0;
  A.matrix[3][4] = -98.0;
  A.matrix[4][0] = 28.0;
  A.matrix[4][1] = -89.0;
  A.matrix[4][2] = 84.0;
  A.matrix[4][3] = 20.0;
  A.matrix[4][4] = -54.0;
  B.matrix[0][0] = 89.00000003664061;
  B.matrix[0][1] = 15.000000094637693;
  B.matrix[0][2] = -72.999999904439;
  B.matrix[0][3] = 83.99999997453918;
  B.matrix[0][4] = 48.000000015533104;
  B.matrix[1][0] = -48.00000008941054;
  B.matrix[1][1] = 97.9999999016849;
  B.matrix[1][2] = -37.00000003212506;
  B.matrix[1][3] = -14.999999956040131;
  B.matrix[1][4] = 75.0000000166082;
  B.matrix[2][0] = -65.00000000140128;
  B.matrix[2][1] = 9.000000066562974;
  B.matrix[2][2] = 65.00000008968755;
  B.matrix[2][3] = -38.99999992486857;
  B.matrix[2][4] = -23.00000004317343;
  B.matrix[3][0] = 97.99999996879005;
  B.matrix[3][1] = -76.0000000282288;
  B.matrix[3][2] = -36.00000005955415;
  B.matrix[3][3] = -79.99999996250125;
  B.matrix[3][4] = -98.00000003676463;
  B.matrix[4][0] = 27.99999994109817;
  B.matrix[4][1] = -89.00000003152424;
  B.matrix[4][2] = 84.00000007691321;
  B.matrix[4][3] = 19.999999959039037;
  B.matrix[4][4] = -53.999999912804135;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_test_3) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows1, cols1, &B);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 1.0;
  A.matrix[0][3] = 0.0;
  A.matrix[0][4] = 1.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = -1.0;
  A.matrix[1][2] = -1.0;
  A.matrix[1][3] = -1.0;
  A.matrix[1][4] = 0.0;
  A.matrix[2][0] = -1.0;
  A.matrix[2][1] = -1.0;
  A.matrix[2][2] = 0.0;
  A.matrix[2][3] = 1.0;
  A.matrix[2][4] = -1.0;
  A.matrix[3][0] = 0.0;
  A.matrix[3][1] = -1.0;
  A.matrix[3][2] = -1.0;
  A.matrix[3][3] = 1.0;
  A.matrix[3][4] = -1.0;
  A.matrix[4][0] = 0.0;
  A.matrix[4][1] = 0.0;
  A.matrix[4][2] = -1.0;
  A.matrix[4][3] = 0.0;
  A.matrix[4][4] = 0.0;
  B.matrix[0][0] = 3.018410239096916e-08;
  B.matrix[0][1] = 1.00000007493629;
  B.matrix[0][2] = 1.0000000433069167;
  B.matrix[0][3] = -9.17621868869887e-08;
  B.matrix[0][4] = 1.0000000438293917;
  B.matrix[1][0] = -1.000000018217474;
  B.matrix[1][1] = -1.000000083388464;
  B.matrix[1][2] = -0.9999999972079685;
  B.matrix[1][3] = -0.9999999058602741;
  B.matrix[1][4] = -1.2304865374555484e-08;
  B.matrix[2][0] = -0.9999999342936077;
  B.matrix[2][1] = -1.0000000257054464;
  B.matrix[2][2] = -8.27796973355895e-08;
  B.matrix[2][3] = 0.9999999038146333;
  B.matrix[2][4] = -1.000000081187636;
  B.matrix[3][0] = -9.633636160900536e-08;
  B.matrix[3][1] = -0.9999999626153269;
  B.matrix[3][2] = -0.9999999028574234;
  B.matrix[3][3] = 0.9999999240293977;
  B.matrix[3][4] = -0.9999999336977742;
  B.matrix[4][0] = 4.161821884740602e-08;
  B.matrix[4][1] = 4.430939140060852e-08;
  B.matrix[4][2] = -0.9999999535764741;
  B.matrix[4][3] = -2.9035838328182373e-08;
  B.matrix[4][4] = 9.478407929020278e-08;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_test_4) {
  int rows1 = 5, cols1 = 2;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows1, cols1, &B);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = -1.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 1.0;
  A.matrix[3][0] = 1.0;
  A.matrix[3][1] = 1.0;
  A.matrix[4][0] = 1.0;
  A.matrix[4][1] = 1.0;
  B.matrix[0][0] = -8.021627222955141e-09;
  B.matrix[0][1] = -1.000000065560335;
  B.matrix[1][0] = 8.272703231169782e-08;
  B.matrix[1][1] = -1.0000000642580948;
  B.matrix[2][0] = -5.800126812247424e-08;
  B.matrix[2][1] = 1.0000000761970786;
  B.matrix[3][0] = 1.000000001199033;
  B.matrix[3][1] = 1.000000021719552;
  B.matrix[4][0] = 1.0000000825280435;
  B.matrix[4][1] = 1.0000000483478904;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_test_5) {
  int rows1 = 4, cols1 = 5;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows1, cols1, &B);
  A.matrix[0][0] = -42.0;
  A.matrix[0][1] = -6.0;
  A.matrix[0][2] = -66.0;
  A.matrix[0][3] = -4.0;
  A.matrix[0][4] = -96.0;
  A.matrix[1][0] = -14.0;
  A.matrix[1][1] = 40.0;
  A.matrix[1][2] = 56.0;
  A.matrix[1][3] = 92.0;
  A.matrix[1][4] = -7.0;
  A.matrix[2][0] = 33.0;
  A.matrix[2][1] = 64.0;
  A.matrix[2][2] = -91.0;
  A.matrix[2][3] = -34.0;
  A.matrix[2][4] = 55.0;
  A.matrix[3][0] = -79.0;
  A.matrix[3][1] = 51.0;
  A.matrix[3][2] = -75.0;
  A.matrix[3][3] = -26.0;
  A.matrix[3][4] = -3.0;
  B.matrix[0][0] = -42.00000000025071;
  B.matrix[0][1] = -6.0000000467236045;
  B.matrix[0][2] = -66.00000000847012;
  B.matrix[0][3] = -3.9999999180681494;
  B.matrix[0][4] = -96.00000005425697;
  B.matrix[1][0] = -13.999999960174542;
  B.matrix[1][1] = 39.99999991655606;
  B.matrix[1][2] = 55.99999994462708;
  B.matrix[1][3] = 92.00000002015003;
  B.matrix[1][4] = -6.99999997591102;
  B.matrix[2][0] = 32.99999999683639;
  B.matrix[2][1] = 63.99999995102012;
  B.matrix[2][2] = -91.00000000732605;
  B.matrix[2][3] = -33.999999952088494;
  B.matrix[2][4] = 55.000000087920355;
  B.matrix[3][0] = -79.00000004131194;
  B.matrix[3][1] = 51.00000002282117;
  B.matrix[3][2] = -74.99999992879957;
  B.matrix[3][3] = -26.00000004169098;
  B.matrix[3][4] = -3.0000000387943504;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  int rows1 = 1, columns1 = 2;
  int rows2 = 2, columns2 = 1;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_7) {
  int rows1 = 2, columns1 = 1;
  matrix_t A = {0};
  s21_create_matrix(rows1, columns1, &A);
  int res = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_8) {
  int rows1 = 2, columns1 = 0;
  int rows2 = 1, columns2 = 2;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_9) {
  int rows1 = 2, columns1 = 1;
  int rows2 = -12, columns2 = 2;
  matrix_t A = {0}, B = {0};
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transpose_test_0) {
  int rows1 = 3, cols1 = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 1.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 1.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 1.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_1) {
  int rows1 = 5, cols1 = 1;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -701.0;
  A.matrix[1][0] = -991.0;
  A.matrix[2][0] = -694.0;
  A.matrix[3][0] = -433.0;
  A.matrix[4][0] = -930.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -701.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -991.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -694.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -433.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -930.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_2) {
  int rows1 = 5, cols1 = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -2.0;
  A.matrix[0][1] = -15.0;
  A.matrix[1][0] = -48.0;
  A.matrix[1][1] = -83.0;
  A.matrix[2][0] = 83.0;
  A.matrix[2][1] = -39.0;
  A.matrix[3][0] = 48.0;
  A.matrix[3][1] = -79.0;
  A.matrix[4][0] = -34.0;
  A.matrix[4][1] = -18.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -48.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 83.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 48.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -34.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -15.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -83.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -39.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -79.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -18.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_3) {
  int rows1 = 2, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;
  A.matrix[0][2] = 10.0;
  A.matrix[0][3] = 0.0;
  A.matrix[0][4] = -6.0;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = -2.0;
  A.matrix[1][2] = 3.0;
  A.matrix[1][3] = 10.0;
  A.matrix[1][4] = -2.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -5.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 10.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 3.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 10.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -6.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], -2.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_4) {
  int rows1 = 5, cols1 = 1;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -60.0;
  A.matrix[1][0] = 16.0;
  A.matrix[2][0] = 24.0;
  A.matrix[3][0] = -49.0;
  A.matrix[4][0] = 80.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -60.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 16.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 24.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -49.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 80.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_5) {
  int rows1 = 5, cols1 = 1;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 50.0;
  A.matrix[1][0] = -73.0;
  A.matrix[2][0] = 7.0;
  A.matrix[3][0] = -100.0;
  A.matrix[4][0] = -71.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 50.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -73.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 7.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -100.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -71.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_null_ptr1) {
  matrix_t result = {0};
  int status = s21_transpose(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_null_ptr2) {
  matrix_t A = {0};
  int status = s21_transpose(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mul_test_1) {
  int rows1 = 2, cols1 = 3;
  int rows2 = 3, cols2 = 2;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -53.0;
  A.matrix[0][1] = -18.0;
  A.matrix[0][2] = -40.0;
  A.matrix[1][0] = -28.0;
  A.matrix[1][1] = 16.0;
  A.matrix[1][2] = 60.0;
  B.matrix[0][0] = -7.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = -7.0;
  B.matrix[1][1] = -4.0;
  B.matrix[2][0] = -3.0;
  B.matrix[2][1] = -2.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 617.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -60.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -96.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -296.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_2) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 5, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = -1.0;
  A.matrix[0][3] = 0.0;
  A.matrix[0][4] = 1.0;
  B.matrix[0][0] = -8.0;
  B.matrix[0][1] = 4.0;
  B.matrix[0][2] = 2.0;
  B.matrix[0][3] = -7.0;
  B.matrix[0][4] = -4.0;
  B.matrix[1][0] = -10.0;
  B.matrix[1][1] = 0.0;
  B.matrix[1][2] = -6.0;
  B.matrix[1][3] = -3.0;
  B.matrix[1][4] = 8.0;
  B.matrix[2][0] = 4.0;
  B.matrix[2][1] = -1.0;
  B.matrix[2][2] = 3.0;
  B.matrix[2][3] = 1.0;
  B.matrix[2][4] = -1.0;
  B.matrix[3][0] = -9.0;
  B.matrix[3][1] = -8.0;
  B.matrix[3][2] = 6.0;
  B.matrix[3][3] = 3.0;
  B.matrix[3][4] = 1.0;
  B.matrix[4][0] = 5.0;
  B.matrix[4][1] = 1.0;
  B.matrix[4][2] = -9.0;
  B.matrix[4][3] = 5.0;
  B.matrix[4][4] = -7.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -9.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -18.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 2.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_3) {
  int rows1 = 2, cols1 = 5;
  int rows2 = 5, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 89.0;
  A.matrix[0][1] = -60.0;
  A.matrix[0][2] = -15.0;
  A.matrix[0][3] = 34.0;
  A.matrix[0][4] = 68.0;
  A.matrix[1][0] = -100.0;
  A.matrix[1][1] = 33.0;
  A.matrix[1][2] = -72.0;
  A.matrix[1][3] = -34.0;
  A.matrix[1][4] = -67.0;
  B.matrix[0][0] = -549.0;
  B.matrix[0][1] = -355.0;
  B.matrix[0][2] = -620.0;
  B.matrix[0][3] = 874.0;
  B.matrix[0][4] = -730.0;
  B.matrix[1][0] = 719.0;
  B.matrix[1][1] = -686.0;
  B.matrix[1][2] = 477.0;
  B.matrix[1][3] = 629.0;
  B.matrix[1][4] = -970.0;
  B.matrix[2][0] = -758.0;
  B.matrix[2][1] = -349.0;
  B.matrix[2][2] = -791.0;
  B.matrix[2][3] = -628.0;
  B.matrix[2][4] = 454.0;
  B.matrix[3][0] = -235.0;
  B.matrix[3][1] = -763.0;
  B.matrix[3][2] = 344.0;
  B.matrix[3][3] = -624.0;
  B.matrix[3][4] = 558.0;
  B.matrix[4][0] = -645.0;
  B.matrix[4][1] = 164.0;
  B.matrix[4][2] = 681.0;
  B.matrix[4][3] = -796.0;
  B.matrix[4][4] = 910.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -132481.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 10.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -13931.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -25878.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 67272.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 184408.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 52944.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 77370.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 53121.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -71640.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_4) {
  int rows1 = 5, cols1 = 2;
  int rows2 = 2, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -941.0;
  A.matrix[0][1] = -41.0;
  A.matrix[1][0] = 816.0;
  A.matrix[1][1] = 736.0;
  A.matrix[2][0] = -510.0;
  A.matrix[2][1] = -326.0;
  A.matrix[3][0] = 914.0;
  A.matrix[3][1] = -935.0;
  A.matrix[4][0] = 716.0;
  A.matrix[4][1] = -545.0;
  B.matrix[0][0] = -1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 1.0;
  B.matrix[0][3] = -1.0;
  B.matrix[0][4] = 1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 0.0;
  B.matrix[1][2] = 0.0;
  B.matrix[1][3] = 1.0;
  B.matrix[1][4] = 1.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 900.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -941.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 900.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -982.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -80.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 816.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -80.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 1552.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 184.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -510.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 184.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], -836.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -1849.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 914.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -1849.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], -21.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -1261.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], 716.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -1261.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], 171.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_5) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 5, cols2 = 4;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 3.0;
  A.matrix[0][1] = 6.0;
  A.matrix[0][2] = -6.0;
  A.matrix[0][3] = -10.0;
  A.matrix[0][4] = -2.0;
  B.matrix[0][0] = -63.0;
  B.matrix[0][1] = -35.0;
  B.matrix[0][2] = 61.0;
  B.matrix[0][3] = -86.0;
  B.matrix[1][0] = -88.0;
  B.matrix[1][1] = 6.0;
  B.matrix[1][2] = -40.0;
  B.matrix[1][3] = 12.0;
  B.matrix[2][0] = -3.0;
  B.matrix[2][1] = -7.0;
  B.matrix[2][2] = -58.0;
  B.matrix[2][3] = 99.0;
  B.matrix[3][0] = 30.0;
  B.matrix[3][1] = -95.0;
  B.matrix[3][2] = -7.0;
  B.matrix[3][3] = 70.0;
  B.matrix[4][0] = -88.0;
  B.matrix[4][1] = -92.0;
  B.matrix[4][2] = -72.0;
  B.matrix[4][3] = 91.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -823.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 1107.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 505.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -1662.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mul_test_6) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 5, cols2 = 4;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -7.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 8.0;
  A.matrix[0][3] = 3.0;
  A.matrix[0][4] = -8.0;
  B.matrix[0][0] = -51.0;
  B.matrix[0][1] = 94.0;
  B.matrix[0][2] = 85.0;
  B.matrix[0][3] = 50.0;
  B.matrix[1][0] = 65.0;
  B.matrix[1][1] = 12.0;
  B.matrix[1][2] = 33.0;
  B.matrix[1][3] = 53.0;
  B.matrix[2][0] = 41.0;
  B.matrix[2][1] = 72.0;
  B.matrix[2][2] = 91.0;
  B.matrix[2][3] = 40.0;
  B.matrix[3][0] = -61.0;
  B.matrix[3][1] = -70.0;
  B.matrix[3][2] = 12.0;
  B.matrix[3][3] = 42.0;
  B.matrix[4][0] = 70.0;
  B.matrix[4][1] = 82.0;
  B.matrix[4][2] = 37.0;
  B.matrix[4][3] = 25.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(B.columns, result.columns);
  ck_assert_int_eq(A.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -58.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -948.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -127.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -104.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mul_matrix_1_err) {
  int rows = 2, columns = 3, rows2 = 2, columns2 = 3;
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mul_matrix_2_err) {
  int rows = 2, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_mult_matrix(&A, NULL, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mul_matrix_3_err) {
  matrix_t B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  int status = s21_mult_matrix(NULL, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_0) {
  int rows1 = 2, cols1 = 3;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -58.0;
  A.matrix[0][1] = -50.0;
  A.matrix[0][2] = -66.0;
  A.matrix[1][0] = -94.0;
  A.matrix[1][1] = 95.0;
  A.matrix[1][2] = -67.0;
  int status = s21_mult_number(&A, 948.0939352882323, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -54989.448246717475, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -47404.696764411616, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -62574.19972902333, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -89120.82991709384, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 90068.92385238207, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -63522.29366431156, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_1) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 8.0;
  A.matrix[0][2] = -4.0;
  A.matrix[0][3] = 1.0;
  A.matrix[0][4] = 10.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = -3.0;
  A.matrix[1][2] = -5.0;
  A.matrix[1][3] = -6.0;
  A.matrix[1][4] = 6.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 7.0;
  A.matrix[2][2] = -7.0;
  A.matrix[2][3] = 7.0;
  A.matrix[2][4] = 0.0;
  A.matrix[3][0] = 2.0;
  A.matrix[3][1] = 4.0;
  A.matrix[3][2] = -3.0;
  A.matrix[3][3] = 3.0;
  A.matrix[3][4] = 10.0;
  A.matrix[4][0] = 8.0;
  A.matrix[4][1] = -6.0;
  A.matrix[4][2] = -4.0;
  A.matrix[4][3] = -2.0;
  A.matrix[4][4] = -5.0;
  int status = s21_mult_number(&A, 1515.684367498505, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -1515.684367498505, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 12125.47493998804, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -6062.73746999402, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 1515.684367498505, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 15156.84367498505, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 1515.684367498505, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -4547.053102495515, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -7578.421837492525, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -9094.10620499103, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 9094.10620499103, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 7578.421837492525, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 10609.790572489535, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -10609.790572489535, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 10609.790572489535, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 3031.36873499701, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 6062.73746999402, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], -4547.053102495515, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 4547.053102495515, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 15156.84367498505, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 12125.47493998804, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], -9094.10620499103, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -6062.73746999402, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -3031.36873499701, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], -7578.421837492525, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_2) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -74.0;
  A.matrix[0][1] = -22.0;
  A.matrix[0][2] = 51.0;
  A.matrix[0][3] = 11.0;
  A.matrix[0][4] = -50.0;
  A.matrix[1][0] = -59.0;
  A.matrix[1][1] = 50.0;
  A.matrix[1][2] = -67.0;
  A.matrix[1][3] = -99.0;
  A.matrix[1][4] = -30.0;
  A.matrix[2][0] = 38.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -76.0;
  A.matrix[2][3] = 28.0;
  A.matrix[2][4] = -96.0;
  A.matrix[3][0] = -55.0;
  A.matrix[3][1] = 16.0;
  A.matrix[3][2] = -40.0;
  A.matrix[3][3] = 13.0;
  A.matrix[3][4] = -88.0;
  A.matrix[4][0] = 5.0;
  A.matrix[4][1] = 62.0;
  A.matrix[4][2] = -9.0;
  A.matrix[4][3] = 58.0;
  A.matrix[4][4] = 79.0;
  int status = s21_mult_number(&A, -7268.448249015911, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 537865.1704271775, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 159905.86147835004, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -370690.8606998114, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -79952.93073917502, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 363422.4124507955, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 428838.44669193873, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -363422.4124507955, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 486986.03268406604, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 719576.3766525752, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 218053.44747047732, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -276201.0334626046, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 14536.896498031821, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 552402.0669252092, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -203516.5509724455, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 697771.0319055275, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 399764.6536958751, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -116295.17198425457, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 290737.9299606364, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -94489.82723720685, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 639623.4459134002, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -36342.24124507955, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], -450643.7914389865, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], 65416.0342411432, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -421569.99844292284, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], -574207.411672257, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_3) {
  int rows1 = 5, cols1 = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = -1.0;
  A.matrix[3][0] = 1.0;
  A.matrix[3][1] = 1.0;
  A.matrix[4][0] = 0.0;
  A.matrix[4][1] = 1.0;
  int status = s21_mult_number(&A, 1990.8087828945843, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 1990.8087828945843, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 1990.8087828945843, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_4) {
  int rows1 = 4, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -13.0;
  A.matrix[0][1] = 23.0;
  A.matrix[0][2] = 68.0;
  A.matrix[0][3] = 9.0;
  A.matrix[0][4] = 70.0;
  A.matrix[1][0] = -86.0;
  A.matrix[1][1] = 82.0;
  A.matrix[1][2] = -14.0;
  A.matrix[1][3] = -42.0;
  A.matrix[1][4] = 100.0;
  A.matrix[2][0] = 97.0;
  A.matrix[2][1] = 74.0;
  A.matrix[2][2] = -27.0;
  A.matrix[2][3] = -2.0;
  A.matrix[2][4] = -36.0;
  A.matrix[3][0] = 92.0;
  A.matrix[3][1] = 85.0;
  A.matrix[3][2] = 31.0;
  A.matrix[3][3] = -10.0;
  A.matrix[3][4] = -33.0;
  int status = s21_mult_number(&A, 5783.965684328195, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -75191.55389626653, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 133031.21073954846, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 393309.66653431725, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 52055.69115895375, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 404877.59790297365, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -497421.0488522247, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 474285.186114912, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -80975.51958059473, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -242926.55874178416, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 578396.5684328194, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 561044.6713798349, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 428013.4606402864, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -156167.07347686126, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -11567.93136865639, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], -208222.764635815, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 532124.8429581939, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 491637.08316789655, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 179302.93621417403, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -57839.65684328195, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], -190870.86758283043, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(num_mul_test_5) {
  int rows1 = 4, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 1.0;
  A.matrix[0][3] = 0.0;
  A.matrix[0][4] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = -1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 1.0;
  A.matrix[1][4] = -1.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 1.0;
  A.matrix[2][2] = -1.0;
  A.matrix[2][3] = -1.0;
  A.matrix[2][4] = -1.0;
  A.matrix[3][0] = -1.0;
  A.matrix[3][1] = -1.0;
  A.matrix[3][2] = 0.0;
  A.matrix[3][3] = 0.0;
  A.matrix[3][4] = 1.0;
  int status = s21_mult_number(&A, -1025.7298145448658, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 1025.7298145448658, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], -1025.7298145448658, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mul_num_1_err) {
  matrix_t R = {0};
  int status = s21_mult_number(NULL, 2, &R);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(sum_test_1) {
  int rows1 = 2, cols1 = 3;
  int rows2 = 2, cols2 = 3;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 695.0;
  A.matrix[0][1] = 930.0;
  A.matrix[0][2] = 363.0;
  A.matrix[1][0] = -60.0;
  A.matrix[1][1] = 842.0;
  A.matrix[1][2] = -291.0;
  B.matrix[0][0] = -61.0;
  B.matrix[0][1] = -91.0;
  B.matrix[0][2] = -94.0;
  B.matrix[1][0] = -10.0;
  B.matrix[1][1] = 17.0;
  B.matrix[1][2] = 71.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 634.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 839.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 269.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -70.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 859.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -220.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_2) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 1, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -7.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 0.0;
  A.matrix[0][3] = -1.0;
  A.matrix[0][4] = 1.0;
  B.matrix[0][0] = 52.0;
  B.matrix[0][1] = -68.0;
  B.matrix[0][2] = -42.0;
  B.matrix[0][3] = -14.0;
  B.matrix[0][4] = -17.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 45.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -63.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -42.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -15.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -16.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_3) {
  int rows1 = 2, cols1 = 5;
  int rows2 = 2, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -8.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = -9.0;
  A.matrix[0][3] = 10.0;
  A.matrix[0][4] = 5.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 7.0;
  A.matrix[1][2] = 7.0;
  A.matrix[1][3] = -8.0;
  A.matrix[1][4] = -7.0;
  B.matrix[0][0] = -2.0;
  B.matrix[0][1] = 63.0;
  B.matrix[0][2] = 43.0;
  B.matrix[0][3] = 61.0;
  B.matrix[0][4] = 91.0;
  B.matrix[1][0] = -85.0;
  B.matrix[1][1] = 78.0;
  B.matrix[1][2] = -94.0;
  B.matrix[1][3] = 95.0;
  B.matrix[1][4] = -57.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -10.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 65.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 34.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 71.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 96.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -86.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 85.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -87.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 87.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -64.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_4) {
  int rows1 = 5, cols1 = 2;
  int rows2 = 5, cols2 = 2;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = -2.0;
  A.matrix[3][0] = -2.0;
  A.matrix[3][1] = -3.0;
  A.matrix[4][0] = 2.0;
  A.matrix[4][1] = 8.0;
  B.matrix[0][0] = -10.0;
  B.matrix[0][1] = -8.0;
  B.matrix[1][0] = -10.0;
  B.matrix[1][1] = -10.0;
  B.matrix[2][0] = -5.0;
  B.matrix[2][1] = 6.0;
  B.matrix[3][0] = 5.0;
  B.matrix[3][1] = -9.0;
  B.matrix[4][0] = -5.0;
  B.matrix[4][1] = -8.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -10.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -8.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -15.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -6.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 4.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 3.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -12.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -3.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 0.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_5) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 1, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = 0.0;
  A.matrix[0][3] = -1.0;
  A.matrix[0][4] = 1.0;
  B.matrix[0][0] = 851.0;
  B.matrix[0][1] = -565.0;
  B.matrix[0][2] = 67.0;
  B.matrix[0][3] = 597.0;
  B.matrix[0][4] = -103.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 850.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -566.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 67.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 596.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -102.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_test_6) {
  int rows1 = 1, cols1 = 5;
  int rows2 = 1, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = -8.0;
  A.matrix[0][3] = -1.0;
  A.matrix[0][4] = 0.0;
  B.matrix[0][0] = -92.0;
  B.matrix[0][1] = 17.0;
  B.matrix[0][2] = 20.0;
  B.matrix[0][3] = 77.0;
  B.matrix[0][4] = 70.0;
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -91.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 20.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 12.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 76.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 70.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_1_err) {
  int rows = 2, columns = 3, rows2 = 2, columns2 = 2;
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  int status = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_2_err) {
  int rows = 2, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_3_err) {
  matrix_t B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  int status = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_1) {
  int rows1 = 2, cols1 = 3;
  int rows2 = 2, cols2 = 3;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 9.0;
  A.matrix[0][2] = -1.0;
  A.matrix[1][0] = -2.0;
  A.matrix[1][1] = -3.0;
  A.matrix[1][2] = -4.0;
  B.matrix[0][0] = -4.0;
  B.matrix[0][1] = -9.0;
  B.matrix[0][2] = 5.0;
  B.matrix[1][0] = -2.0;
  B.matrix[1][1] = -8.0;
  B.matrix[1][2] = 7.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 18.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -6.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -11.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_2) {
  int rows1 = 5, cols1 = 5;
  int rows2 = 5, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -5.0;
  A.matrix[0][1] = -49.0;
  A.matrix[0][2] = 91.0;
  A.matrix[0][3] = 65.0;
  A.matrix[0][4] = 19.0;
  A.matrix[1][0] = -19.0;
  A.matrix[1][1] = -83.0;
  A.matrix[1][2] = 63.0;
  A.matrix[1][3] = 92.0;
  A.matrix[1][4] = -35.0;
  A.matrix[2][0] = -69.0;
  A.matrix[2][1] = -97.0;
  A.matrix[2][2] = -86.0;
  A.matrix[2][3] = 37.0;
  A.matrix[2][4] = 18.0;
  A.matrix[3][0] = -22.0;
  A.matrix[3][1] = 96.0;
  A.matrix[3][2] = 35.0;
  A.matrix[3][3] = 1.0;
  A.matrix[3][4] = 93.0;
  A.matrix[4][0] = -44.0;
  A.matrix[4][1] = -98.0;
  A.matrix[4][2] = 4.0;
  A.matrix[4][3] = 32.0;
  A.matrix[4][4] = 31.0;
  B.matrix[0][0] = -849.0;
  B.matrix[0][1] = 535.0;
  B.matrix[0][2] = 146.0;
  B.matrix[0][3] = 118.0;
  B.matrix[0][4] = 993.0;
  B.matrix[1][0] = 297.0;
  B.matrix[1][1] = -555.0;
  B.matrix[1][2] = 32.0;
  B.matrix[1][3] = 263.0;
  B.matrix[1][4] = -477.0;
  B.matrix[2][0] = 759.0;
  B.matrix[2][1] = 279.0;
  B.matrix[2][2] = -13.0;
  B.matrix[2][3] = 839.0;
  B.matrix[2][4] = 327.0;
  B.matrix[3][0] = 258.0;
  B.matrix[3][1] = 825.0;
  B.matrix[3][2] = -102.0;
  B.matrix[3][3] = -455.0;
  B.matrix[3][4] = -607.0;
  B.matrix[4][0] = 217.0;
  B.matrix[4][1] = -21.0;
  B.matrix[4][2] = -791.0;
  B.matrix[4][3] = 872.0;
  B.matrix[4][4] = 439.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 844.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -584.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -55.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -53.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -974.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -316.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 472.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 31.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -171.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 442.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -828.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -376.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -73.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -802.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], -309.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -280.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -729.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 137.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 456.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 700.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -261.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], -77.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], 795.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -840.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], -408.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_3) {
  int rows1 = 5, cols1 = 5;
  int rows2 = 5, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -8.0;
  A.matrix[0][1] = -6.0;
  A.matrix[0][2] = 4.0;
  A.matrix[0][3] = -4.0;
  A.matrix[0][4] = -6.0;
  A.matrix[1][0] = 9.0;
  A.matrix[1][1] = -5.0;
  A.matrix[1][2] = -8.0;
  A.matrix[1][3] = -7.0;
  A.matrix[1][4] = 10.0;
  A.matrix[2][0] = -3.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = -1.0;
  A.matrix[2][3] = 2.0;
  A.matrix[2][4] = -4.0;
  A.matrix[3][0] = -9.0;
  A.matrix[3][1] = -2.0;
  A.matrix[3][2] = -1.0;
  A.matrix[3][3] = -4.0;
  A.matrix[3][4] = -4.0;
  A.matrix[4][0] = -7.0;
  A.matrix[4][1] = -1.0;
  A.matrix[4][2] = 3.0;
  A.matrix[4][3] = 2.0;
  A.matrix[4][4] = -7.0;
  B.matrix[0][0] = 12.0;
  B.matrix[0][1] = 47.0;
  B.matrix[0][2] = 86.0;
  B.matrix[0][3] = 35.0;
  B.matrix[0][4] = -97.0;
  B.matrix[1][0] = 63.0;
  B.matrix[1][1] = -73.0;
  B.matrix[1][2] = -73.0;
  B.matrix[1][3] = 82.0;
  B.matrix[1][4] = 50.0;
  B.matrix[2][0] = 40.0;
  B.matrix[2][1] = 95.0;
  B.matrix[2][2] = -56.0;
  B.matrix[2][3] = 9.0;
  B.matrix[2][4] = -43.0;
  B.matrix[3][0] = -8.0;
  B.matrix[3][1] = -28.0;
  B.matrix[3][2] = -20.0;
  B.matrix[3][3] = 87.0;
  B.matrix[3][4] = -8.0;
  B.matrix[4][0] = -78.0;
  B.matrix[4][1] = -36.0;
  B.matrix[4][2] = 78.0;
  B.matrix[4][3] = 26.0;
  B.matrix[4][4] = -93.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -20.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -53.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -82.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -39.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 91.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -54.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 68.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 65.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -89.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -40.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -43.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -95.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 55.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -7.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 39.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 26.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 19.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -91.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 4.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 71.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 35.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -75.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -24.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], 86.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_4) {
  int rows1 = 5, cols1 = 2;
  int rows2 = 5, cols2 = 2;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 899.0;
  A.matrix[0][1] = -833.0;
  A.matrix[1][0] = 83.0;
  A.matrix[1][1] = -925.0;
  A.matrix[2][0] = -586.0;
  A.matrix[2][1] = -736.0;
  A.matrix[3][0] = -688.0;
  A.matrix[3][1] = -414.0;
  A.matrix[4][0] = -445.0;
  A.matrix[4][1] = 859.0;
  B.matrix[0][0] = -95.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 59.0;
  B.matrix[1][1] = 88.0;
  B.matrix[2][0] = -69.0;
  B.matrix[2][1] = -54.0;
  B.matrix[3][0] = -13.0;
  B.matrix[3][1] = 41.0;
  B.matrix[4][0] = -60.0;
  B.matrix[4][1] = 54.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 994.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -839.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 24.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -1013.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -517.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -682.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -675.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -455.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -385.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 805.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_5) {
  int rows1 = 4, cols1 = 5;
  int rows2 = 4, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = 920.0;
  A.matrix[0][1] = -288.0;
  A.matrix[0][2] = -308.0;
  A.matrix[0][3] = 323.0;
  A.matrix[0][4] = -487.0;
  A.matrix[1][0] = 279.0;
  A.matrix[1][1] = 486.0;
  A.matrix[1][2] = 685.0;
  A.matrix[1][3] = 754.0;
  A.matrix[1][4] = -321.0;
  A.matrix[2][0] = 545.0;
  A.matrix[2][1] = -610.0;
  A.matrix[2][2] = -296.0;
  A.matrix[2][3] = 215.0;
  A.matrix[2][4] = 161.0;
  A.matrix[3][0] = 248.0;
  A.matrix[3][1] = 547.0;
  A.matrix[3][2] = 798.0;
  A.matrix[3][3] = -898.0;
  A.matrix[3][4] = 727.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 1.0;
  B.matrix[0][2] = 0.0;
  B.matrix[0][3] = 1.0;
  B.matrix[0][4] = -1.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = 0.0;
  B.matrix[1][3] = 0.0;
  B.matrix[1][4] = 1.0;
  B.matrix[2][0] = 0.0;
  B.matrix[2][1] = 0.0;
  B.matrix[2][2] = -1.0;
  B.matrix[2][3] = 1.0;
  B.matrix[2][4] = 0.0;
  B.matrix[3][0] = 0.0;
  B.matrix[3][1] = -1.0;
  B.matrix[3][2] = 0.0;
  B.matrix[3][3] = -1.0;
  B.matrix[3][4] = 0.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], 919.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -289.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -308.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 322.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], -486.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 278.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 485.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 685.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 754.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -322.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 545.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -610.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -295.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 214.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 161.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 248.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 548.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 798.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -897.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 727.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_test_6) {
  int rows1 = 4, cols1 = 5;
  int rows2 = 4, cols2 = 5;
  matrix_t A = {0}, result = {0}, B = {0};
  s21_create_matrix(rows1, cols1, &A);
  s21_create_matrix(rows2, cols2, &B);
  A.matrix[0][0] = -11.0;
  A.matrix[0][1] = 79.0;
  A.matrix[0][2] = -20.0;
  A.matrix[0][3] = -21.0;
  A.matrix[0][4] = 92.0;
  A.matrix[1][0] = 51.0;
  A.matrix[1][1] = 94.0;
  A.matrix[1][2] = -28.0;
  A.matrix[1][3] = 43.0;
  A.matrix[1][4] = -67.0;
  A.matrix[2][0] = -21.0;
  A.matrix[2][1] = -69.0;
  A.matrix[2][2] = 63.0;
  A.matrix[2][3] = 73.0;
  A.matrix[2][4] = 42.0;
  A.matrix[3][0] = 89.0;
  A.matrix[3][1] = -94.0;
  A.matrix[3][2] = -32.0;
  A.matrix[3][3] = 12.0;
  A.matrix[3][4] = 81.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[0][2] = 1.0;
  B.matrix[0][3] = 1.0;
  B.matrix[0][4] = 0.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 1.0;
  B.matrix[1][2] = -1.0;
  B.matrix[1][3] = 0.0;
  B.matrix[1][4] = -1.0;
  B.matrix[2][0] = -1.0;
  B.matrix[2][1] = -1.0;
  B.matrix[2][2] = 0.0;
  B.matrix[2][3] = 1.0;
  B.matrix[2][4] = 0.0;
  B.matrix[3][0] = 1.0;
  B.matrix[3][1] = 0.0;
  B.matrix[3][2] = -1.0;
  B.matrix[3][3] = 0.0;
  B.matrix[3][4] = 1.0;
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.columns, result.columns);
  ck_assert_int_eq(B.rows, result.rows);
  ck_assert_double_eq_tol(result.matrix[0][0], -12.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 79.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], -21.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -22.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 92.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 50.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 93.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -27.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 43.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -66.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -20.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -68.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 63.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 72.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 42.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 88.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -94.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], -31.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 12.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 80.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_1_err) {
  int rows = 2, columns = 3, rows2 = 2, columns2 = 2;
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  int status = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_2_err) {
  int rows = 2, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_3_err) {
  matrix_t B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  int status = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(status, 1);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_0) {
  int rows1 = 2, cols1 = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 57.0;
  A.matrix[0][1] = -55.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -79.0;
  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -79.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 55.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 57.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_1) {
  matrix_t A = {0}, check = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  check.matrix[0][0] = 0;
  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;

  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, OK);
  int eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t A = {0}, check = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &check);
  A.matrix[0][0] = 23464;

  check.matrix[0][0] = 1;

  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, OK);
  int eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_3) {
  matrix_t A = {0}, check = {0}, result = {0};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &check);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 15;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 9;
  A.matrix[1][0] = 8;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = 2;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 9;
  A.matrix[2][3] = 9;
  A.matrix[3][0] = -1;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 3;
  A.matrix[3][3] = 2;

  check.matrix[0][0] = -6;
  check.matrix[0][1] = 92;
  check.matrix[0][2] = -222;
  check.matrix[0][3] = 192;
  check.matrix[1][0] = 234;
  check.matrix[1][1] = 48;
  check.matrix[1][2] = 174;
  check.matrix[1][3] = -216;
  check.matrix[2][0] = 66;
  check.matrix[2][1] = -204;
  check.matrix[2][2] = 18;
  check.matrix[2][3] = 312;
  check.matrix[3][0] = -504;
  check.matrix[3][1] = 456;
  check.matrix[3][2] = 744;
  check.matrix[3][3] = -840;

  int ret_val = s21_calc_complements(&A, &result);
  ck_assert_int_eq(ret_val, OK);
  int eq = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(eq, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_4) {
  int rows1 = 4, cols1 = 4;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[0][3] = -1.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = -1.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = -1.0;
  A.matrix[2][2] = 1.0;
  A.matrix[2][3] = 1.0;
  A.matrix[3][0] = -1.0;
  A.matrix[3][1] = 1.0;
  A.matrix[3][2] = -1.0;
  A.matrix[3][3] = -1.0;
  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 0.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_5) {
  int rows1 = 4, cols1 = 4;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = -1.0;
  A.matrix[0][3] = 1.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 1.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 0.0;
  A.matrix[2][3] = 0.0;
  A.matrix[3][0] = 0.0;
  A.matrix[3][1] = 1.0;
  A.matrix[3][2] = -1.0;
  A.matrix[3][3] = -1.0;
  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -3.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -2.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -0.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 1.0, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 1.0, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_null_ptr1) {
  matrix_t result = {0};
  int status = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_null_ptr2) {
  matrix_t A = {0};
  int status = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_alc_complements_3_err) {
  int rows = 3, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_calc_complements(&A, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(det_test_0) {
  int rows1 = 2, cols1 = 2;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = -1.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 0.0000001);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_1) {
  int rows1 = 1, cols1 = 1;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = -55.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -55.000000000014, 0.0000001);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_2) {
  int rows1 = 2, cols1 = 2;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = -1.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 0.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -1.0, 7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_3) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = -1.0;
  A.matrix[0][3] = 0.0;
  A.matrix[0][4] = 1.0;
  A.matrix[1][0] = -1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = -1.0;
  A.matrix[1][3] = -1.0;
  A.matrix[1][4] = -1.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = -1.0;
  A.matrix[2][3] = 1.0;
  A.matrix[2][4] = -1.0;
  A.matrix[3][0] = 1.0;
  A.matrix[3][1] = 0.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 0.0;
  A.matrix[3][4] = 1.0;
  A.matrix[4][0] = -1.0;
  A.matrix[4][1] = 0.0;
  A.matrix[4][2] = 0.0;
  A.matrix[4][3] = 1.0;
  A.matrix[4][4] = -1.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 2.0, 0.0000001);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_4) {
  int rows1 = 1, cols1 = 1;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = 22.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 22.000000000000004, 0.0000001);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_5) {
  int rows1 = 1, cols1 = 1;
  matrix_t A = {0};
  s21_create_matrix(rows1, cols1, &A);
  double result = 0;
  A.matrix[0][0] = 1.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 1.0, 0.0000001);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_test_null_ptr1) {
  double result = 0;
  int status = s21_determinant(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant_3_err) {
  int rows = 3, columns = 2;
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(rows, columns, &A);
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_0) {
  int rows1 = 3, cols1 = 3;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 766.0;
  A.matrix[0][1] = 240.0;
  A.matrix[0][2] = -476.0;
  A.matrix[1][0] = 645.0;
  A.matrix[1][1] = -513.0;
  A.matrix[1][2] = 815.0;
  A.matrix[2][0] = -243.0;
  A.matrix[2][1] = 616.0;
  A.matrix[2][2] = -416.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0008641345, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.000578947962788534, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.00014546750173738873,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.0002103961612866347,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0013003216272451977,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 0.002788246872541524, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], -0.0008163191424059061,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 0.0015872927101572784,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 0.001639931419623541, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_1) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -910.0;
  A.matrix[0][1] = -557.0;
  A.matrix[0][2] = 112.0;
  A.matrix[0][3] = -865.0;
  A.matrix[0][4] = -876.0;
  A.matrix[1][0] = -6.0;
  A.matrix[1][1] = 470.0;
  A.matrix[1][2] = -21.0;
  A.matrix[1][3] = 619.0;
  A.matrix[1][4] = -687.0;
  A.matrix[2][0] = 217.0;
  A.matrix[2][1] = -885.0;
  A.matrix[2][2] = 759.0;
  A.matrix[2][3] = 830.0;
  A.matrix[2][4] = 852.0;
  A.matrix[3][0] = 337.0;
  A.matrix[3][1] = -300.0;
  A.matrix[3][2] = -515.0;
  A.matrix[3][3] = -423.0;
  A.matrix[3][4] = 186.0;
  A.matrix[4][0] = 639.0;
  A.matrix[4][1] = 318.0;
  A.matrix[4][2] = 65.0;
  A.matrix[4][3] = 82.0;
  A.matrix[4][4] = -49.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.00019350613989249304,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0001411592845602524,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.0002631302868267338,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 0.0006050388068648478,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 0.0014333962329494139,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.0004966177070684136,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.0005269671888727825,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -0.0006912626240476625,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -0.0010928055572588776,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 9.889756752596478e-05,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.0004489502427905742,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -0.0007445787791843059,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 0.0002230442393125384,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -0.0013264832762574213,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 0.0012561839005199482,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -0.00032525463861768675,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 0.0009996638017220041,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 0.00035835614565125673,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 0.000322536881504121, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], -0.0007456055571282856,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], -0.0006482269804431723,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], -0.0008938769823126321,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -0.00015914656461542517,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -0.00042175016928734313,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], -0.0006550629147508305,
                          0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -12.0;
  A.matrix[0][1] = 62.0;
  A.matrix[0][2] = 6.0;
  A.matrix[0][3] = 22.0;
  A.matrix[0][4] = 56.0;
  A.matrix[1][0] = -63.0;
  A.matrix[1][1] = -81.0;
  A.matrix[1][2] = 18.0;
  A.matrix[1][3] = 56.0;
  A.matrix[1][4] = -92.0;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = 45.0;
  A.matrix[2][2] = -35.0;
  A.matrix[2][3] = 22.0;
  A.matrix[2][4] = -53.0;
  A.matrix[3][0] = 44.0;
  A.matrix[3][1] = 17.0;
  A.matrix[3][2] = 90.0;
  A.matrix[3][3] = -16.0;
  A.matrix[3][4] = -49.0;
  A.matrix[4][0] = 100.0;
  A.matrix[4][1] = -10.0;
  A.matrix[4][2] = 2.0;
  A.matrix[4][3] = -53.0;
  A.matrix[4][4] = 50.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.008521704629175248, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.009167665441345825, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.00826376866944917, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 0.00044493385904102083,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 0.01651982519887636, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.001360118173368697, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.007067456274437373,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], 0.005039659348831998, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 0.003412488115349414, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -0.005841174636333363,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.004357896382673963, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 0.0013708103111181222,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -0.00696225080889106, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 0.007883605213786072, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], -0.0020126057240516682,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 0.02385379834474297, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], 0.02026762619525435, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 0.008382280158783494, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], -0.0027564489568132513,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 0.01676007504378939, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 0.008339324766443832, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 0.0016800292169457617,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -0.006355898468465792,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -0.003444550197785648,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], 0.003638298450359432, 0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  int rows1 = 2, cols1 = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = -374.0;
  A.matrix[0][1] = 466.0;
  A.matrix[1][0] = 582.0;
  A.matrix[1][1] = -919.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -0.01267691119265044, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.006428118189091518,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.008028250613843912,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.005159047645322376,
                          0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 10.0;
  A.matrix[0][2] = -10.0;
  A.matrix[0][3] = -7.0;
  A.matrix[0][4] = -7.0;
  A.matrix[1][0] = -7.0;
  A.matrix[1][1] = -4.0;
  A.matrix[1][2] = -4.0;
  A.matrix[1][3] = -6.0;
  A.matrix[1][4] = -1.0;
  A.matrix[2][0] = 10.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = -8.0;
  A.matrix[2][3] = 9.0;
  A.matrix[2][4] = 1.0;
  A.matrix[3][0] = -7.0;
  A.matrix[3][1] = -4.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = -7.0;
  A.matrix[3][4] = -5.0;
  A.matrix[4][0] = 9.0;
  A.matrix[4][1] = -9.0;
  A.matrix[4][2] = 10.0;
  A.matrix[4][3] = -2.0;
  A.matrix[4][4] = 7.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.01944743803272263, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.023807191143333007,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.08019006564122662, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 0.0853335945919467, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 0.06554325462917608, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.06965807778975214, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.06260409522876456, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -0.14098167923973745, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], -0.1830116586656216, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], -0.04986773782698149, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.008180660331145293, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], -0.11916658502335, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], -0.08969334770255707, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], -0.018679990855948535,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], -0.009372652754645508,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], -0.07960223376114431, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -0.03605368864504752, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], 0.08234544920152836, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 0.08396198687175466, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], -0.03654354854511611, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 0.030126383854217696, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 0.1100551908820744, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -0.13270304692857846, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], -0.2943404852878743, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], -0.002579928807027859,
                          0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_5) {
  int rows1 = 5, cols1 = 5;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows1, cols1, &A);
  A.matrix[0][0] = 456.0;
  A.matrix[0][1] = 798.0;
  A.matrix[0][2] = -989.0;
  A.matrix[0][3] = -399.0;
  A.matrix[0][4] = 71.0;
  A.matrix[1][0] = 709.0;
  A.matrix[1][1] = -812.0;
  A.matrix[1][2] = -39.0;
  A.matrix[1][3] = 567.0;
  A.matrix[1][4] = 439.0;
  A.matrix[2][0] = -34.0;
  A.matrix[2][1] = 457.0;
  A.matrix[2][2] = 762.0;
  A.matrix[2][3] = -750.0;
  A.matrix[2][4] = -598.0;
  A.matrix[3][0] = -969.0;
  A.matrix[3][1] = 722.0;
  A.matrix[3][2] = 289.0;
  A.matrix[3][3] = -867.0;
  A.matrix[3][4] = 346.0;
  A.matrix[4][0] = 663.0;
  A.matrix[4][1] = -774.0;
  A.matrix[4][2] = 674.0;
  A.matrix[4][3] = 883.0;
  A.matrix[4][4] = -245.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0007583461364238186,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0007259756963678526,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.0005223280767558048,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][3], 0.0001730335772956844,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[0][4], 0.0004900544254527106,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.001378511422098663, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.0009852492454638898,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][2], -0.0006175323100391719,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][3], 0.0013701890423531305,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[1][4], 0.0020764066215018997,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][0], 0.0002462938735654122,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][1], 0.0001043064979764259,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][2], 0.00019649050621145238,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][3], 0.001005032696536952, 0.0000001);
  ck_assert_double_eq_tol(result.matrix[2][4], 0.0011980302364168658,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][0], 0.0006070965568700898,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][1], -0.0012402412021589196,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][2], -0.0011996921025869726,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][3], 0.0007026181906962917,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[3][4], 0.0018741213841548454,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][0], 0.0005627917479347087,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][1], 0.0008941812277988655,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][2], -0.00041885715321779735,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][3], 0.0014367299706793746,
                          0.0000001);
  ck_assert_double_eq_tol(result.matrix[4][4], 0.0007350568187198888,
                          0.0000001);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_null_ptr1) {
  matrix_t result = {0};
  int status = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_null_ptr2) {
  matrix_t A = {0};
  int status = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(status, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_3_err) {
  int rows = 3, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_4_err) {
  int rows = 2, columns = 2;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 25;
  A.matrix[0][1] = 60;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 12;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_create_matrix_test_1);
  tcase_add_test(tc1_1, s21_create_matrix_test_2);
  tcase_add_test(tc1_1, s21_create_matrix_test_3);
  tcase_add_test(tc1_1, s21_create_matrix_test_4);
  tcase_add_test(tc1_1, s21_create_matrix_test_5);
  tcase_add_test(tc1_1, s21_create_matrix_test_6);
  tcase_add_test(tc1_1, s21_create_matrix_test_7);
  tcase_add_test(tc1_1, equal_test_1);
  tcase_add_test(tc1_1, equal_test_2);
  tcase_add_test(tc1_1, equal_test_3);
  tcase_add_test(tc1_1, equal_test_4);
  tcase_add_test(tc1_1, equal_test_5);
  tcase_add_test(tc1_1, s21_eq_matrix_6);
  tcase_add_test(tc1_1, s21_eq_matrix_7);
  tcase_add_test(tc1_1, s21_eq_matrix_8);
  tcase_add_test(tc1_1, s21_eq_matrix_9);
  tcase_add_test(tc1_1, transpose_test_0);
  tcase_add_test(tc1_1, transpose_test_1);
  tcase_add_test(tc1_1, transpose_test_2);
  tcase_add_test(tc1_1, transpose_test_3);
  tcase_add_test(tc1_1, transpose_test_4);
  tcase_add_test(tc1_1, transpose_test_5);
  tcase_add_test(tc1_1, transpose_test_null_ptr1);
  tcase_add_test(tc1_1, transpose_test_null_ptr2);
  tcase_add_test(tc1_1, mul_test_1);
  tcase_add_test(tc1_1, mul_test_2);
  tcase_add_test(tc1_1, mul_test_3);
  tcase_add_test(tc1_1, mul_test_4);
  tcase_add_test(tc1_1, mul_test_5);
  tcase_add_test(tc1_1, mul_test_6);
  tcase_add_test(tc1_1, s21_mul_matrix_1_err);
  tcase_add_test(tc1_1, s21_mul_matrix_2_err);
  tcase_add_test(tc1_1, s21_mul_matrix_3_err);
  tcase_add_test(tc1_1, num_mul_test_0);
  tcase_add_test(tc1_1, num_mul_test_1);
  tcase_add_test(tc1_1, num_mul_test_2);
  tcase_add_test(tc1_1, num_mul_test_3);
  tcase_add_test(tc1_1, num_mul_test_4);
  tcase_add_test(tc1_1, num_mul_test_5);
  tcase_add_test(tc1_1, s21_mul_num_1_err);
  tcase_add_test(tc1_1, sum_test_1);
  tcase_add_test(tc1_1, sum_test_2);
  tcase_add_test(tc1_1, sum_test_3);
  tcase_add_test(tc1_1, sum_test_4);
  tcase_add_test(tc1_1, sum_test_5);
  tcase_add_test(tc1_1, sum_test_6);
  tcase_add_test(tc1_1, s21_sum_matrix_1_err);
  tcase_add_test(tc1_1, s21_sum_matrix_2_err);
  tcase_add_test(tc1_1, s21_sum_matrix_3_err);
  tcase_add_test(tc1_1, sub_test_1);
  tcase_add_test(tc1_1, sub_test_2);
  tcase_add_test(tc1_1, sub_test_3);
  tcase_add_test(tc1_1, sub_test_4);
  tcase_add_test(tc1_1, sub_test_5);
  tcase_add_test(tc1_1, sub_test_6);
  tcase_add_test(tc1_1, s21_sub_matrix_1_err);
  tcase_add_test(tc1_1, s21_sub_matrix_2_err);
  tcase_add_test(tc1_1, s21_sub_matrix_3_err);
  tcase_add_test(tc1_1, calc_complements_test_0);
  tcase_add_test(tc1_1, calc_complements_test_1);
  tcase_add_test(tc1_1, calc_complements_test_2);
  tcase_add_test(tc1_1, calc_complements_test_3);
  tcase_add_test(tc1_1, calc_complements_test_4);
  tcase_add_test(tc1_1, calc_complements_test_5);
  tcase_add_test(tc1_1, calc_complements_test_null_ptr1);
  tcase_add_test(tc1_1, calc_complements_test_null_ptr2);
  tcase_add_test(tc1_1, s21_alc_complements_3_err);
  tcase_add_test(tc1_1, det_test_0);
  tcase_add_test(tc1_1, det_test_1);
  tcase_add_test(tc1_1, det_test_2);
  tcase_add_test(tc1_1, det_test_3);
  tcase_add_test(tc1_1, det_test_4);
  tcase_add_test(tc1_1, det_test_5);
  tcase_add_test(tc1_1, det_test_null_ptr1);
  tcase_add_test(tc1_1, s21_determinant_3_err);
  tcase_add_test(tc1_1, inverse_matrix_test_0);
  tcase_add_test(tc1_1, inverse_matrix_test_1);
  tcase_add_test(tc1_1, inverse_matrix_test_2);
  tcase_add_test(tc1_1, inverse_matrix_test_3);
  tcase_add_test(tc1_1, inverse_matrix_test_4);
  tcase_add_test(tc1_1, inverse_matrix_test_5);
  tcase_add_test(tc1_1, inverse_matrix_test_null_ptr1);
  tcase_add_test(tc1_1, inverse_matrix_test_null_ptr2);
  tcase_add_test(tc1_1, s21_inverse_matrix_3_err);
  tcase_add_test(tc1_1, s21_inverse_matrix_4_err);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
