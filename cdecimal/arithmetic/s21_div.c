#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exp = -1, status = 0, pos = 0;
  int power_1 = s21_get_exp(value_1);
  int power_2 = s21_get_exp(value_2);
  if (power_1 < power_2) {
    s21_convert(&value_1, &value_2);
    power_1 = s21_get_exp(value_1);
    power_2 = s21_get_exp(value_2);
  }
  int sign_1 = s21_get_bit(value_1, 127);
  int sign_2 = s21_get_bit(value_2, 127);
  fill_decimals_with_zeros(result);
  s21_set_exp(&value_1, 0);
  s21_set_exp(&value_2, 0);
  s21_set_bit(&value_1, 127, 0);
  s21_set_bit(&value_2, 127, 0);
  if (s21_is_equal(value_2, *result)) status = 3;
  for (int i = 95; i >= 0; i--)
    if (pos == 0 && s21_get_bit(value_2, i)) pos = i;
  s21_decimal ten = value_2;
  while (s21_is_greater_or_equal(value_1, ten) && status == 0) {
    do {
      if (exp != -1) s21_shift_left(&ten);
      exp++;
    } while (s21_is_less_or_equal(ten, value_1) && exp <= 95 - pos);
    s21_decimal slag = {0};
    s21_set_bit(&slag, exp - 1, 1);
    s21_add(slag, *result, result);
    s21_shift_right(&ten);
    s21_sub(value_1, ten, &value_1);
    s21_set_bit(&value_2, 127, 0);
    exp = -1;
    ten = value_2;
  }
  if (sign_1 != sign_2) s21_set_bit(result, 127, 1);
  s21_set_exp(result, power_1 - power_2);
  return status;
}