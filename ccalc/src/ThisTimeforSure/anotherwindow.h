#ifndef ANOTHERWINDOW_H
#define ANOTHERWINDOW_H

#include <QVector>
#include <QWidget>

namespace Ui {
class AnotherWindow;
}

class AnotherWindow : public QWidget {
  Q_OBJECT

 public:
  explicit AnotherWindow(const char *infix = "ERROR", double x1 = 0.0,
                         double x2 = 0.0, double y1 = 0.0, double y2 = 0.0,
                         double rabbit = 0.0, QWidget *parent = 0);
  ~AnotherWindow();

 signals:
  void firstWindow();

 private slots:

  void on_Close_clicked();

 private:
  Ui::AnotherWindow *ui;
};

#endif  // ANOTHERWINDOW_H
