#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0, sign1 = s21_get_bit(value_1, 127),
      sign2 = s21_get_bit(value_2, 127);
  if (s21_add_overflow(&value_1, &value_2)) {
    if (s21_get_exp(value_1) >= 1 && s21_get_exp(value_2) >= 1) {
      s21_divide_by_10(&value_1);
      s21_divide_by_10(&value_2);
    } else {
      if (!s21_get_exp(value_1)) {
        status = s21_get_sign(value_1) ? 2 : 1;
      } else {
        status = s21_get_sign(value_2) ? 2 : 1;
      }
    }
  }

  int round;
  if (!status) {
    for (int i = 0; i < 4; i++) result->bits[i] = 0;
    round = s21_convert(&value_1, &value_2);
    int pow_val = s21_get_exp(value_2);
    s21_set_exp(result, pow_val);
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      s21_set_bit(result, 127, 1);
      status = s21_bit_add(value_1, value_2, result);
      if (status) status++;
    } else if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
      if (s21_get_sign(value_1)) {
        s21_set_bit(&value_1, 127, 0);
        s21_sub(value_2, value_1, result);
      } else {
        s21_set_bit(&value_2, 127, 0);
        s21_sub(value_1, value_2, result);
      }
    } else {
      status = s21_bit_add(value_1, value_2, result);
    }
  }

  if (round) {
    unsigned int result_int = 0;
    result_int += ((unsigned)result->bits[0]);
    if (sign1 && result_int % 2 == 1) {
      if (sign2) {
        result->bits[0] -= 1;
      } else {
        result->bits[0] += 1;
      }
    } else if (!sign1 && result_int % 2 == 1) {
      if (sign2) {
        result->bits[0] += 1;
      } else {
        result->bits[0] -= 1;
      }
    }
  }

  return status;
}