#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == S21_NULL) return 1;
  fill_decimals_with_zeros(dst);
  if (src < 0) {
    s21_set_bit(dst, 127, 1);
    src *= -1;
  }
  dst->bits[0] = (unsigned)src;
  return 0;
}
