#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return 1;
  fill_decimals_with_zeros(result);
  unsigned int exp = (~(1 << 31) & value.bits[3]) >> 16;
  unsigned int remainder = 0;
  int flag_remainder_only_zeroes = 1;
  while (exp-- > 0) {
    remainder = s21_div_by_ten(value, &value);
    if (remainder != 0) flag_remainder_only_zeroes = 0;
  }
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  unsigned difference =
      (unsigned int)(((unsigned long int)S21_MAX_UINT + 1) / 10);
  if (value.bits[3] >> 31) s21_set_bit(result, 127, 1);
  if ((value.bits[3] >> 31) && (!flag_remainder_only_zeroes)) {
    if (result->bits[0] < S21_MAX_UINT) {
      result->bits[0] += 1;
    } else if (result->bits[1] < S21_MAX_UINT) {
      result->bits[0] -= difference, result->bits[1] += 1;
    } else if (result->bits[2] < S21_MAX_UINT) {
      result->bits[1] -= difference, result->bits[2] += 1;
    }
  }
  return 0;
}
