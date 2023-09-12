#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(const s21::Controller& controller, QWidget* parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->num_10, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->point, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_1, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_2, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_3, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_4, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_5, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->oper_6, SIGNAL(clicked()), this, SLOT(MakeString()));
  connect(ui->func_1, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_2, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_3, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_4, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_5, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_6, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_7, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_8, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->func_9, SIGNAL(clicked()), this, SLOT(MakeStringAddsBracket()));
  connect(ui->backspace, SIGNAL(clicked()), this, SLOT(RemoveOne()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(RemoveAll()));
  connect(ui->equals, SIGNAL(clicked()), this, SLOT(Equals()));
  connect(ui->input_field, SIGNAL(returnPressed()), this, SLOT(Equals()));
  connect(ui->graph, SIGNAL(clicked()), this, SLOT(MakeGraph()));
  connect(ui->deposit, SIGNAL(clicked()), this, SLOT(Deposit()));
  connect(ui->credit, SIGNAL(clicked()), this, SLOT(Credit()));
}

MainWindow::~MainWindow() {
  delete credit_;
  delete deposit_;
  delete ui;
}

void MainWindow::MakeString() {
  ui->input_field->setText(ui->input_field->text() +
                           qobject_cast<QPushButton*>(sender())->text());
}

void MainWindow::MakeStringAddsBracket() {
  ui->input_field->setText(ui->input_field->text() +
                           qobject_cast<QPushButton*>(sender())->text() + '(');
}

void MainWindow::Equals() {
  size_t byte_array_size = ui->input_field->text().length();
  std::byte string_in_byte_array[byte_array_size + 10];
  StringToBites(byte_array_size, string_in_byte_array);
  controller_.Calculate(string_in_byte_array, byte_array_size);
  std::string aboba(reinterpret_cast<char*>(string_in_byte_array),
                    byte_array_size);
  ui->input_field->setText(QString::fromStdString(aboba));
}

void MainWindow::MakeGraph() {
  size_t byte_array_size = ui->input_field->text().length();
  std::byte string_in_byte_array[byte_array_size + 10];
  StringToBites(byte_array_size, string_in_byte_array);

  double graph_settings[] = {
      ui->mix->text().toDouble(), ui->max->text().toDouble(),
      ui->miy->text().toDouble(), ui->may->text().toDouble(),
      ui->step->text().toDouble()};

  std::byte graph_settings_to_byte_array[5 * sizeof(double)];
  std::memcpy(graph_settings_to_byte_array, graph_settings, 5 * sizeof(double));
  std::unique_ptr<std::byte[]> res;
  std::unique_ptr<std::byte[]> res_size;
  controller_.MakeGraph(string_in_byte_array, byte_array_size,
                        graph_settings_to_byte_array, res, res_size);
  VecsToGraphW(byte_array_size, res, res_size, graph_settings);
}

void MainWindow::Deposit() { deposit_->show(); }

void MainWindow::Credit() { credit_->show(); }

void MainWindow::StringToBites(size_t& byte_array_size,
                               std::byte* string_in_byte_array) {
  auto data1 = ui->input_field->text().toStdString();
  auto data = data1.c_str();
  std::memcpy(string_in_byte_array, data, byte_array_size);
}

void MainWindow::RemoveOne() {
  ui->input_field->setText(
      ui->input_field->text().left(ui->input_field->text().length() - 1));
}

void MainWindow::RemoveAll() { ui->input_field->setText(""); }

void MainWindow::VecsToGraphW(size_t& byte_array_size,
                              std::unique_ptr<std::byte[]>& res,
                              std::unique_ptr<std::byte[]>& res_size,
                              double* graph_settings) {
  if (res != nullptr) {
    std::vector<size_t> indexes(byte_array_size);
    std::memcpy(indexes.data(), res_size.get(),
                byte_array_size * sizeof(size_t));
    size_t xysize = indexes[indexes.size() - 1];
    QVector<double> q_ys(xysize);
    QVector<double> q_xs(xysize);
    std::memcpy(q_xs.data(), res.get(), xysize * sizeof(double));
    std::memcpy(q_ys.data(), res.get() + xysize * sizeof(double),
                xysize * sizeof(double));
    QVector<QVector<double>> qv_ys;
    QVector<QVector<double>> qv_xs;
    size_t to_start = 0, j = 0;
    for (size_t i = 0; i < xysize;) {
      i = indexes[j++];
      qv_ys.push_back(
          QVector<double>(q_ys.begin() + to_start, q_ys.begin() + i));
      qv_xs.push_back(
          QVector<double>(q_xs.begin() + to_start, q_xs.begin() + i));
      to_start = i;
    }
    GraphWIndow* graph = new GraphWIndow(qv_xs, qv_ys, graph_settings);
    graph->show();
  } else {
    ui->input_field->setText("ERROR");
  }
}
