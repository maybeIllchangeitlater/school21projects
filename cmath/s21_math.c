#include "s21_math.h"

int s21_abs(int x) {
  return (x >> (sizeof(int) * 8 - 1)) ? ~x + 1 : x;
  // if last bit is 1 - sign negative, to convert to positive reverse and append
  // because 0 exist
}

long double s21_fabs(double x) {
  uint64_t *intPtr = (uint64_t *)&x;  // adresses because otherwise it tries to
                                      // force type - works like union
  uint64_t sign_bit =
      *intPtr & (1ULL << 63);  // gets 0000000'd xber except for sign which is
                               // 0 unless it was 1
  uint64_t inverted =
      *intPtr ^
      sign_bit;  // xor will set it to 0 (0 && 0) or (0 & 1) xor is 0 either way
  double *resPtr = (double *)&inverted;
  return (long double)*resPtr;
}

long double s21_ceil(double x) {  // 0.8
  if (x != x) return s21_NAN;
  long long int my_ceil = (long long int)x;
  double fraction_check = x / my_ceil;
  if (my_ceil == 0 && x < 0) {  // -
    float my_minus_is_zero = -0.0;
    return ((long double)my_minus_is_zero);
  }
  if (fraction_check > 1) {
    if (my_ceil >= 0) ++my_ceil;
  }
  if (my_ceil == 0 && x > 0) my_ceil++;
  return ((long double)my_ceil);
}

long double s21_factorial(long long int x) {
  if (x == 1 || x == 0) return 1;
  if (x < 0) return (1.0 / 0.0);
  long double my_factorial = x * s21_factorial(x - 1);
  return my_factorial;
}

long double s21_sqrt(double x) {
  if (x != x || x < 0) return s21_NAN;
  return s21_pow(x, 0.5);
}

long double s21_floor(double x) {  // -1
  if (x != x) return s21_NAN;
  long long int my_floor = (long long int)x;
  double we_missed_the_crutch = my_floor / x;
  if (x < 0 && we_missed_the_crutch != 1) --my_floor;
  if (my_floor == 0 && x < 0) {
    float my_minus_is_zero = -0.0;
    return ((long double)my_minus_is_zero);
  }
  return ((long double)my_floor);
}

long double s21_exp(double x) {
  long double res = 1.;
  return (s21_exp_err(x, &res)) ? s21_calc_exp(x) : res;
}

long double s21_calc_exp(double x) {
  long double result = 1.0;
  int sign = (x < 0) ? -1 : 1;
  x = s21_fabs(x);
  long double tmp_x = (long double)x;
  double add = 1.0;
  for (int i = 1; s21_fabs(add / result) > 1e-100; i++) {
    add = add * tmp_x / i;
    result += add;
    if (result > s21_DBL_MAX) {
      result = s21_INF;
      break;
    }
  }
  if (sign == -1) {
    result = 1.0 / result;
  }
  return result;
}

int s21_exp_err(double x, long double *result) {
  int status = 1;
  if (s21_isnan(x) || x == s21_INF) {
    *result = x;
    status = 0;
  } else if (x == s21_NINF) {
    *result = 0.0;
    status = 0;
  }
  return status;
}

long double s21_pow(double base, double exp) {
  long double res = 0;
  long long int kostyl = (long long int)exp;  // 4.8->4
  if (exp == 0 || (s21_fabs(base) == 1.0 && s21_isinf(exp))) {
    res = 1.0;
  } else {
    int sign = base < 0 ? -1 : 1;
    res = s21_exp(exp * s21_log(base * sign));
    if (s21_fmod(exp, 2)) res *= sign;
  }
  if (res == s21_NINF) res = s21_INF;
  if (res != s21_NAN && base < 0 && exp / kostyl != 1 && res != 1 && res != 0 &&
      res != s21_INF)
    res = s21_NAN;
  return res;
}

long double s21_fmod(double x, double y) {
  return (y ? (((long double)(x / y) - (long long int)(x / y)) * y)
            : (1.0 / 0.0));
}

long double s21_log(double x) {
  long double res_clown = 0, copy_res = 0;
  int i = 0;
  if (x == s21_INF) {
    res_clown = s21_INF;
  } else if (s21_isnan(x) || x < 0) {
    res_clown = s21_NAN;
  } else if (x == 0) {
    res_clown = s21_NINF;
  } else if (x > 0) {
    for (; x >= s21_E; i++) x /= s21_E;
    for (int j = 0; j < 150; j++) {
      copy_res = res_clown;
      res_clown = copy_res + 2 * (x - s21_exp((double)copy_res)) /
                                 (x + s21_exp((double)copy_res));
    }
  }
  res_clown += i;
  return res_clown;
}
