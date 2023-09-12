#include "s21_sscanf.h"
#include "s21_string.h"

stack *s21_push(stack *head, char f, int width, char length, int skip,
                int is_a_flag) {
  stack *newstack = malloc(sizeof(stack));
  newstack->next = head;
  newstack->width = width;
  newstack->length = length;
  newstack->skip = skip;
  newstack->flag = f;
  newstack->is_a_flag = is_a_flag;
  return newstack;
}

stack *s21_pop(stack *head) {
  stack *tmp = head->next;
  free(head);
  return tmp;
}

void s21_destroy(stack *head) {
  while (head != s21_NULL) {
    stack *tmp = head;
    head = head->next;
    free(tmp);
  }
}
