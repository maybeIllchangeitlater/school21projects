#include "../s21_decimal.h"

typedef struct {
  unsigned int bits[6];
} s21_uint_x6;

const unsigned long long pow_2_32 = 0x100000000;

s21_uint_x6 mul_mantises(s21_decimal value_1, s21_decimal value_2) {
  s21_uint_x6 long_result = {{0, 0, 0, 0, 0, 0}};
  unsigned long long num1_arr[3], num2_arr[3];
  for (int i = 0; i < 3; i++) {
    num1_arr[i] = (unsigned long long)(value_1.bits[i]);
    num2_arr[i] = (unsigned long long)(value_2.bits[i]);
  }
  unsigned long long buffer;
  unsigned long long buffer2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      buffer = num1_arr[i] * num2_arr[j];
      for (int k = i + j; k < 6 && buffer; k++) {
        buffer2 = long_result.bits[k] + buffer;
        long_result.bits[k] = (long_result.bits[k] + buffer) % pow_2_32;
        buffer = buffer2 / pow_2_32;
      }
    }
  }
  return long_result;
}

void just_add_1(s21_uint_x6 *long_result) {
  unsigned long long buffer = 1;
  for (int i = 0; i < 6 && buffer; i++) {
    unsigned long long buffer2 = (long_result->bits[i] + buffer) / pow_2_32;
    long_result->bits[i] = (long_result->bits[i] + buffer) % pow_2_32;
    buffer = buffer2;
  }
}

int reduce_long_result(s21_uint_x6 *long_result, int curr_exp) {
  int no_zero_meet = 0, mod_10 = 0, decrease_exp = 0, need_to_break = 0;
  for (int i = 1; (i <= curr_exp) && !need_to_break; i++) {
    need_to_break = !long_result->bits[3] && !long_result->bits[4];
    need_to_break &= !long_result->bits[5] && (curr_exp - i < 28);
    if (need_to_break) {
      int need_to_add_1 = (mod_10 == 5) && !no_zero_meet;
      need_to_add_1 &= (long_result->bits[0] % 2);
      need_to_add_1 |= (mod_10 == 5 && no_zero_meet);
      need_to_add_1 |= mod_10 > 5;
      if (need_to_add_1) {
        just_add_1(long_result);
      }
      need_to_break &= !long_result->bits[3];
      if (need_to_break) {
        decrease_exp = i - 1;
      }
    }
    unsigned long long buffer = 0;
    no_zero_meet |= (mod_10 > 0);
    for (int j = 5; (j >= 0) && !need_to_break; j--) {
      mod_10 = (long_result->bits[j] + buffer) % 10;
      long_result->bits[j] = (long_result->bits[j] + buffer) / 10;
      buffer = (mod_10) * (pow_2_32);
    }
  }
  return decrease_exp;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = 0;
  result->bits[3] = 0;
  int err = 0;
  s21_uint_x6 long_result = mul_mantises(value_1, value_2);
  int curr_exp = s21_get_exp(value_1) + s21_get_exp(value_2);
  int decrease_exp = reduce_long_result(&long_result, curr_exp);

  if (!long_result.bits[3] && !long_result.bits[4] && !long_result.bits[5]) {
    result->bits[0] = long_result.bits[0];
    result->bits[1] = long_result.bits[1];
    result->bits[2] = long_result.bits[2];
    s21_set_exp(result, curr_exp - decrease_exp);
    s21_set_bit(result, 127, s21_get_sign(value_2) ^ s21_get_sign(value_1));
  } else {
    err = (s21_get_sign(value_2) ^ s21_get_sign(value_1)) ? 2 : 1;
  }
  return err;
}
