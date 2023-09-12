#include <stdio.h>

#include "s21_decimal.h"

void s21_shift_left(s21_decimal* number) {
  int low_last_bit = s21_get_bit(*number, 31);
  int mid_last_bit = s21_get_bit(*number, 63);

  number->bits[0] <<= 1;
  number->bits[1] <<= 1;
  number->bits[2] <<= 1;

  s21_set_bit(number, 32, low_last_bit);
  s21_set_bit(number, 64, mid_last_bit);
}

void s21_shift_right(s21_decimal* number) {
  int low_last_bit = s21_get_bit(*number, 32);
  int mid_last_bit = s21_get_bit(*number, 64);

  number->bits[0] >>= 1;
  number->bits[1] >>= 1;
  number->bits[2] >>= 1;

  s21_set_bit(number, 31, low_last_bit);
  s21_set_bit(number, 63, mid_last_bit);
}

unsigned int s21_divide_by_10(s21_decimal* number) {
  unsigned int buffer = 0;

  int sign = s21_get_sign(*number);
  int scale_of_number = s21_get_exp(*number);
  s21_decimal result = {{0, 0, 0, 0}};

  int highest_bit_position = s21_get_highest_bit(*number);

  for (int i = 0; i < highest_bit_position + 2; i++) {
    if (buffer >= 10) {
      s21_shift_left(&result);
      s21_set_bit(&result, 0, 1);
      buffer = buffer - 10u;
      int new_bit = s21_get_bit(*number, highest_bit_position - i);
      buffer = buffer << 1;
      buffer |= new_bit;
    } else {
      s21_shift_left(&result);
      s21_set_bit(&result, 0, 0);
      int new_bit = s21_get_bit(*number, highest_bit_position - i);
      buffer = buffer << 1;
      buffer |= new_bit;
    }
  }

  buffer = buffer >> 1;
  *number = result;
  s21_set_bit(number, 127, sign);
  s21_set_scale(number, scale_of_number - 1);

  return buffer;
}

void s21_set_exp(s21_decimal* value, int exp) {
  int clearMask = ~(0xFF << 16);
  value->bits[3] &= clearMask;
  int mask = exp << 16;
  value->bits[3] |= mask;
}

int s21_bit_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int occupy = 0;
  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(value_1, i);
    int bit2 = s21_get_bit(value_2, i);
    if (bit1 + bit2 + occupy == 1) {
      s21_set_bit(result, i, 1);
      occupy = 0;
    } else if (bit1 + bit2 + occupy == 2) {
      occupy = 1;
    } else if (bit1 + bit2 + occupy == 3) {
      s21_set_bit(result, i, 1);
      occupy = 1;
    } else
      occupy = 0;
  }
  return occupy;
}

void s21_set_scale(s21_decimal* number, int scale) {
  int sign = s21_get_sign(*number);

  number->bits[3] = scale;
  number->bits[3] <<= 16;

  if (sign == 1) {
    s21_set_bit(number, 127, 1);
  }
}

int s21_convert(s21_decimal* value_1, s21_decimal* value_2) {
  int round = 0;
  int different = s21_get_exp(*value_1) - s21_get_exp(*value_2);
  if (different < 0) {
    round = s21_diff_up(value_1, value_2, &different);
  } else if (different > 0) {
    round = s21_diff_down(value_1, value_2, &different);
  }
  return round;
}

int s21_diff_up(s21_decimal* value_1, s21_decimal* value_2, int* different) {
  int round = 0;
  for (; *different < 0 && !(round = s21_exp_up(value_1)); (*different)++) {
    continue;
  }
  for (; *different < 0; (*different)++) {
    round = s21_divide_by_10(value_2);
  }
  return round;
}

int s21_diff_down(s21_decimal* value_1, s21_decimal* value_2, int* different) {
  int round = 0;
  for (; *different > 0 && !(round = s21_exp_up(value_2)); (*different)--) {
    continue;
  }
  for (; *different < 0; (*different)++) {
    round = s21_divide_by_10(value_1);
  }
  return round;
}

int s21_add_overflow(s21_decimal* value_1, s21_decimal* value_2) {
  unsigned long exp = 0;
  for (int i = 0; i < 3; i += 1) {
    exp = (exp + (long)(unsigned)value_1->bits[i] +
           (long)(unsigned)value_2->bits[i]) >>
          32;
  }
  return exp;
}

int s21_exp_up(
    s21_decimal* value) {  // Если вернуло 0, то умножение прошло удачно, иначе
                           // число не изменится и будет возвращен !0
  unsigned long carry = 0;
  s21_decimal buffer = {0};
  if (s21_get_exp(*value) + 1 < 29) {
    for (int i = 0; i < 3; i++) {
      buffer.bits[i] = value->bits[i] * 10;
      buffer.bits[i] += carry;
      carry = ((unsigned long)(unsigned)value->bits[i] * 10) >> 32;
    }
  } else {
    carry = -1;
  }

  if (!carry) {
    buffer.bits[3] = value->bits[3] + (1u << 16);
    *value = buffer;
  }
  return carry;
}

int s21_is_null(s21_decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}

void s21_set_bit(s21_decimal* varPtr, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (bit / 32 < 4 && value) {
    varPtr->bits[bit / 32] |= mask;
  } else if (bit / 32 < 4 && !value) {
    varPtr->bits[bit / 32] &= ~mask;
  }
}

int s21_get_bit(const s21_decimal decVar, int bit) {
  int res = 0;
  if (bit / 32 < 4) {
    unsigned int mask = 1u << (bit % 32);
    res = decVar.bits[bit / 32] & mask;
  }
  return res != 0;
}

int s21_get_exp(s21_decimal value) {
  return (char)(((unsigned)value.bits[3]) >> 16);
}

int s21_get_sign(s21_decimal value) { return ((unsigned)value.bits[3] >> 31); }

int s21_get_highest_bit(s21_decimal number) {
  int bit_position = -1;
  for (int i = 0; i < 96 && bit_position == -1; i++) {
    if (s21_get_bit(number, (95 - i)) == 1) {
      bit_position = (95 - i);
    }
  }
  return bit_position;
}