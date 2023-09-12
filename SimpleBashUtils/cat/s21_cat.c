#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    options config = {0};
    if (checkflags(argc, argv, &config)) {
      for (int x = config.indexoffirstfile; x < argc; x++) {
        FILE *file = fopen(argv[x], "r");
        if (file != NULL) {
          printdata(file, &config);
          fclose(file);
          config.linecounter = 0;
        } else
          fprintf(stderr, ERROR_1, argv[x]);
      }
    }
  }
  return 0;
}

void flag_v(char symb, options *config) {
  if (config->v) {
    if (symb < -96) {
      printf("M-^%c", symb + 192);
      config->do_we_print = 0;
    } else if (symb < 0) {
      printf("M-%c", symb + 128);
      config->do_we_print = 0;
    } else if (symb < 32 && symb != 9 && symb != 10) {
      printf("^%c", symb + 64);
      config->do_we_print = 0;
    } else if (symb == 127) {
      printf("^?");
      config->do_we_print = 0;
    }
  }
}

void flag_s(FILE *file, char symb, options *config) {
  char newsymb = symb;
  if (config->s && symb == '\n' && config->previous_was_eol) {
    while ((newsymb = getc(file)) != EOF && newsymb == '\n')
      ;
    if (newsymb == EOF) return;
    fseek(file, -sizeof(char), SEEK_CUR);
  }
}

void flag_b(char symb, options *config) {
  if (symb == '\n' && config->next_line_is_empty) return;
  if ((config->previous_was_eol && symb != '\n') ||
      (config->linecounter == 0 && symb != '\n')) {
    config->linecounter++;
    printf("%6d\t", config->linecounter);
    config->previous_was_eol = 0;
  }
}

void flag_n(options *config) {
  if (config->n) {
    if (config->linecounter == 0 || config->previous_was_eol) {
      config->linecounter++;
      printf("%6d\t", config->linecounter);
    }
  }
}

void check_next_symbol(FILE *file, char ch, options *config) {
  char nextch = getc(file);
  if (nextch == EOF) {
    if (ch == '\n') {
      return;
    }
  } else {
    if (nextch == '\n' && ch == '\n') {
      config->next_line_is_empty = 1;
    } else {
      config->next_line_is_empty = 0;
    }
    fseek(file, -sizeof(char), SEEK_CUR);
  }
}

void flag_t(char symb, options *config) {
  if (config->t && (symb == '\t')) {
    printf("^I");
    config->do_we_print = 0;
  }
}

int checkflags(int argc, char **argv, options *config) {
  optind = 1;
  int opt, status = 1;
  const struct option long_options[] = {{"number-nonblank", 0, &config->b, 1},
                                        {"number", 0, &config->n, 1},
                                        {"squeeze-blank", 0, &config->s, 1},
                                        {NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, "+sneEtTvb", long_options, NULL)) !=
         -1) {
    if (opt == 's')
      config->s = 1;
    else if (opt == 'n')
      config->n = 1;
    else if (opt == 'v')
      config->v = 1;
    else if (opt == 'e') {
      config->v = 1;
      config->e = 1;
    } else if (opt == 'E')
      config->e = 1;
    else if (opt == 't') {
      config->v = 1;
      config->t = 1;
    } else if (opt == 'T')
      config->t = 1;
    else if (opt == 'b')
      config->b = 1;
    else if (opt == '?') {
      fprintf(stderr, ERROR_2, opt);
      status = 0;
      break;
    }
  }
  config->indexoffirstfile = optind;
  return status;
}

void printdata(FILE *file, options *config) {
  char c = getc(file);
  config->previous_was_eol = c == '\n' ? 1 : 0;
  while (c != EOF) {
    config->do_we_print = 1;
    flag_s(file, c, config);
    check_next_symbol(file, c, config);
    config->b ? flag_b(c, config) : flag_n(config);
    flag_t(c, config);
    flag_v(c, config);
    if (config->do_we_print)
      config->e &&c == '\n' ? printf("$%c", c) : printf("%c", c);
    config->previous_was_eol = c == '\n' ? 1 : 0;
    c = getc(file);
  }
}