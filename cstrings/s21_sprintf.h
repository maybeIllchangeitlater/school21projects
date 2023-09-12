#ifndef SPR_S21_SPRINTF_H
#define SPR_S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct {
  int flag_zeropad;
  int flag_minus_left;
  int flag_plus;
  int flag_space;
  int flag_hash;
  int index_buffer;
  int index_format;
  unsigned int flag_width;
  unsigned int flag_precision;
  unsigned int precision;
  int flag_long_int;
  int flag_short;
  int long_double;
  int flag_upper_case;
  unsigned int base;
  int written_char;
  int flag_f;
} options;

int s21_sprintf(char *str, const char *format, ...);
void config_printf(char *buffer, const char *format, options *config,
                   va_list va);
void write_char_in_buffer(char *buffer, const char *format, options *config);
int s21_atoi(const char **format);
int is_digit(const char **format);
void ntoa_long(char *buffer, unsigned long value, int negative,
               options *config);
void ntoa_format(char *buffer, char *buf, unsigned int buf_size,
                 unsigned int len, int negative, options *config);
void reverse(char *buffer, char *buf, unsigned int len, options *config);
void s21_ftoa(char *buffer, long double value, options *config);
void s21_etoa(char *buffer, long double value, options *config);
unsigned int s21_strnlen(const char *str, unsigned int maxsize);
void config_s(char *buffer, char *p, options *config);
void config_c(char *buffer, char input_char, options *config);
void flags_congig(const char **format, int *counter, options *config);
void config_width_field(const char **format, va_list va, options *config);
void config_precision_field(const char **format, va_list va, options *config);
void config_length_field(const char **format, options *config);
void config_decimal(const char **format, options *config);
void convert_to_integer(const char **format, char *buffer, va_list va,
                        options *config);
void s21_gtoa(char *buffer, long double value, options *config);
#endif
