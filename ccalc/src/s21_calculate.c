#include "s21_to_curva.h"

double calculate(Stack* reversedKurva) {
  Stack* result = NULL;
  Stack* kurvaClone = reversedKurva;
  double intermediate_value = 0.0,
         x_value = kurvaClone->oper == 'p' ? kurvaClone->value : 0.0;
  if (kurvaClone->oper == 'p') kurvaClone = kurvaClone->next;
  while (kurvaClone != NULL) {
    if (kurvaClone->oper == 'f' || kurvaClone->oper == 'X') {
      result = kurvaClone->oper == 'X'
                   ? push(result, x_value, 'f')
                   : push(result, kurvaClone->value, kurvaClone->oper);
    } else {
      intermediate_value = result->value;
      result = pop(result);
      if (kurvaClone->oper == '+') {
        intermediate_value += result->value;
        result = pop(result);
      } else if (kurvaClone->oper == '-') {
        intermediate_value = result->value - intermediate_value;
        result = pop(result);
      } else if (kurvaClone->oper == '*') {
        intermediate_value *= result->value;
        result = pop(result);
      } else if (kurvaClone->oper == '/') {
        intermediate_value = result->value / intermediate_value;
        result = pop(result);
      } else if (kurvaClone->oper == 's') {
        intermediate_value = sin(intermediate_value);
      } else if (kurvaClone->oper == 'c') {
        intermediate_value = cos(intermediate_value);
      } else if (kurvaClone->oper == 't') {
        intermediate_value = tan(intermediate_value);
      } else if (kurvaClone->oper == 'S') {
        intermediate_value = asin(intermediate_value);
      } else if (kurvaClone->oper == 'C') {
        intermediate_value = acos(intermediate_value);
      } else if (kurvaClone->oper == 'T') {
        intermediate_value = atan(intermediate_value);
      } else if (kurvaClone->oper == 'q') {
        intermediate_value = sqrt(intermediate_value);
      } else if (kurvaClone->oper == '^') {
        intermediate_value = pow(result->value, intermediate_value);
        result = pop(result);
      } else if (kurvaClone->oper == 'm') {
        intermediate_value = fmod(result->value, intermediate_value);
        result = pop(result);
      } else if (kurvaClone->oper == 'o') {
        intermediate_value = log10(intermediate_value);
      } else if (kurvaClone->oper == 'n') {
        intermediate_value = log(intermediate_value);
      } else if (kurvaClone->oper == '!') {
        intermediate_value = factorial(intermediate_value);
      } else if (kurvaClone->oper == 'u') {
        intermediate_value = -intermediate_value;
      }
      result = push(result, intermediate_value, 'f');
    }
    kurvaClone = kurvaClone->next;
  }
  intermediate_value = result->value;
  destroy(result);
  return intermediate_value;
}

double factorial(long long int x) {
  if (x == 1 || x == 0) return 1;
  if (x < 0) return 1.0 / 0.0;
  double fac = x * factorial(x - 1);
  return fac;
}

// double res_kurva = 0.0, res_og = 0.0;
// const char * string =
// "(-sin(0.5)+cos(0.5)+tan(0.5)+acos(0.5)+atan(0.5)+Asin(0.5)*5)/0.3^2
// -mod(7,3)--5 + 3!/2! +ln(3) + log(2)"; char result[255] = {0}; solve(string,
// result); res_kurva = atof(result); res_og = (-sin(0.5) + cos(0.5) + tan(0.5)
// + atan(0.5) + acos(0.5) + asin(0.5)*5)/pow(0.3,2)-fmod(7,3)+5 + 6/2 + log(3)
// - log10(2); ck_assert_float_eq(res_kurva, res_og);
