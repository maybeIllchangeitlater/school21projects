#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return 1;
  fill_decimals_with_zeros(result);
  unsigned int exp = (~(1 << 31) & value.bits[3]) >> 16;
  unsigned int ostatok = 0;
  while (exp-- > 0) {
    ostatok = s21_div_by_ten(value, &value);
  }
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  ostatok = ostatok >= 5 ? 1 : 0;
  if (value.bits[3] >> 31) s21_set_bit(result, 127, 1);
  if (result->bits[0] < S21_MAX_UINT) {
    result->bits[0] += ostatok;
  } else if (result->bits[1] < S21_MAX_UINT) {
    result->bits[0] -=
        (unsigned int)(((unsigned long int)S21_MAX_UINT + 1) / 10);
    result->bits[1] += ostatok;
  } else if (result->bits[2] < S21_MAX_UINT) {
    result->bits[1] -=
        (unsigned int)(((unsigned long int)S21_MAX_UINT + 1) / 10);
    result->bits[2] += ostatok;
  }
  return 0;
}