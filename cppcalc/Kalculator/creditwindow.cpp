#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(const s21::Controller& controller, QWidget* parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  connect(ui->calcCredit, SIGNAL(clicked()), this, SLOT(CalcCred()));
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::showEvent(QShowEvent* event) {
  ui->credit->setText("");
  ui->monthly->setText("");
  ui->over->setText("");
  ui->rate->setText("");
  ui->term->setText("");
  ui->over->setText("");
  ui->total->setText("");
  ui->type->setText("");
}

void CreditWindow::CalcCred() {
  std::byte credit_info[7 * sizeof(double)];
  std::vector<double> credits{ui->credit->text().toDouble(),
                              ui->rate->text().toDouble(),
                              ui->term->text().toDouble(),
                              ui->type->text().toDouble(),
                              0.0,
                              0.0,
                              0.0};
  std::memcpy(credit_info, credits.data(), 7 * sizeof(double));
  controller_.CreditCalc(credit_info);
  std::memcpy(credits.data(), credit_info, 7 * sizeof(double));
  ui->monthly->setText(QString::number(credits[4]));
  ui->over->setText(QString::number(credits[5]));
  ui->total->setText(QString::number(credits[6]));
}
