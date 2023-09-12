#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QWidget>

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = 0);
  ~CreditWindow();

 signals:
  void firstWindow();

 private slots:

  void on_exit_clicked();
  void on_Cal_clicked();

 private:
  Ui::CreditWindow *ui;
};

#endif
