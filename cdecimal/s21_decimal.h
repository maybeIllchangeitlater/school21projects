#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int mantis;
  int exp;
  int mantis_sign;
  int mul_mantis_by;
  int exp_sign;
} sprintfvals;

typedef enum {
  s21_NORMAL_VALUE = 0,
  s21_INFINITY = 1,
  s21_NEGATIVE_INFINITY = 2,
  s21_NAN = 3
} value_type_t;

#define S21_NULL (void *)0

#define S21_MAX_DECIMAL 7.9228162514264337593543950335e+28
#define S21_MAX_UINT 4294967295  // for big tests

// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_substruction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_adding(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// compare
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// conversion
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// rounding
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// support functions
void s21_shift_right(s21_decimal* number);
void s21_shift_left(s21_decimal* number);
int s21_div_by_ten(s21_decimal value, s21_decimal *result);
void parse_string_for_ftd(char *str, sprintfvals *kostyl);
void fill_decimals_with_zeros(s21_decimal *val);
unsigned int s21_divide_by_10(s21_decimal *number);
void s21_set_exp(s21_decimal *value, int pow);
int s21_get_highest_bit(s21_decimal number);
void s21_set_scale(s21_decimal *number, int scale);
int s21_add_overflow(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_null(s21_decimal value);
void s21_set_bit(s21_decimal *varPtr, int bit, int value);
int s21_get_bit(const s21_decimal decVar, int bit);
int s21_convert(s21_decimal *value_1, s21_decimal *value_2);
int s21_exp_up(s21_decimal *value);
int s21_get_exp(s21_decimal value);
int s21_get_sign(s21_decimal value);
int s21_diff_up(s21_decimal *value_1, s21_decimal *value_2, int *different);
int s21_diff_down(s21_decimal *value_1, s21_decimal *value_2, int *different);
int s21_bit_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif /*S21_DECIMAL_H*/