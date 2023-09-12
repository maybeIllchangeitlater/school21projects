#include "mainwindow.h"

#include <iostream>
#include <string>

#include "ui_mainwindow.h"

//#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->variable, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->PI, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->e, SIGNAL(clicked()), this, SLOT(digit_numbers()));

  connect(ui->sum, SIGNAL(clicked()), this, SLOT(ooperators_un_possible()));
  connect(ui->diff, SIGNAL(clicked()), this, SLOT(ooperators_un_possible()));

  connect(ui->mul, SIGNAL(clicked()), this, SLOT(ooperators()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(ooperators()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(ooperators()));

  connect(ui->cos, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(bracketable()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(bracketable()));
  // connect(ui->equal, SIGNAL(clicked()), this, SLOT(on_equal_clicked()));
  connect(ui->expression, SIGNAL(returnPressed()), this,
          SLOT(on_equal_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  if (!(ui->expression->text().right(1) >= '0' &&
        ui->expression->text().right(1) <= '9') &&
      ui->expression->text().right(1) != '(' &&
      ui->expression->text().size() != 0 &&
      (ui->expression->text().right(1) != '.') &&
      !(ui->expression->text().size() == 1 &&
        (ui->expression->text().right(1) == '+' ||
         ui->expression->text().right(1) == '-')))
    ui->expression->setText(ui->expression->text() + ' ');
  if (qobject_cast<QPushButton *>(sender())->text() ==
      QString::fromStdString("PI"))
    ui->expression->setText(ui->expression->text() + QString::number(M_PI));
  else if (qobject_cast<QPushButton *>(sender())->text() ==
           QString::fromStdString("e"))
    ui->expression->setText(ui->expression->text() + QString::number(M_E));
  else
    ui->expression->setText(ui->expression->text() +
                            qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::bracketable() {
  (ui->expression->text().isEmpty() || ui->expression->text().right(1) == '(')
      ? ui->expression->setText(ui->expression->text() +
                                qobject_cast<QPushButton *>(sender())->text() +
                                '(')
      : ui->expression->setText(ui->expression->text() + ' ' +
                                qobject_cast<QPushButton *>(sender())->text() +
                                '(');
}

void MainWindow::ooperators() {
  ui->expression->setText(ui->expression->text() + ' ' +
                          qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::ooperators_un_possible() {
  ui->expression->text().isEmpty()
      ? ui->expression->setText(ui->expression->text() +
                                qobject_cast<QPushButton *>(sender())->text())
      : ui->expression->setText(ui->expression->text() + ' ' +
                                qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::on_point_clicked() {
  ui->expression->setText(ui->expression->text() +
                          qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::on_factorial_clicked() {
  ui->expression->setText(ui->expression->text() +
                          qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::on_reset_clicked() { ui->expression->setText(""); }

void MainWindow::on_backspace_clicked() {
  ui->expression->setText(
      ui->expression->text().left(ui->expression->text().length() - 1));
  while (ui->expression->text().right(1) == ' ')
    ui->expression->setText(
        ui->expression->text().left(ui->expression->text().length() - 1));
}

void MainWindow::on_open_b_clicked() {
  ui->expression->setText(ui->expression->text() + ' ' +
                          qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::on_close_b_clicked() {
  ui->expression->setText(ui->expression->text() +
                          qobject_cast<QPushButton *>(sender())->text());
}

void MainWindow::on_CoW_clicked() {
  QString cow =
      "-------\n< hello >\n-------\n     ^__^\n      (oo)\\_______\n      "
      "(__)\\              )\\/\\\n             ||----w |\n             ||     "
      "     ||";
  QString cow_kill =
      "-------\n< goodbye >\n-------\n     ^__^\n      (XX)\\_______\n      "
      "(__)\\              )\\/\\\n       U      ||----w |\n                || "
      "        ||";
  ui->cow_window->toPlainText() == "" ||
          ui->cow_window->toPlainText() == cow_kill
      ? ui->cow_window->setText(cow)
      : ui->cow_window->setText(cow_kill);
}

void MainWindow::on_equal_clicked() {
  if (ui->expression->text().length() > 255 ||
      ui->expression->text().contains('x') ||
      ui->expression->text().contains('X'))
    ui->expression->setText("NOPE");
  else {
    std::string cpp_infix_array = ui->expression->text().toStdString();
    const char *infix_array = cpp_infix_array.c_str();
    char Cstring[255] = {0};
    solve(infix_array, Cstring);
    std::string Cppstring(Cstring);
    ui->expression->setText(QString::fromStdString(Cppstring));
  }
}

bool isDouble(QString s) {
  bool status = 1, comma = 0;
  for (QChar ch : s)
    if (!((ch >= '0' && ch <= '9') || ch == '.' || ch == '-')) {
      status = 0;
      if (ch == '.') comma ? (status = 0) : (comma = 1);
    }
  return status;
}

void MainWindow::on_Graph_clicked() {
  std::string cpp_infix_array = ui->expression->text().toStdString();
  const char *infix_array = cpp_infix_array.c_str();
  double x1 = !ui->minX->text().isEmpty() && isDouble(ui->minX->text())
                  ? ui->minX->text().toDouble()
                  : 0.0;
  double x2 = !ui->maxX->text().isEmpty() && isDouble(ui->maxX->text())
                  ? ui->maxX->text().toDouble()
                  : 0.0;
  double y1 = !ui->minY->text().isEmpty() && isDouble(ui->minY->text())
                  ? ui->minY->text().toDouble()
                  : 0.0;
  double y2 = !ui->maxY->text().isEmpty() && isDouble(ui->maxY->text())
                  ? ui->maxY->text().toDouble()
                  : 0.0;
  double rabbit = !ui->Step->text().isEmpty() && isDouble(ui->Step->text())
                      ? ui->Step->text().toDouble()
                      : 0.0;

  graphWindow = new AnotherWindow(infix_array, x1, x2, y1, y2, rabbit);
  connect(graphWindow, &AnotherWindow::firstWindow, this, &MainWindow::show);

  graphWindow->show();
  this->close();
}

void MainWindow::on_credit_clicked() {
  greditWindow = new CreditWindow();
  connect(greditWindow, &CreditWindow::firstWindow, this, &MainWindow::show);

  greditWindow->show();
  this->close();
}

void MainWindow::on_deposit_clicked() {
  depositWindow = new DepositCalc();
  connect(depositWindow, &DepositCalc::firstWindow, this, &MainWindow::show);

  depositWindow->show();
  this->close();
}
