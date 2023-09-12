#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal decimal, float *destination) {
  if (destination == S21_NULL) return 1;
  *destination = 0.0F;
  double value_one = 0.0, value_two = 0.0, value_zero = 0.0;
  int sign = s21_get_sign(decimal);
  unsigned int exp = (~(1 << 31) & decimal.bits[3]) >> 16;
  value_two = decimal.bits[2] * (pow(2, 64));
  value_one = decimal.bits[1] * (pow(2, 32));
  value_zero = decimal.bits[0];
  *destination = ((value_one + value_two + value_zero)) / pow(10, exp);
  if (sign) {
    *destination *= -1;
  }
  return 0;
}