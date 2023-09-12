#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_to_curva.h"
#ifdef __cplusplus
}
#endif

#include <anotherwindow.h>
#include <creditwindow.h>
#include <depositcalc.h>
#include <qcustomplot.h>

#include <QMainWindow>
#include <QVector>

bool isDouble(QString s);

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void digit_numbers();

  void bracketable();

  void ooperators();

  void ooperators_un_possible();

  void on_point_clicked();

  void on_factorial_clicked();

  void on_reset_clicked();

  void on_backspace_clicked();

  void on_open_b_clicked();

  void on_close_b_clicked();

  void on_equal_clicked();

  void on_CoW_clicked();

  void on_Graph_clicked();

  void on_credit_clicked();

  void on_deposit_clicked();

 private:
  Ui::MainWindow *ui;
  AnotherWindow *graphWindow;
  CreditWindow *greditWindow;
  DepositCalc *depositWindow;
};
#endif  // MAINWINDOW_H
