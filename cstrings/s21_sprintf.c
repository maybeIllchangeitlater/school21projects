#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list va;
  va_start(va, format);
  options config = {0};
  config_printf(str, format, &config, va);
  str[config.written_char] = '\0';
  va_end(va);
  return config.written_char;
}

void config_printf(char *buffer, const char *format, options *config,
                   va_list va) {
  int counter;
  while (*format) {
    if (*format != '%') {
      write_char_in_buffer(buffer, format, config);
      format++;
      continue;
    } else {
      format++;
    }
    do {
      counter = 0;
      flags_congig(&format, &counter, config);
    } while (counter != 0);
    config_width_field(&format, va, config);
    config_precision_field(&format, va, config);
    config_length_field(&format, config);
    switch (*format) {
      case 'd':
      case 'i':
      case 'u':
      case 'x':
      case 'X':
      case 'o': {
        config_decimal(&format, config);
        convert_to_integer(&format, buffer, va, config);
        break;
      }
      case 'f':
        config->flag_f += 1;
        s21_ftoa(
            buffer,
            config->long_double ? va_arg(va, long double) : va_arg(va, double),
            config);
        format++;
        break;
      case 'e':
      case 'E':
        config->flag_f += 1;
        if (*format == 'E') config->flag_upper_case = 1;
        s21_etoa(
            buffer,
            config->long_double ? va_arg(va, long double) : va_arg(va, double),
            config);
        format++;
        break;
      case 'g':
      case 'G':
        if (*format == 'G') config->flag_upper_case = 1;
        s21_gtoa(
            buffer,
            config->long_double ? va_arg(va, long double) : va_arg(va, double),
            config);
        format++;
        break;
      case 'c': {
        char input_char = (char)va_arg(va, int);
        config_c(buffer, input_char, config);
        format++;
        break;
      }
      case 's': {
        char *p = va_arg(va, char *);
        config_s(buffer, p, config);
        format++;
        break;
      }
      case 'p': {
        config->base = 16;
        config->flag_hash = 1;
        config->flag_plus = 0;
        ntoa_long(buffer, (unsigned long)va_arg(va, void *), 0, config);
        format++;
        break;
      }
      case '%': {
        buffer[config->written_char] = '%';
        config->written_char += 1;
        format++;
        break;
      }
      case 'n': {
        int *pointer_int = s21_NULL;
        pointer_int = va_arg(va, int *);
        if (pointer_int != s21_NULL) {
          *pointer_int = config->written_char;
        }
        format++;
        break;
      }
    }
  }
}

void s21_gtoa(char *buffer, long double value, options *config) {
  if (!config->flag_precision) {
    config->flag_precision += 1;
    config->precision = 6;
  }

  char *g_reversed_buffer =
      (char *)malloc((config->precision + 16) * sizeof(char));

  int negative = 0;
  if (value < 0) {
    value = -value;
    negative += 1;
  }

  long double border_number = pow(10, config->precision);

  int expval = 0;
  if (value > 1e-15) {
    expval = (int)floorl(log10l(value));
    if (expval > (int)(config->precision)) {
      while (value >= border_number) {
        value /= 10;
      }
    } else {
      while (value < border_number) {
        value *= 10;
      }
    }
    if (value >= border_number) {
      value /= 10;
    }
  }

  value = roundl(value);
  unsigned long int_value = (unsigned long)value;

  unsigned int buffer_index = 0;

  if ((expval >= (int)(config->precision)) || (expval < -4)) {
    char exp_signum = '+';
    if (expval < 0) {
      expval = -expval;
      exp_signum = '-';
    }
    g_reversed_buffer[0] = (char)('0' + expval % 10);
    expval /= 10;
    g_reversed_buffer[1] = (char)('0' + expval % 10);
    expval /= 10;
    buffer_index = 2;
    if (expval) {
      g_reversed_buffer[buffer_index++] = (char)('0' + expval % 10);
    }
    g_reversed_buffer[buffer_index++] = exp_signum;
    if (config->flag_upper_case) {
      g_reversed_buffer[buffer_index++] = 'E';
    } else {
      g_reversed_buffer[buffer_index++] = 'e';
    }
    if (!config->flag_hash) {
      for (; !(int_value % 10); int_value /= 10)
        ;
    }
    int need_to_print = 0;
    while (int_value > 9) {
      g_reversed_buffer[buffer_index++] = (char)('0' + int_value % 10);
      int_value /= 10;
      need_to_print = 1;
    }
    if (need_to_print) {
      g_reversed_buffer[buffer_index++] = '.';
    }
    g_reversed_buffer[buffer_index++] = (char)('0' + int_value);
  } else {
    int need_to_print = 0;
    for (int i = 0; i < ((int)(config->precision) - 1 - expval); i++) {
      unsigned digit = int_value % 10;
      if (digit || config->flag_hash) {
        need_to_print = 1;
      }
      if (need_to_print) {
        g_reversed_buffer[buffer_index++] = (char)((int)digit + '0');
      }
      int_value /= 10;
    }
    if (need_to_print) {
      g_reversed_buffer[buffer_index++] = '.';
    }
    if (!int_value) {
      g_reversed_buffer[buffer_index++] = '0';
    }
    while (int_value) {
      unsigned digit = int_value % 10;
      g_reversed_buffer[buffer_index++] = (char)((int)digit + '0');
      int_value /= 10;
    }
  }

  if (negative) {
    g_reversed_buffer[buffer_index++] = '-';
  } else if (config->flag_plus) {
    g_reversed_buffer[buffer_index++] =
        '+';  // ignore the space if the '+' exists
  } else if (config->flag_space) {
    g_reversed_buffer[buffer_index++] = ' ';
  }

  reverse(buffer, g_reversed_buffer, buffer_index, config);

  free(g_reversed_buffer);
}

void flags_congig(const char **format, int *counter, options *config) {
  switch (**format) {
    case '0':
      config->flag_zeropad = 1;
      *format += 1;
      *counter += 1;
      break;
    case '-':
      config->flag_minus_left = 1;
      *format += 1;
      *counter += 1;
      break;
    case '+':
      config->flag_plus = 1;
      *format += 1;
      *counter += 1;
      break;
    case ' ':
      config->flag_space = 1;
      *format += 1;
      *counter += 1;
      break;
    case '#':
      config->flag_hash = 1;
      *format += 1;
      *counter += 1;
      break;
  }
}

void config_width_field(const char **format, va_list va, options *config) {
  if (is_digit(format)) {
    config->flag_width = s21_atoi(format);
  } else if (**format == '*') {
    int w = va_arg(va, int);
    if (w < 0) {
      config->flag_minus_left += 1;  // reverse padding
      config->flag_width = (unsigned int)-w;
    } else {
      config->flag_width = (unsigned int)w;
    }
    *format += 1;
  }
}

void config_precision_field(const char **format, va_list va, options *config) {
  if (**format == '.') {
    config->flag_precision = 1;  // if - this is add left_flag
    *format += 1;
    if (**format == '-') {  // test it
      config->flag_minus_left += 1;
      *format += 1;
    }
    if (is_digit(format)) {
      config->precision = s21_atoi(format);
    } else if (**format == '*') {
      int prec = (int)va_arg(va, int);
      if (prec > 0) {  // if 0?
        config->precision = prec;
      } else {
        config->precision = -prec;
        config->flag_minus_left += 1;
      }
      *format += 1;
    }
  }
}

void config_length_field(const char **format, options *config) {
  switch (**format) {
    case 'l':
      config->flag_long_int += 1;
      *format += 1;
      break;
    case 'h':
      config->flag_short += 1;
      *format += 1;
      break;
    case 'L':
      config->long_double += 1;
      *format += 1;
      break;
  }
}

void config_decimal(const char **format, options *config) {
  if (**format == 'x' || **format == 'X') {
    config->base = 16U;
  } else if (**format == 'o') {
    config->base = 8U;
  } else {
    config->base = 10U;
    config->flag_hash = 0;
    // no hash for dec format
  }
  // uppercase
  if (**format == 'X') {
    config->flag_upper_case = 1;
  }

  // no plus or space flag for u, x, X, o
  if ((**format != 'i') && (**format != 'd')) {
    config->flag_plus = 0;
    config->flag_space = 0;
  }

  // ignore '0' flag when precision is given
  if (config->flag_precision) {
    config->flag_zeropad = 0;
  }
}

void convert_to_integer(const char **format, char *buffer, va_list va,
                        options *config) {
  if ((**format == 'i') || (**format == 'd')) {
    // signed
    if (config->flag_long_int) {
      int negative = 0;
      long value_s = va_arg(va, long);
      unsigned long value;
      if (value_s >= 0) {
        value = (unsigned long)value_s;
      } else {
        value = (unsigned long)0 - value_s;
        negative = 1;
      }
      ntoa_long(buffer, value, negative, config);

    } else {
      int value =
          (config->flag_short) ? (short int)va_arg(va, int) : va_arg(va, int);
      ntoa_long(buffer, (unsigned int)(value > 0 ? value : 0 - value),
                value < 0, config);
    }
  } else {
    // unsigned
    if (config->flag_long_int) {
      ntoa_long(buffer, va_arg(va, unsigned long), 0, config);
    } else {
      unsigned int value = (config->flag_short)
                               ? (unsigned short int)va_arg(va, unsigned int)
                               : va_arg(va, unsigned int);
      ntoa_long(buffer, value, 0, config);
    }
  }
  *format += 1;
}

void s21_ftoa(char *buffer, long double value, options *config) {
  unsigned int buf_size = 1024U;
  char buf[buf_size];
  unsigned int len = 0U;

  // test for negative
  int negative = 0;
  if (value < 0) {
    negative = 1;
    value = -value;
  }

  // set default precision, if not set explicitly установите точность по
  if (!config->flag_precision) {
    config->precision = 6;
  }

  long whole_part = (long)value;
  double tmp = (value - whole_part) * pow(10, config->precision);
  long frac = (long)round(tmp);

  // now do fractional part, as an unsigned number
  unsigned int count = config->precision;
  if (config->precision) {
    while (len < buf_size) {
      if (count > 0) {
        --count;
      }
      buf[len++] = (char)('0' + (frac % 10U));
      if (!(frac /= 10U)) {
        break;
      }
    }
    // add extra 0s
    while ((len < buf_size) && (count-- > 0U)) {
      buf[len++] = '0';
    }

    if (len < buf_size) {
      // add decimal
      buf[len++] = '.';
    }
  }

  // do whole part, number is reversed
  while (len < buf_size) {
    buf[len++] = (char)('0' + (whole_part % 10));
    if (!(whole_part /= 10)) {
      break;
    }
  }

  // pad leading zeros
  if (!(config->flag_minus_left) && (config->flag_precision)) {
    if (config->flag_width &&
        (negative || config->flag_plus || config->flag_space)) {
      config->flag_width--;
    }
    while ((len < config->flag_width) && (len < buf_size)) {
      buf[len++] = '0';
    }
  }

  if (len < buf_size) {
    if (negative) {
      buf[len++] = '-';
    } else if (config->flag_plus) {
      buf[len++] = '+';  // ignore the space if the '+' exists
    } else if (config->flag_space) {
      buf[len++] = ' ';
    }
  }

  reverse(buffer, buf, len, config);
}

void config_c(char *buffer, char input_char, options *config) {
  unsigned int len = 1U;
  // pre padding
  if (!(config->flag_minus_left)) {
    while (len++ < config->flag_width) {
      buffer[config->written_char] = ' ';
      config->written_char += 1;
    }
  }
  // char output
  buffer[config->written_char] = input_char;
  config->written_char += 1;
  // post padding
  if (config->flag_minus_left) {
    while (len++ < config->flag_width) {
      buffer[config->written_char] = ' ';
      config->written_char += 1;
    }
  }
}

unsigned int s21_strnlen(const char *str, unsigned int maxsize) {
  const char *s;
  for (s = str; *s && maxsize--; ++s)
    ;
  return (unsigned int)(s - str);
}

void config_s(char *buffer, char *p, options *config) {
  unsigned int l =
      s21_strnlen(p, config->precision ? config->precision : (unsigned int)-1);

  // pre padding
  if (config->flag_precision) {
    l = (l < config->precision ? l : config->precision);
  }
  if (!(config->flag_minus_left)) {
    while (l++ < config->flag_width) {
      buffer[config->written_char] = ' ';
      config->written_char += 1;
    }
  }
  // string output
  while ((*p != 0) && (!(config->flag_precision) || config->precision--)) {
    buffer[config->written_char] = *p++;
    config->written_char += 1;
  }
  // post padding
  if (config->flag_minus_left) {
    while (l++ < config->flag_width) {
      buffer[config->written_char] = ' ';
      config->written_char += 1;
    }
  }
}

// itoa for 'long' type
void ntoa_long(char *buffer, unsigned long value, int negative,
               options *config) {
  unsigned int buf_size = 1024U;
  char buf[buf_size];
  unsigned int len = 0U;

  // no hash for 0 values
  if (!value) {
    config->flag_hash = 0;
  }

  // write if precision != 0 and value is != 0
  if (!(config->flag_precision) || value) {
    do {
      const char digit = (char)(value % config->base);
      buf[len++] = digit < 10
                       ? ('0' + digit)
                       : (config->flag_upper_case ? 'A' : 'a') + digit - 10;
      value /= config->base;
    } while (value && (len < buf_size));
  }

  ntoa_format(buffer, buf, buf_size, len, negative, config);
}

void ntoa_format(char *buffer, char *buf, unsigned int buf_size,
                 unsigned int len, int negative, options *config) {
  if (!(config->flag_minus_left)) {
    if ((config->flag_width) && (config->flag_zeropad) &&
        (negative || (config->flag_plus || config->flag_space))) {
      config->flag_width -= 1;
    }
    while ((len < config->precision) && (len < buf_size)) {
      buf[len++] = '0';
    }
    while ((config->flag_zeropad) && (len < config->flag_width) &&
           (len < buf_size)) {
      buf[len++] = '0';
    }
  }

  // handle hash
  if (config->flag_hash) {
    if (!(config->flag_precision) && len &&
        ((len == config->precision) || (len == config->flag_width))) {
      len--;
      if (len && (config->base == 16U)) {
        len--;
      }
    }
    if ((config->base == 16U) && !(config->flag_upper_case) &&
        (len < buf_size)) {
      buf[len++] = 'x';
    } else if ((config->base == 16U) && (config->flag_upper_case) &&
               (len < buf_size)) {
      buf[len++] = 'X';
    }

    if (len < buf_size) {
      buf[len++] = '0';
    }
  }

  if (len < buf_size) {
    if (negative) {
      buf[len++] = '-';
    } else if (config->flag_plus) {
      buf[len++] = '+';  // ignore the space if the '+' exists
    } else if (config->flag_space) {
      buf[len++] = ' ';
    }
  }

  reverse(buffer, buf, len, config);
}

void reverse(char *buffer, char *buf, unsigned int len, options *config) {
  const unsigned int start_index = config->written_char;

  if (!(config->flag_minus_left) && !(config->flag_zeropad)) {
    for (; len < config->flag_width; len++) {
      buf[len] = ' ';
    }
  }

  if ((config->flag_f) && config->flag_zeropad && !(config->flag_minus_left)) {
    for (; len < config->flag_width; len++) {
      buf[len] = '0';
    }
  }

  buf[len] = '\0';

  while (len) {
    buffer[config->written_char] = buf[--len];
    config->written_char += 1;
  }

  if (config->flag_minus_left) {
    if (config->flag_width) {
      while (config->written_char - start_index < config->flag_width) {
        buffer[config->written_char++] = ' ';
      }
    } else {
      while (config->written_char - start_index < config->precision) {
        buffer[config->written_char++] = ' ';
      }
    }
  }
}

void write_char_in_buffer(char *buffer, const char *format, options *config) {
  buffer[config->written_char] = *format;
  config->written_char += 1;
}

int s21_atoi(const char **format) {
  int i = 0;
  do {
    i = i * 10U + (unsigned int)(*((*format)++) - '0');
  } while (is_digit(format));
  return i;
}

int is_digit(const char **format) {
  int boolean = 0;
  if ((**format >= '0') && (**format <= '9')) {
    boolean = 1;
  }
  return boolean;
}

void s21_etoa(char *buffer, long double value, options *config) {
  if (!config->flag_precision) {
    config->flag_precision += 1;
    config->precision = 6;
  }

  char *g_reversed_buffer =
      (char *)malloc((config->precision + 16) * sizeof(char));

  // determine the sign
  int negative = 0;
  if (value < 0) {
    value = -value;
    negative += 1;
  }

  long double border_number = 10 * pow(10, config->precision);

  int expval = 0;
  if (value > 1e-15) {
    expval = (int)floorl(log10l(value));
    if (expval > (int)(config->precision)) {
      while (value >= border_number) {
        value /= 10;
      }
    } else {
      while (value < border_number) {
        value *= 10;
      }
    }
    if (value >= border_number) {
      value /= 10;
    }
  }

  value = roundl(value);

  if (value >= border_number) {
    value /= 10;
  }
  value = roundl(value);

  unsigned long int_value = (unsigned long)value;

  unsigned int buffer_index = 0;

  char exp_signum = '+';
  if (expval < 0) {
    expval = -expval;
    exp_signum = '-';
  }
  g_reversed_buffer[0] = (char)('0' + expval % 10);
  expval /= 10;
  g_reversed_buffer[1] = (char)('0' + expval % 10);
  expval /= 10;
  buffer_index = 2;
  if (expval) {
    g_reversed_buffer[buffer_index++] = (char)('0' + expval % 10);
  }
  g_reversed_buffer[buffer_index++] = exp_signum;
  if (config->flag_upper_case) {
    g_reversed_buffer[buffer_index++] = 'E';
  } else {
    g_reversed_buffer[buffer_index++] = 'e';
  }
  if (int_value) {
    while (int_value > 9) {
      g_reversed_buffer[buffer_index++] = (char)('0' + int_value % 10);
      int_value /= 10;
    }
  } else {
    for (int i = 0; i < (int)(config->precision); i++) {
      g_reversed_buffer[buffer_index++] = '0';
    }
  }

  g_reversed_buffer[buffer_index++] = '.';
  g_reversed_buffer[buffer_index++] = (char)('0' + int_value);

  if (negative) {
    g_reversed_buffer[buffer_index++] = '-';
  } else if (config->flag_plus) {
    g_reversed_buffer[buffer_index++] = '+';
  } else if (config->flag_space) {
    g_reversed_buffer[buffer_index++] = ' ';
  }

  reverse(buffer, g_reversed_buffer, buffer_index, config);

  free(g_reversed_buffer);
}
