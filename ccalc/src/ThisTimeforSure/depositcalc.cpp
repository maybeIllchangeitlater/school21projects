#include "depositcalc.h"

#include "mainwindow.h"
#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositCalc), i_rep(0), i_wit(0) {
  ui->setupUi(this);
  rep.resize(30);
  withdraw.resize(30);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_rep_add_clicked() {
  if (isDouble(ui->replenishment_in->text()) ||
      ui->replenishment_in->text().isEmpty()) {
    if (ui->replenishment_in->text().isEmpty())
      rep[i_rep++] = 0.0;
    else
      rep[i_rep++] = ui->replenishment_in->text().toDouble();
    ui->replenishment_counter->setText(QString::number(i_rep + 1));
  } else
    ui->replenishment_in->setText("ERROR");
}

void DepositCalc::on_with_add_clicked() {
  if (isDouble(ui->withdrawal_in->text()) ||
      ui->withdrawal_in->text().isEmpty()) {
    if (ui->withdrawal_in->text().isEmpty())
      withdraw[i_wit++] = 0.0;
    else
      withdraw[i_wit++] = ui->withdrawal_in->text().toDouble();
    ui->withdrawal_counter->setText(QString::number(i_wit + 1));
  } else
    ui->withdrawal_in->setText("ERROR");
}

void DepositCalc::on_close_clicked() {
  this->close();
  emit firstWindow();
}

void DepositCalc::on_calc_clicked() {
  if (isDouble(ui->interest_in->text()) && isDouble(ui->deposit_in->text()) &&
      isDouble(ui->deposit_term_in->text()) && isDouble(ui->tax_in->text()) &&
      isDouble(ui->deposit_term_in->text()) &&
      isDouble(ui->pereodicity_in->text()) &&
      (ui->capitalization_in->text().isEmpty() ||
       isDouble(ui->capitalization_in->text()))) {
    rep.resize(ui->deposit_term_in->text().toInt());
    withdraw.resize(ui->deposit_term_in->text().toInt());
    Deposit kmp = {0};
    kmp.capitalization = ui->capitalization_in->text().isEmpty()
                             ? 0
                             : ui->capitalization_in->text().toInt();
    kmp.interest = ui->interest_in->text().toDouble();
    kmp.deposit = ui->deposit_in->text().toDouble();
    kmp.term = ui->deposit_term_in->text().toInt();
    kmp.pereodicity = ui->pereodicity_in->text().toInt();
    kmp.tax = ui->tax_in->text().toDouble();
    kmp.replenishment = rep.data();
    kmp.withdrawal = withdraw.data();
    calc_deposit(&kmp);
    ui->aquired_interest->setText(QString::number(kmp.res_accuired_interest));
    ui->tax_amount->setText(QString::number(kmp.res_tax_amount));
    ui->deposit_amount->setText(QString::number(kmp.res_deposit_amount));
  } else {
    ui->aquired_interest->setText("PLS");
    ui->tax_amount->setText("STOP");
    ui->deposit_amount->setText("IT");
  }
}
