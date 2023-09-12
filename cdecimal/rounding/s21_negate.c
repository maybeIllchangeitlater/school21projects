#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return 1;
  for (int i = 0; i <= 3; i++) {
    result->bits[i] = value.bits[i];
  }
  s21_get_sign(value) ? s21_set_bit(result, 127, 0)
                      : s21_set_bit(result, 127, 1);
  return 0;
}