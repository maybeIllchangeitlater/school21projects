#ifndef _S21_SSCANF_H_
#define _S21_SSCANF_H_

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  char *string;
  int string_position;
  int sscanf_counter;
  int current_width;
  int current_sign;
} scanfopt;

typedef struct stack {
  struct stack *next;
  char flag;
  int width;
  char length;
  int skip;
  int is_a_flag;
} stack;

stack *s21_parse_format(const char *format, stack *head);
int s21_sscanf(const char *str, const char *format, ...);
void s21_parse_ss_arguments(va_list *ss_arguments, scanfopt *sconfig,
                            stack *head);
s21_size_t s21_atoi_(char *str);
int s21_is_digit(char ch);
int s21_is_hex(char ch);
int s21_is_scientific(char ch);
long double s21_atof(char *str);
stack *s21_push(stack *head, char f, int width, char length, int skip,
                int is_a_flag);
stack *s21_pop(stack *head);
void s21_destroy(stack *head);
stack *s21_flip_stack(stack *head);
stack *s21_flag_d(va_list *ss_arguments, scanfopt *sconfig, stack *tail);
stack *s21_flag_c(va_list *ss_arguments, scanfopt *sconfig, stack *tail);
stack *s21_flags_e(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_i(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_s(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_u(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_p(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_n(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flags_x(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
stack *s21_flag_o(va_list *ss_arguments, stack *tail, scanfopt *sconfig);
s21_size_t s21_convert_from_hex(char *buffer);
s21_size_t s21_convert_from_octal(char *buffer);
char *filling_buffer(char *buffer, scanfopt *sconfig, char *condition);
stack *checking_for_trash(scanfopt *sconfig, stack *tail);
char *deleting_extra_whitespaces(char *str);
int s21_is_whitespace(char ch);
void s21_what_sign(scanfopt *sconfig);

#endif
