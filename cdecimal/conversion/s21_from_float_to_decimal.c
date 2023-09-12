#include "../s21_decimal.h"

int s21_from_float_to_decimal(float source, s21_decimal *dst) {
  if (dst == S21_NULL) return 1;
  fill_decimals_with_zeros(dst);
  if (isinf(source) || isnan(source) || fabs(source) > S21_MAX_DECIMAL ||
      (fabs(source) > 0 && fabs(source) < 1e-28))
    return 1;
  char str[20] = {0};
  sprintf(str, "%e", source);
  sprintfvals kostyl = {0};
  parse_string_for_ftd(str, &kostyl);
  dst->bits[0] = kostyl.mantis;
  s21_set_bit(dst, 127, kostyl.mantis_sign);
  while (kostyl.exp > 28) {
    s21_div_by_ten(*dst, dst);
    kostyl.exp--;
  }
  while (kostyl.exp < 0) {
    s21_exp_up(dst);
    kostyl.exp++;
  }
  s21_set_exp(dst, kostyl.exp);
  return 0;
}