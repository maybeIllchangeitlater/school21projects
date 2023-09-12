#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMainWindow>
#include <QMovie>
#include <QProcess>
#include <QTimer>
#include <iostream>

#include "./gifmaker/gif_hash.h"
#include "./gifmaker/gif_lib.h"
#include "./gifmaker/gif_lib_private.h"
#include "./gifmaker/qgifglobal.h"
#include "./gifmaker/qgifimage.h"
#include "./gifmaker/qgifimage_p.h"
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_Browse_clicked();

  void closeEvent(QCloseEvent *event);

  void saveSettings();

  void loadSettings();

  void on_color_clicked();

  void on_color_2_clicked();

  void on_ScaleSlider_sliderMoved(int position);

  void on_line_thicc_sliderMoved(int position);

  void on_line_t_clicked();

  void on_close_line_wid_clicked();

  void translateBy();

  void rotateBy();

  void on_centerModel_clicked();

  void on_gif_clicked();

  void on_changePerspective_clicked();

  void makeScreenshot();

  void makeVidya();

  void on_showVertexes_clicked();

  void on_showVertexes_2_clicked();

  void displayLines();

  void on_color_3_clicked();

  void on_brokenLines_clicked();

  void on_vertex_t_clicked();

  void vertex_wid_clicked();

  void on_takeJpeg_clicked();

  void on_takeBmp_clicked();

  void VertexesToVec();

  void IndicesToVec();

  void OpenAndParseFile();

  void on_vertex_thicc_sliderMoved(int position);

 private:
  OpenGLWidget *glWidget;
  Ui::MainWindow *ui;
  QList<QImage> jiff;
  int imagecounter;
  int screenshotcounter;
  int maxface;
  QDir dir;
  QString filename;
  QColor color;
  QColor back_color;
  QColor vertex_color;
  bool showLines;
  bool smoothVertexes;
  bool vertexesShown;
  bool brokenEdges;
  bool orth;
  float minx = 0, miny = 0, minz = 0, maxx = 0, maxy = 0, maxz = 0;
  Gigachad bigstructarray = {0};
  float medianX, medianY, medianZ;
  std::vector<GLfloat> vertexPositions;
  std::vector<GLuint> indices;
  int lineW;
  int vertexW;
  QTimer timer;
};

#endif  // MAINWINDOW_H
