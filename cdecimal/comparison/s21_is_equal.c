#include "./../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    s21_convert(&value_1, &value_2);
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit(value_1, i) != s21_get_bit(value_2, i)) {
        res = 0;
        break;
      }
    }
  } else if (!(s21_is_null(value_1) && s21_is_null(value_2))) {
    res = 0;
  }
  return res;
}
