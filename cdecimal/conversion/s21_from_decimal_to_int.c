#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == S21_NULL) return 1;
  *dst = 0;
  int COW = 0;
  int sign = s21_get_sign(src) ? -1 : 1;
  s21_decimal result = {0};
  s21_truncate(src, &result);
  if (result.bits[2] || result.bits[1] ||
      (sign == 1 ? result.bits[0] > __INT32_MAX__
                 : (unsigned)result.bits[0] > (unsigned)__INT32_MAX__ + 1))
    COW = 1;
  else
    *dst = (int)result.bits[0] * sign;
  return COW;
}