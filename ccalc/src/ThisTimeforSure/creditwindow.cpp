#include "creditwindow.h"

#include "mainwindow.h"
#include "ui_creditwindow.h"
//

CreditWindow::CreditWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  ui->Monthly->setReadOnly(true);
  ui->Overpay->setReadOnly(true);
  ui->Total_payment->setReadOnly(true);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_exit_clicked() {
  this->close();
  emit firstWindow();
}

void CreditWindow::on_Cal_clicked() {
  Credit res = {0};
  isDouble(ui->total_credit->text()) && isDouble(ui->term->text()) &&
          isDouble(ui->percentage->text()) &&
          (ui->type->text() == '1' || ui->type->text() == '2')
      ? (gib_gredit(&res, ui->total_credit->text().toDouble(),
                    ui->term->text().toDouble(),
                    ui->percentage->text().toDouble(),
                    ui->type->text().toInt()),
         ui->Monthly->setText(QString::number(res.monthly_payment)),
         ui->Overpay->setText(QString::number(res.overpay)),
         ui->Total_payment->setText(QString::number(res.total_payment)))
      : (ui->Monthly->setText("NO"), ui->Overpay->setText("WAY"),
         ui->Total_payment->setText("BRUH"));
}
