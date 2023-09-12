#include "s21_math.h"

long double s21_sin(double x) {
  long double res = 0;
  int sign = x < 0 ? -1 : 1;
  x = s21_fmod(s21_fabs(x), 2 * s21_PI);
  int counter = 0, status = 1;
  if (s21_isnan(x) || s21_isinf(x)) {
    status = 0;
  } else {
    for (int i = 1; i < 1000 && (s21_pow(x, i) / s21_factorial(i)) > s21_EPS;
         i += 2) {
      res += !counter ? (s21_pow(x, i) / s21_factorial(i))
                      : -(s21_pow(x, i) / s21_factorial(i));
      counter = ~counter;
    }
  }
  return status ? res * sign : s21_NAN;
}

long double s21_cos(double x) {
  long double sinus = s21_sin(x);
  long double where_is_x = 0.0;
  int sign = -1;
  where_is_x = (s21_fmod(s21_fabs(x), (2 * s21_PI)));
  if (where_is_x <= (s21_PI / 2) || where_is_x >= (s21_PI * 1.5)) sign = 1;
  // checks if x in positive or negative
  // quarter (it's mirrored for cos)
  int status = 1;
  if (s21_isnan(sinus) || s21_isinf(sinus)) {
    status = 0;
  }
  return status ? (s21_sqrt(1.0 - s21_pow(sinus, 2.0))) * sign : s21_NAN;
}

long double s21_tan(double x) {
  int status = 1;
  if (s21_isnan(x) || s21_isinf(x)) {
    status = 0;
  }
  return status ? s21_sin(x) / s21_cos(x) : s21_NAN;
}

long double s21_atan(double x) {
  int status = 1, counter = 0, too_big = 0;
  long double res = 0.0;
  int sign = x < 0 ? -1 : 1;
  x = s21_fabs(x);
  if (s21_isnan(x)) {
    status = 0;
  } else if (s21_isinf(x)) {
    res = s21_PI / 2;
  } else if (x == 1.0 || x == -1.0) {
    res = s21_PI / 4;
  } else {
    if (x > 1.0) {
      x = 1 / x;
      too_big = 1;
    }
    for (int i = 1; i < 1000.0 && (s21_pow(x, i) / i > s21_EPS); i += 2) {
      if (counter == 0) {
        res += (s21_pow(x, i) / i);
        counter++;
      } else {
        res -= (s21_pow(x, i) / i);
        counter--;
      }
    }
  }
  return status ? (!too_big ? res * sign : ((s21_PI / 2) - res) * sign)
                : s21_NAN;
}

long double s21_acos(double x) {
  int status = 1;
  long double result = s21_PI / 2;
  if (s21_isnan(x) || s21_isinf(x) || s21_fabs(x) > 1.0) {
    status = 0;
  } else {
    if (x == 1.0)
      result = 0;
    else if (x == (-1.0))
      result = s21_PI;
    else if (x > 0)
      result = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / (x));
    else if (x < 0)
      result = s21_PI + s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / (x));
  }
  return status ? result : s21_NAN;
}

long double s21_asin(double x) {
  int status = 1;
  long double result = s21_PI / 2;
  if (s21_isnan(x) || s21_isinf(x) || s21_fabs(x) > 1.0) {
    status = 0;
  } else {
    if (x == 1.0)
      result = 0;
    else if (x == (-1.0))
      result = -s21_PI / 2;
    else if (x == 0.0 || x == -0.0)
      result = x;
    else
      result = s21_PI / 2 - s21_acos(x);
  }
  return status ? result : s21_NAN;
}
