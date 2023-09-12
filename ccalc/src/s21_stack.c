#include "s21_to_curva.h"

Stack* push(Stack* head, double value, char oper) {
  Stack* newstack = calloc(1, sizeof(Stack));
  newstack->next = head;
  newstack->value = value;
  newstack->oper = oper;
  return newstack;
}

Stack* pop(Stack* head) {
  if (head != NULL) {
    Stack* tmp = head;
    head = head->next;
    free(tmp);
  }
  return head;
}

void destroy(Stack* head) {
  while (head != NULL) {
    Stack* tmp = head;
    head = head->next;
    free(tmp);
  }
}
