#include "graphwindow.h"

#include "ui_graphwindow.h"

GraphWIndow::GraphWIndow(const QVector<QVector<double>>& xs,
                         const QVector<QVector<double>>& ys,
                         double* graph_settings, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::GraphWIndow) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  ui->graphic->clearGraphs();
  ui->graphic->xAxis->setRange(graph_settings[0], graph_settings[1]);
  ui->graphic->yAxis->setRange(graph_settings[2], graph_settings[3]);
  size_t i = 0;
  auto iter2 = xs.begin();
  for (const auto& val : ys) {
    ui->graphic->addGraph();
    ui->graphic->graph(i++)->addData(*iter2++, val, true);
    ui->graphic->replot();
  }
}

GraphWIndow::~GraphWIndow() { delete ui; }
