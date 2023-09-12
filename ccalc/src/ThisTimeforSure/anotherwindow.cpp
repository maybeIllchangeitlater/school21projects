#include "anotherwindow.h"

#include "mainwindow.h"
#include "ui_anotherwindow.h"
//

AnotherWindow::AnotherWindow(const char *infix, double x1, double x2, double y1,
                             double y2, double rabbit, QWidget *parent)
    : QWidget(parent), ui(new Ui::AnotherWindow) {
  ui->setupUi(this);
  ui->ErrorWindow->setReadOnly(true);
  int i = 0;
  int N = (x2 - x1) / rabbit + 2;
  bool status = (rabbit > 0) && (x1 < x2) && (y1 < y2) && (x2 - x1 >= rabbit) &&
                N < 2000000 && (fabs(x2 - x1) <= 2000000);
  QVector<double> resx(N), resy(N);
  Stack *kurva = kurvanize(infix);
  if (kurva == NULL) {
    ui->ErrorWindow->setText("ERROR");
    status = 0;
  }
  std::string check(infix);
  double temp = 0.0;
  if (check.find('X') != -1 || check.find('x') != -1)
    kurva = push(kurva, 0, 'p');
  for (double X = x1; X <= x2 && status; X += rabbit) {
    if (kurva->oper == 'p') kurva->value = X;
    resx[i] = X;
    temp = calculate(kurva);
    resy[i] = temp < y1 || temp > y2 ? NAN : temp;
    i++;
  }
  destroy(kurva);
  if (status) {
    ui->AnotherWindow_2->clearGraphs();
    ui->AnotherWindow_2->addGraph();
    ui->AnotherWindow_2->graph(0)->setData(resx, resy);
    ui->AnotherWindow_2->xAxis->setRange(x1, x2);
    ui->AnotherWindow_2->yAxis->setRange(y1, y2);
    ui->AnotherWindow_2->replot();
  } else
    ui->ErrorWindow->setText("ERROR");
}

AnotherWindow::~AnotherWindow() { delete ui; }

void AnotherWindow::on_Close_clicked() {
  this->close();
  emit firstWindow();
}
