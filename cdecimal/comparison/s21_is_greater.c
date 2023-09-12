#include "./../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_a = s21_get_sign(value_1), sign_b = s21_get_sign(value_2);
  if (!(s21_is_null(value_1) && s21_is_null(value_2))) {
    if (sign_a != sign_b) {
      if (sign_a == 0) {
        res = 1;
      } else {
        res = 0;
      }
    } else {
      s21_convert(&value_1, &value_2);
      for (int i = 95; i >= 0; i--) {
        int bit_a = s21_get_bit(value_1, i), bit_b = s21_get_bit(value_2, i);
        if (bit_a != bit_b) {
          if (bit_a != 0) {
            res = (sign_a == 0) ? 1 : 0;
            break;
          } else {
            res = (sign_a == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  }
  return res;
}
