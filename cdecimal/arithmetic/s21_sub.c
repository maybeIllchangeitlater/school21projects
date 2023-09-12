#include "../s21_decimal.h"
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int sign1 = s21_get_bit(value_1, 127);
  int sign2 = s21_get_bit(value_2, 127);

  for (int i = 0; i < 4; i++) result->bits[i] = 0;
  int round = s21_convert(&value_1, &value_2);
  int pow_val = s21_get_exp(value_1);
  s21_set_exp(result, pow_val);
  if (sign1 && sign2) {
    if (s21_is_less_or_equal(value_1, value_2)) {
      s21_substruction(value_1, value_2, result);
      s21_set_bit(result, 127, 1);
    } else
      s21_substruction(value_2, value_1, result);
  } else if (sign1 && !sign2) {
    s21_set_bit(result, 127, 1);
    s21_set_bit(&value_1, 127, 0);
    status = s21_bit_add(value_1, value_2, result);
    if (status) status++;
  } else if (!sign1 && sign2) {
    s21_set_bit(&value_2, 127, 0);
    status = s21_bit_add(value_1, value_2, result);
  } else {
    if (s21_is_less(value_1, value_2)) {
      s21_substruction(value_2, value_1, result);
      s21_set_bit(result, 127, 1);
    } else
      s21_substruction(value_1, value_2, result);
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

int s21_substruction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int occupy = 0;
  for (int i = 0; i <= 96; i++) {
    int bit1 = s21_get_bit(value_1, i);
    int bit2 = s21_get_bit(value_2, i);
    if (bit1 - bit2 - occupy == 1) {
      s21_set_bit(result, i, 1);
      occupy = 0;
    } else if (bit1 - bit2 - occupy == 0) {
      occupy = 0;
    } else if (bit1 - bit2 - occupy == -1) {
      occupy = 1;
      s21_set_bit(result, i, 1);
    }
  }
  return occupy;
}
