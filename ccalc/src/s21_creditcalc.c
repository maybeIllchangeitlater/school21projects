#include "s21_to_curva.h"

void gib_gredit(Credit* result, double total_gredit, double term,
                double integest_rate, int type) {
  integest_rate /= 100.0;
  float monthlyInterestRate = integest_rate / 12.0;

  if (type == 1) {
    result->monthly_payment = (total_gredit * monthlyInterestRate *
                               pow(1 + monthlyInterestRate, term)) /
                              (pow(1 + monthlyInterestRate, term) - 1);
    result->total_payment = result->monthly_payment * term;
    result->overpay = result->total_payment - total_gredit;
  } else {
    result->monthly_payment = total_gredit / term;
    result->total_payment = 0.0;
    for (int i = 0; i < term; i++) {
      double interest =
          (total_gredit - (i * result->monthly_payment)) * monthlyInterestRate;
      result->total_payment += result->monthly_payment + interest;
    }
    result->overpay = result->total_payment - total_gredit;
  }
}
