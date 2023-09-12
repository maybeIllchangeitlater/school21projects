#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  s21::Model model;
  s21::Controller controller(model);
  QApplication a(argc, argv);
  MainWindow w(controller);
  w.show();
  return a.exec();
}
