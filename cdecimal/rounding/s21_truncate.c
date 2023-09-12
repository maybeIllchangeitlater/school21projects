#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return 1;
  fill_decimals_with_zeros(result);
  unsigned int exp = (~(1 << 31) & value.bits[3]) >> 16;
  while (exp-- > 0) s21_div_by_ten(value, &value);
  result->bits[2] = value.bits[2];
  result->bits[1] = value.bits[1];
  result->bits[0] = value.bits[0];
  s21_set_bit(result, 127, s21_get_sign(value));
  return 0;
}