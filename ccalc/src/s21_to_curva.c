#include "s21_to_curva.h"

char *solve(const char *infix, char *Cstring) {
  Stack *kurva = kurvanize((const char *)infix);
  double res = 0.0;
  if (kurva == NULL)
    strcpy(Cstring, "ERROR");
  else {
    res = calculate(kurva);
    if (isnan(res))
      strcpy(Cstring, "NAN");
    else if (isinf(res))
      strcpy(Cstring, "INF");
    else if (-isinf(res))
      strcpy(Cstring, "-INF");
    else
      sprintf(Cstring, "%.7f", res);
    destroy(kurva);
  }
  return Cstring;
}

Stack *kurvanize(const char *notKurva) {
  Stack *opers = NULL, *output = NULL;
  valid check = {0};
  check.func = '1';
  for (int i = 0; i < strlen(notKurva) && !check.status; i++) {
    if (check.bracket < 0 || check.fmod_brackets < 0)
      check.status = 1;
    else if (check.is_func && !check_function(notKurva, &i, &check)) {
      opers = push_greaterPrecedenceToOutput(opers, &output, check.func);
      opers = push_functionToStack(&check, opers);
      opers = push(opers, 0, '(');
    } else if ((notKurva[i] == ' ') ||
               (check_startOfFunction(notKurva, i, &check)))
      ;
    else if (notKurva[i] == ',')
      parse_comma(&check);
    else if (is_digit(notKurva[i]) && !parse_number(&check)) {
      output = eat_theNumber(notKurva, &i, &check, output);
    } else if ((notKurva[i] == 'x' || notKurva[i] == 'X') &&
               !parse_number(&check)) {
      output = push(output, 0, 'X');
    } else if ((notKurva[i] == '*' || notKurva[i] == '/' ||
                notKurva[i] == '^') &&
               !parse_oper(&check, notKurva[i])) {
      opers = push_greaterPrecedenceToOutput(opers, &output, notKurva[i]);
      opers = push_functionToStack(&check, opers);
    } else if (notKurva[i] == '+' || notKurva[i] == '-') {
      char sign = parse_pm(notKurva, &check, &i);
      if (!(check.func == 'u' && sign == '+')) {
        opers = push_greaterPrecedenceToOutput(opers, &output, check.func),
        opers = push_functionToStack(&check, opers);
      }
    } else if (notKurva[i] == '!' && check.was_variable) {
      check.func = notKurva[i];
      opers = push_greaterPrecedenceToOutput(opers, &output, check.func);
      opers = push_functionToStack(&check, opers);
    } else if (notKurva[i] == '(' && !check.was_variable) {
      opers = parse_openBracket(opers, &check);
    } else if (notKurva[i] == ')' && check.was_variable) {
      parse_closedBracket(&output, &opers, &check);
    } else
      check.status = 1;
    if (check.fmod && check.fmod_comma && !check.fmod_brackets) {
      check.fmod = 0, check.fmod_comma = 0;
    }
  }
  Stack *reverseKurva = reverseKurvanize(opers, output, &check);
  return reverseKurva;
}

int is_digit(char ch) { return ((ch >= '0' && ch <= '9') || ch == '.'); }

void parse_comma(valid *check) {
  (check->was_variable && check->fmod && !check->fmod_comma)
      ? (check->was_variable = 0, check->fmod_comma = 1, check->was_oper = 1)
      : (check->status = 1);
}

int parse_number(valid *check) {
  check->was_variable
      ? (check->status = 1)
      : (check->was_variable = 1, check->was_pm = 0, check->was_oper = 0,
         check->was_function = 0, check->was_bracket = 0);
  return check->status;
}

int parse_oper(valid *check, char ope) {
  (check->was_oper || check->was_pm || check->was_function)
      ? (check->status = 1)
      : (check->was_oper = 1, check->was_variable = 0, check->was_pm = 0,
         check->was_bracket = 0, check->func = ope);
  return check->status;
}

char parse_pm(const char *notKurva, valid *check, int *i) {
  char sign = notKurva[*i];
  int j = *i;
  while ((*i + 1) < strlen(notKurva) &&
         (notKurva[*i + 1] == '+' || notKurva[*i + 1] == '-' ||
          notKurva[*i + 1] == ' ')) {
    if (notKurva[*i + 1] != ' ')
      sign = sign == '-'               ? notKurva[*i + 1] == '-' ? '+' : '-'
             : notKurva[*i + 1] == '-' ? '-'
                                       : '+';
    (*i)++;
  }
  (check->was_bracket || check->was_oper || j == 0) ? (check->func = 'u')
                                                    : (check->func = sign);
  check->was_pm = 1, check->was_variable = 0, check->was_function = 0,
  check->was_bracket = 0;
  return sign;
}

Stack *parse_openBracket(Stack *opers, valid *check) {
  opers = push(opers, 0, '(');
  check->bracket++, check->was_bracket = 1;
  if (check->fmod) check->fmod_brackets++;
  return opers;
}

void parse_closedBracket(Stack **output, Stack **opers, valid *check) {
  while ((*opers)->oper != '(') {
    *output = push(*output, (*opers)->value, (*opers)->oper);
    *opers = pop(*opers);
  }
  *opers = pop(*opers);
  check->bracket--;
  if (check->fmod) check->fmod_brackets--;
}

Stack *push_greaterPrecedenceToOutput(Stack *opers, Stack **output,
                                      char goes_in) {
  while (opers != NULL &&
         (check_precedence(goes_in) <= check_precedence(opers->oper) &&
          !(goes_in == '^' && opers->oper == '^'))) {
    *output = push(*output, 0, opers->oper);
    opers = pop(opers);
  }
  return opers;
}

int check_precedence(char ch) {
  int prec = 0;
  if (ch == 'u')
    prec = 5;
  else if (ch == '!')
    prec = 4;
  else if (ch == '^')
    prec = 3;
  else if (ch == 'C' || ch == 'S' || ch == 'T' || ch == 'c' || ch == 's' ||
           ch == 't' || ch == 'q' || ch == 'o' || ch == 'm' || ch == 'n')
    prec = 6;
  else if (ch == '*' || ch == '/')
    prec = 2;
  else if (ch == '+' || ch == '-')
    prec = 1;
  return prec;
}

Stack *push_functionToStack(valid *check, Stack *opers) {
  if (check->is_trig) {
    if (check->func == 'c' || check->func == 'C')
      opers = push(opers, 0, 'C');
    else if (check->func == 's' || check->func == 'S')
      opers = push(opers, 0, 'S');
    else if (check->func == 't' || check->func == 'T')
      opers = push(opers, 0, 'T');
  } else if (check->func == 'c' || check->func == 'C')
    opers = push(opers, 0, 'c');
  else if (check->func == 's' || check->func == 'S')
    opers = push(opers, 0, 's');
  else if (check->func == 't' || check->func == 'T')
    opers = push(opers, 0, 't');
  else if (check->func == 'q')
    opers = push(opers, 0, 'q');
  else if (check->func == 'm' || check->func == 'M')
    opers = push(opers, 0, 'm');
  else if (check->func == 'o')
    opers = push(opers, 0, 'o');
  else if (check->func == 'n')
    opers = push(opers, 0, 'n');
  else
    opers = push(opers, 0, check->func);
  check->is_trig = 0;
  return opers;
}

Stack *eat_theNumber(const char *notKurva, int *i, valid *check,
                     Stack *output) {
  bool was_point = 0;
  char *number = calloc(strlen(notKurva), sizeof(char));
  int j = 0;
  while (*i < strlen(notKurva) &&
         (is_digit(notKurva[*i]) || notKurva[*i] == '.')) {
    if (notKurva[*i] == '.') {
      if (was_point)
        check->status = 1;
      else
        was_point = 1;
    }
    number[j++] = notKurva[(*i)++];
  }
  (*i)--;
  number[j] = '\0';
  Stack *newhead = push(output, atof(number), 'f');
  free(number);
  return newhead;
}

Stack *reverseKurvanize(Stack *opers, Stack *output, valid *check) {
  Stack *reverseKurva = NULL;
  if (check->bracket || check->fmod || !check->was_variable) {
    check->status = 1;
  }
  if (check->status) {
    destroy(opers);
    destroy(output);
    return NULL;
  }
  while (opers != NULL && opers->oper != 'f') {
    output = push(output, opers->value, opers->oper);
    opers = pop(opers);
  }
  destroy(opers);
  while (output != NULL) {
    reverseKurva = push(reverseKurva, output->value, output->oper);
    output = pop(output);
  }
  destroy(output);
  return reverseKurva;
}

int check_startOfFunction(const char *notKurva, int i, valid *check) {
  int was_it = 0;
  if (notKurva[i] == 'A' || notKurva[i] == 'C' || notKurva[i] == 'S' ||
      notKurva[i] == 'T' || notKurva[i] == 'a' || notKurva[i] == 'c' ||
      notKurva[i] == 's' || notKurva[i] == 't' || notKurva[i] == 'm' ||
      notKurva[i] == 'M' || notKurva[i] == 'l' || notKurva[i] == 'L') {
    was_it = 1;
    (check->was_variable) ? (check->status = 1) : (check->is_func = 1);
    check->func = notKurva[i];
    check->was_oper = 0, check->was_pm = 0, check->was_variable = 0;
  }
  return was_it;
}

int check_function(const char *notKurva, int *i, valid *check) {
  if (check->func == 'A' || check->func == 'a') {
    check->func = notKurva[(*i)++];
    check->is_trig = 1;
  }
  if (check->func == 'C' || check->func == 'c') {
    (*i + 2) < strlen(notKurva) &&
            (notKurva[*i] == 'o' || notKurva[*i] == 'O') &&
            (notKurva[*i + 1] == 's' || notKurva[*i + 1] == 'S') &&
            notKurva[*i + 2] == '('
        ? (*i += 2, check->is_func = 0, check->bracket++)
        : (check->status = 1);
  } else if (check->func == 'S' || check->func == 's') {
    (*i + 2) < strlen(notKurva) &&
            (notKurva[*i] == 'i' || notKurva[*i] == 'I') &&
            (notKurva[*i + 1] == 'n' || notKurva[*i + 1] == 'N') &&
            notKurva[*i + 2] == '('
        ? (*i += 2, check->is_func = 0, check->bracket++)
    : (*i + 3) < strlen(notKurva) && !check->is_trig &&
            (notKurva[*i] == 'q' || notKurva[*i] == 'Q') &&
            (notKurva[*i + 1] == 'r' || notKurva[*i + 1] == 'R') &&
            (notKurva[*i + 2] == 't' || notKurva[*i + 2] == 'T') &&
            notKurva[*i + 3] == '('
        ? (*i += 3, check->is_func = 0, check->func = 'q', check->bracket++)
        : (check->status = 0);
  } else if (check->func == 't' || check->func == 'T') {
    (*i + 2) < strlen(notKurva) &&
            (notKurva[*i] == 'a' || notKurva[*i] == 'A') &&
            (notKurva[*i + 1] == 'n' || notKurva[*i + 1] == 'N') &&
            notKurva[*i + 2] == '('
        ? (*i += 2, check->is_func = 0, check->bracket++)
        : (check->status = 1);
  } else if ((check->func == 'M' || check->func == 'm') && !check->is_trig) {
    (*i + 2) < strlen(notKurva) &&
            (notKurva[*i] == 'o' || notKurva[*i] == 'O') &&
            (notKurva[*i + 1] == 'd' || notKurva[*i + 1] == 'D') &&
            notKurva[*i + 2] == '('
        ? (*i += 2, check->is_func = 0, check->bracket++, check->fmod = 1,
           check->fmod_brackets++)
        : (check->status = 1);
  } else if ((check->func == 'L' || check->func == 'l') && !check->is_trig)
    ((*i + 2) < strlen(notKurva) &&
     (notKurva[*i] == 'o' || notKurva[*i] == 'O') &&
     (notKurva[*i + 1] == 'g' || notKurva[*i + 1] == 'G') &&
     (notKurva[*i + 2] == '('))
        ? (*i += 2, check->is_func = 0, check->func = 'o', check->bracket++)
    : (*i + 1) < strlen(notKurva) &&
            (notKurva[*i] == 'N' || notKurva[*i] == 'n')
        ? (*i += 1, check->is_func = 0, check->func = 'n', check->bracket++)
        : (check->status = 1);
  else
    check->status = 1;
  if (!check->status) {
    check->was_function = 1, check->was_bracket = 1;
  }
  return check->status;
}
// pow is right associative, (doesnt go away with same prior)