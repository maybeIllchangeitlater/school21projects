#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  scanfopt sconfig = {0};
  sconfig.string = deleting_extra_whitespaces((char *)(str));
  stack *head = malloc(sizeof(stack));
  head->next = s21_NULL;
  head = s21_parse_format(format, head);
  if (head != s21_NULL) {
    stack *tail = s21_flip_stack(head);
    s21_destroy(head);
    tail = s21_pop(tail);
    va_list ss_arguments;
    va_start(ss_arguments, format);
    s21_parse_ss_arguments(&ss_arguments, &sconfig, tail);
    va_end(ss_arguments);
  }
  free(sconfig.string);
  return sconfig.sscanf_counter;
}

char *deleting_extra_whitespaces(char *str) {
  char *fxdstr = malloc(sizeof(char) * s21_strlen(str) + 1);
  char prev_ch = str[0];
  fxdstr[0] = str[0];
  s21_size_t j = 1;
  for (s21_size_t i = 1; i < s21_strlen(str) && str[i] != '\0'; i++) {
    if (!(s21_is_whitespace(str[i]) && s21_is_whitespace(prev_ch))) {
      fxdstr[j] = str[i];
      j++;
    }
    prev_ch = str[i];
  }
  fxdstr[j] = '\0';
  return fxdstr;
}

stack *s21_flip_stack(stack *head) {
  stack *newhead = s21_NULL;
  while (head != s21_NULL) {
    newhead = s21_push(newhead, head->flag, head->width, head->length,
                       head->skip, head->is_a_flag);
    head = head->next;
  }
  return newhead;
}

stack *s21_parse_format(const char *format, stack *head) {
  int percentage_met = 0, length_met = 0;
  for (s21_size_t i = 0; i < s21_strlen(format);) {
    int width = 0;
    if (format[i] == '%') {
      head = s21_push(head, '\0', 0, '\0', 0, 0);
      percentage_met = 1;
      i++;
    } else if (percentage_met && format[i] == '*') {
      head->skip = 1;
      i++;
    } else if (percentage_met &&
               (format[i] == 'L' || format[i] == 'l' || format[i] == 'h')) {
      head->length = format[i];
      length_met = 1;
      i++;
    } else if (percentage_met &&
               (format[i] == 'd' || format[i] == 'c' || format[i] == 'f' ||
                format[i] == 'e' || format[i] == 'E' || format[i] == 'g' ||
                format[i] == 'G' || format[i] == 'i' || format[i] == 's' ||
                format[i] == 'u' || format[i] == 'p' || format[i] == 'n' ||
                format[i] == 'x' || format[i] == 'X' || format[i] == 'o')) {
      percentage_met = 0;
      length_met = 0;
      head->flag = format[i];
      head->is_a_flag = 1;
      i++;
    } else if (percentage_met && !length_met && s21_is_digit(format[i])) {
      while (s21_is_digit(format[i])) {
        width = width * 10 + (unsigned int)((format[i]) - '0');
        i++;
      }
      head->width = width;
    } else if (!percentage_met || format[i] == '%') {
      while (s21_is_whitespace(format[i]) && s21_is_whitespace(format[i + 1]) &&
             (i + 1) < s21_strlen(format)) {
        i++;
      }
      head = s21_push(head, format[i], 0, '\0', 0, 0);
      i++;
    } else {
      s21_destroy(head);
      return s21_NULL;
    }
  }
  return head;
}

stack *s21_flag_d(va_list *ss_arguments, scanfopt *sconfig, stack *tail) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  s21_what_sign(sconfig);
  char buffer[sconfig->current_width + 1];
  filling_buffer(buffer, sconfig, "decimal");
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'h')
      *(short *)ptr = (short)s21_atoi_(buffer) * sconfig->current_sign;
    else if (tail->length == 'l')
      *(long int *)ptr = (long int)s21_atoi_(buffer) * sconfig->current_sign;
    else
      *(int *)ptr = (int)s21_atoi_(buffer) * sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_c(va_list *ss_arguments, scanfopt *sconfig, stack *tail) {
  if (!tail->skip) {
    char *ptr = va_arg(*ss_arguments, char *);
    *ptr = sconfig->string[sconfig->string_position];
    sconfig->sscanf_counter++;
    for (int i = 1; i < tail->width; i++) sconfig->string_position++;
  }
  sconfig->string_position++;
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flags_e(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  s21_what_sign(sconfig);
  char buffer[sconfig->current_width + 1];
  filling_buffer(buffer, sconfig, "science");
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'L')
      *(long double *)ptr =
          (long double)s21_atof(buffer) * sconfig->current_sign;
    else
      *(float *)ptr = (float)s21_atof(buffer) * sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_i(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  s21_size_t kostil = 0;
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  s21_what_sign(sconfig);
  if (sconfig->string[sconfig->string_position] == '0') {
    if ((int)s21_strlen(sconfig->string) > sconfig->string_position + 1 &&
        (sconfig->string[sconfig->string_position + 1] == 'x' ||
         sconfig->string[sconfig->string_position + 1] == 'X')) {
      filling_buffer(buffer, sconfig, "hex");
      kostil = s21_convert_from_hex(buffer);
    } else {
      filling_buffer(buffer, sconfig, "octal");
      kostil = s21_convert_from_octal(buffer);
    }
  } else {
    filling_buffer(buffer, sconfig, "decimal");
    kostil = s21_atoi_(buffer);
  }
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'h')
      *(short *)ptr = (short)(kostil)*sconfig->current_sign;
    else if (tail->length == 'l')
      *(long int *)ptr = (long int)(kostil)*sconfig->current_sign;
    else
      *(int *)ptr = (int)(kostil)*sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}
stack *s21_flags_x(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  s21_what_sign(sconfig);
  filling_buffer(buffer, sconfig, "hex");
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'h')
      *(short unsigned *)ptr =
          (short unsigned)s21_convert_from_hex(buffer) * sconfig->current_sign;
    else if (tail->length == 'l')
      *(s21_size_t *)ptr =
          (s21_size_t)s21_convert_from_hex(buffer) * sconfig->current_sign;
    else
      *(unsigned int *)ptr =
          (unsigned int)s21_convert_from_hex(buffer) * sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_o(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  s21_what_sign(sconfig);
  filling_buffer(buffer, sconfig, "octal");
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'h')
      *(short unsigned *)ptr = (short unsigned)s21_convert_from_octal(buffer) *
                               sconfig->current_sign;
    else if (tail->length == 'l')
      *(s21_size_t *)ptr =
          (s21_size_t)s21_convert_from_octal(buffer) * sconfig->current_sign;
    else
      *(unsigned int *)ptr =
          (unsigned int)s21_convert_from_octal(buffer) * sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_n(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  if (!tail->skip) {
    int *ptr = va_arg(*ss_arguments, int *);
    *ptr = sconfig->string_position;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_s(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  filling_buffer(buffer, sconfig, "string");
  if (!tail->skip) {
    char *ptr = va_arg(*ss_arguments, char *);
    s21_memcpy(ptr, buffer, s21_strlen(buffer) + 1);
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_u(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  s21_what_sign(sconfig);
  filling_buffer(buffer, sconfig, "decimal");
  if (!tail->skip) {
    void *ptr = va_arg(*ss_arguments, void *);
    if (tail->length == 'h')
      *(unsigned short *)ptr =
          (unsigned short)s21_atoi_(buffer) * sconfig->current_sign;
    else if (tail->length == 'l')
      *(s21_size_t *)ptr =
          (s21_size_t)s21_atoi_(buffer) * sconfig->current_sign;
    else
      *(unsigned int *)ptr =
          (unsigned int)s21_atoi_(buffer) * sconfig->current_sign;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

stack *s21_flag_p(va_list *ss_arguments, stack *tail, scanfopt *sconfig) {
  if (sconfig->string[sconfig->string_position] == '0' &&
      (sconfig->string[sconfig->string_position + 1] == 'x' ||
       sconfig->string[sconfig->string_position + 1] == 'X')) {
    sconfig->string_position += 2;
  }
  s21_size_t value = 0;
  sconfig->current_width = tail->width == 0 ? 1024 : tail->width;
  char buffer[sconfig->current_width + 1];
  filling_buffer(buffer, sconfig, "hex");
  value = s21_convert_from_hex(buffer);
  if (!tail->skip) {
    void **ptr = va_arg(*ss_arguments, void **);
    *ptr = (void *)value;
    sconfig->sscanf_counter++;
  }
  tail = s21_pop(tail);
  return tail;
}

s21_size_t s21_convert_from_hex(char *buffer) {
  s21_size_t decimal = 0;
  while (s21_is_hex(*buffer)) {
    int digit;
    if (*buffer >= '0' && *buffer <= '9')
      digit = *buffer - '0';
    else if (*buffer >= 'a' && *buffer <= 'f')
      digit = *buffer - 'a' + 10;
    else if (*buffer >= 'A' && *buffer <= 'F')
      digit = *buffer - 'A' + 10;
    else
      break;
    decimal = decimal * 16 + digit;
    buffer++;
  }
  return decimal;
}

s21_size_t s21_convert_from_octal(char *buffer) {
  s21_size_t decimal = 0;
  while (*buffer <= '7' && *buffer >= '0') {
    int digit;
    digit = *buffer - '0';
    decimal = decimal * 8 + digit;
    buffer++;
  }
  return decimal;
}
stack *checking_for_trash(scanfopt *sconfig, stack *tail) {
  if (s21_is_whitespace(sconfig->string[sconfig->string_position]) &&
      tail->is_a_flag && !(tail->flag == 'c')) {
    sconfig->string_position++;
  }
  if (!tail->is_a_flag) {
    while (sconfig->string[sconfig->string_position] == tail->flag &&
           !tail->is_a_flag) {
      sconfig->string_position++;
      tail = s21_pop(tail);
    }
    if (s21_is_whitespace(sconfig->string[sconfig->string_position]) &&
        tail->is_a_flag && !(tail->flag == 'c')) {
      sconfig->string_position++;
    }
    if (!tail->is_a_flag) {
      s21_destroy(tail);
      return s21_NULL;
    }
  }
  return tail;
}

void s21_parse_ss_arguments(va_list *ss_arguments, scanfopt *sconfig,
                            stack *tail) {
  while (tail != s21_NULL) {
    tail = checking_for_trash(sconfig, tail);
    if (tail == s21_NULL) return;
    if (tail->flag == 'd')
      tail = s21_flag_d(ss_arguments, sconfig, tail);
    else if (tail->flag == 'c')
      tail = s21_flag_c(ss_arguments, sconfig, tail);
    else if (tail->flag == 'e' || tail->flag == 'E' || tail->flag == 'G' ||
             tail->flag == 'g' || tail->flag == 'f')
      tail = s21_flags_e(ss_arguments, tail, sconfig);
    else if (tail->flag == 'i')
      tail = s21_flag_i(ss_arguments, tail, sconfig);
    else if (tail->flag == 's')
      tail = s21_flag_s(ss_arguments, tail, sconfig);
    else if (tail->flag == 'u')
      tail = s21_flag_u(ss_arguments, tail, sconfig);
    else if (tail->flag == 'p')
      tail = s21_flag_p(ss_arguments, tail, sconfig);
    else if (tail->flag == 'n')
      tail = s21_flag_n(ss_arguments, tail, sconfig);
    else if (tail->flag == 'x' || tail->flag == 'X')
      tail = s21_flags_x(ss_arguments, tail, sconfig);
    else if (tail->flag == 'o')
      tail = s21_flag_o(ss_arguments, tail, sconfig);
    else
      break;
  }
  s21_destroy(tail);
}

s21_size_t s21_atoi_(char *str) {
  s21_size_t i = 0;
  while (s21_is_digit(*str)) {
    i = i * 10 + (unsigned int)((*str) - '0');
    str++;
  }
  return i;
}

long double s21_atof(char *str) {
  long double result = 0.0, factor = 1.0;
  int fraction = 0, exponent = 0, exponent_sign = 1;
  result = (long double)s21_atoi_(str);
  while (s21_is_digit(*str)) str++;
  if (*str == '.') {  // fractional part
    fraction = 1;
    str++;
    while (s21_is_digit(*str)) {
      result = result * 10.0 + (unsigned int)(*str - '0');
      str++;
      factor *= 10.0;
    }
  }
  if (*str == 'e' || *str == 'E') {  // exponent
    str++;
    if (*str == '+') {
      str++;
      exponent = 1;
    } else if (*str == '-') {
      exponent = 1;
      exponent_sign = -1;
      str++;
    }
    exponent = s21_atoi_((str));
    exponent *= exponent_sign;
    while (s21_is_digit(*str)) str++;
  }
  if (fraction) {
    result /= factor;
  }
  if (exponent) {
    result *= powl(10, exponent);
  }
  return result;
}

int s21_is_hex(char ch) {
  int boolean = 0;
  if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') ||
      (ch >= 'A' && ch <= 'F')) {
    boolean = 1;
  }
  return boolean;
}

int s21_is_digit(char ch) {
  int boolean = 0;
  if ((ch >= '0') && (ch <= '9')) {
    boolean = 1;
  }
  return boolean;
}

int s21_is_scientific(char ch) {
  int booly = 0;
  if (s21_is_digit(ch) || (ch == 'E') || (ch == 'e') || (ch == '+') ||
      (ch == '-') || (ch == '.'))
    booly = 1;
  return booly;
}

int s21_is_whitespace(char ch) {
  int booger = 0;
  if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\f' || ch == '\r')
    booger = 1;
  return booger;
}

void s21_what_sign(scanfopt *sconfig) {
  sconfig->current_sign = 1;
  if (sconfig->string[sconfig->string_position] == '+') {
    sconfig->string_position++;
    sconfig->current_width--;
  }
  if (sconfig->string[sconfig->string_position] == '-') {
    sconfig->string_position++;
    sconfig->current_width--;
    sconfig->current_sign = -1;
  }
}

char *filling_buffer(char *buffer, scanfopt *sconfig, char *condition) {
  int i = 0;
  if (s21_strncmp(condition, "hex", 3) == 0) {
    if ((int)(s21_strlen(sconfig->string)) > sconfig->string_position + 2 &&
        sconfig->string[sconfig->string_position] == '0' &&
        (sconfig->string[sconfig->string_position + 1] == 'X' ||
         sconfig->string[sconfig->string_position + 1] == 'x')) {
      sconfig->string_position += 2;
      sconfig->current_width -= 2;
    }
    while (s21_is_hex(sconfig->string[sconfig->string_position]) &&
           i < sconfig->current_width) {
      buffer[i] = sconfig->string[sconfig->string_position];
      i++;
      sconfig->string_position++;
    }
  } else if (s21_strncmp(condition, "octal", 5) == 0) {
    while ((sconfig->string[sconfig->string_position] <= '7' &&
            sconfig->string[sconfig->string_position] >= '0') &&
           i < sconfig->current_width) {
      buffer[i] = sconfig->string[sconfig->string_position];
      i++;
      sconfig->string_position++;
    }
  } else if (s21_strncmp(condition, "decimal", 7) == 0) {
    while (s21_is_digit(sconfig->string[sconfig->string_position]) &&
           i < sconfig->current_width) {
      buffer[i] = sconfig->string[sconfig->string_position];
      i++;
      sconfig->string_position++;
    }
  } else if (s21_strncmp(condition, "science", 7) == 0) {
    while (s21_is_scientific(sconfig->string[sconfig->string_position]) &&
           i < sconfig->current_width) {
      buffer[i] = sconfig->string[sconfig->string_position];
      i++;
      sconfig->string_position++;
    }
  } else if (s21_strncmp(condition, "string", 6) == 0) {
    while (s21_is_whitespace(sconfig->string[sconfig->string_position]) &&
           sconfig->string[sconfig->string_position] != '\0')
      sconfig->string_position++;
    while (sconfig->string[sconfig->string_position] != '\0' &&
           !s21_is_whitespace(sconfig->string[sconfig->string_position]) &&
           i < sconfig->current_width) {
      buffer[i] = sconfig->string[sconfig->string_position];
      i++;
      sconfig->string_position++;
    }
  }
  buffer[i] = '\0';
  return buffer;
}
// check 0 width
