#include "s21_to_curva.h"

void calc_deposit(Deposit* dep) {
  dep->res_deposit_amount = dep->deposit;
  dep->interest /= 100;
  dep->tax /= 100;
  for (int i = 0, j = i; i < dep->term; i += dep->pereodicity) {
    double c_interest = dep->capitalization
                            ? dep->res_deposit_amount * dep->interest
                            : dep->res_deposit_amount * dep->interest /12;
    dep->res_accuired_interest += c_interest;
    for (; j <= i; j++)
      dep->res_deposit_amount += dep->replenishment[j] - dep->withdrawal[j];
    dep->res_tax_amount += c_interest * dep->tax;
  }
  dep->res_deposit_amount += dep->res_accuired_interest - dep->res_tax_amount;
}