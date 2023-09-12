#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(const s21::Controller& controller, QWidget* parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);
  connect(ui->rep, SIGNAL(clicked()), this, SLOT(ReplenishBalance()));
  connect(ui->with, SIGNAL(clicked()), this, SLOT(WithdrawBalance()));
  connect(ui->calc, SIGNAL(clicked()), this, SLOT(CalcDeposit()));
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::ReplenishBalance() {
  replenish_.push_back(ui->replenish->text().toDouble());
}

void DepositWindow::WithdrawBalance() {
  withdrawl_.push_back(ui->withdraw->text().toDouble());
}

void DepositWindow::CalcDeposit() {
  double deposit_info[]{ui->amount->text().toDouble(),
                        ui->term->text().toDouble(),
                        ui->interest->text().toDouble(),
                        ui->tax->text().toDouble(),
                        ui->pereodicity->text().toDouble(),
                        ui->capitalization->text().toDouble(),
                        0.0,
                        0.0,
                        0.0};
  replenish_.resize(deposit_info[1]);
  withdrawl_.resize(deposit_info[1]);
  double* deposits[]{deposit_info, replenish_.data(), withdrawl_.data()};
  std::unique_ptr<std::byte[]> deposit_settings =
      std::make_unique<std::byte[]>(3 * sizeof(double*));
  std::memcpy(deposit_settings.get(), deposits, 3 * sizeof(double*));
  controller_.DepositCalc(deposit_settings);
  ui->a_amount->setText(QString::number(deposits[0][8]));
  ui->a_interst->setText(QString::number(deposits[0][6]));
  ui->a_tax->setText(QString::number(deposits[0][7]));
}

void DepositWindow::showEvent(QShowEvent* event) {
  ui->a_amount->setText("");
  ui->a_interst->setText("");
  ui->a_tax->setText("");
  ui->amount->setText("");
  ui->term->setText("");
  ui->interest->setText("");
  ui->tax->setText("");
  ui->pereodicity->setText("");
  ui->capitalization->setText("");
}
