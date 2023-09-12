#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QWidget>
#include <vector>

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();

 signals:
  void firstWindow();

 private slots:
  void on_rep_add_clicked();

  void on_close_clicked();

  void on_with_add_clicked();

  void on_calc_clicked();

 private:
  Ui::DepositCalc *ui;
  std::vector<double> rep;
  std::vector<double> withdraw;
  int i_rep;
  int i_wit;
};

#endif  // DEPOSITCALC_H
