#ifndef TO_CURVA_H
#define TO_CURVA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct valid {
  bool status;
  bool was_variable;
  bool was_oper;
  bool was_function;
  bool was_pm;
  bool was_bracket;
  bool is_func;
  bool is_trig;
  bool fmod;
  bool fmod_comma;
  char func;
  int bracket;
  int fmod_brackets;
} valid;

typedef struct Stack {
  double value;
  char oper;
  struct Stack *next;
} Stack;

typedef struct Credit {
  double monthly_payment;
  double total_payment;
  double overpay;
} Credit;

typedef struct Deposit {
  int capitalization;
  double deposit;
  int term;
  double interest;
  double tax;
  int pereodicity;
  double *replenishment;
  double *withdrawal;
  double res_accuired_interest;
  double res_tax_amount;
  double res_deposit_amount;
  // term is size for both arrays
} Deposit;

char *solve(const char *infix, char *Cstring);
Stack *kurvanize(const char *notKurva);
Stack *reverseKurvanize(Stack *opers, Stack *output, valid *check);
Stack *eat_theNumber(const char *temp, int *i, valid *check, Stack *output);
Stack *push_greaterPrecedenceToOutput(Stack *opers, Stack **output,
                                      char goes_in);
Stack *push_functionToStack(valid *check, Stack *opers);
int check_precedence(char ch);

double calculate(Stack *kurvaClone);

void gib_gredit(Credit *result, double total_gredit, double term,
                double integest_rate, int type);

void calc_deposit(Deposit *dep);

double factorial(long long int x);
int is_digit(char ch);

int check_startOfFunction(const char *temp, int i, valid *check);
int check_function(const char *temp, int *i, valid *check);
int parse_number(valid *check);
void parse_comma(valid *check);
int parse_oper(valid *check, char ope);
char parse_pm(const char *notKurva, valid *check, int *i);
Stack *parse_openBracket(Stack *opers, valid *check);
void parse_closedBracket(Stack **output, Stack **opers, valid *check);

Stack *push(Stack *head, double value, char oper);
Stack *pop(Stack *head);
void destroy(Stack *head);

#endif
