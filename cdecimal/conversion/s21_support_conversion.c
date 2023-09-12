#include "../s21_decimal.h"

void parse_string_for_ftd(char *str, sprintfvals *kostyl) {
  int i = strlen(str) - 1, numlen = 0, meaningless_zeroes = 1;
  kostyl->mul_mantis_by = -1;
  while (str[i] != '+' && str[i] != '-') {
    kostyl->exp += (str[i] - '0') * pow(10, numlen++);
    i--;
  }
  kostyl->exp = str[i] == '+' ? -kostyl->exp : kostyl->exp;
  i -= 2, numlen = 0;
  while (i >= 0) {
    if (str[i] == '-')
      kostyl->mantis_sign = 1;
    else if (str[i] == '.')
      ;
    else if (meaningless_zeroes && str[i] == '0')
      ;
    else {
      meaningless_zeroes = 0, kostyl->mul_mantis_by++;
      kostyl->mantis += (str[i] - '0') * pow(10, numlen++);
    }
    i--;
  }
  kostyl->exp += kostyl->mul_mantis_by;
}

void fill_decimals_with_zeros(s21_decimal *val) {
  memset(val->bits, 0, sizeof(val->bits));
}

int s21_div_by_ten(s21_decimal value, s21_decimal *result) {
  unsigned long int buffer = 0;
  unsigned long int buffer2 = 0;
  buffer = (value.bits[2] % 10) * ((unsigned long int)__UINT32_MAX__ + 1);
  buffer2 =
      ((value.bits[1] + buffer) % 10) * ((unsigned long int)__UINT32_MAX__ + 1);
  result->bits[2] = (unsigned long)(value.bits[2]) / 10;
  result->bits[1] = (unsigned long)(value.bits[1] + buffer) / 10;
  result->bits[0] = (unsigned long)(value.bits[0] + buffer2) / 10;
  return (value.bits[0] + buffer2) % 10;
}