#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "widget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), glWidget(nullptr) {
  ui->setupUi(this);
  ui->ScaleSlider->setEnabled(false);
  ui->line_thicc->setVisible(false);
  ui->line_thicc->setEnabled(false);
  ui->vertex_thicc->setVisible(false);
  ui->vertex_thicc->setEnabled(false);
  ui->close_vertex_wid->setVisible(false);
  ui->close_vertex_wid->setEnabled(false);
  ui->close_line_wid->setVisible(false);
  ui->close_line_wid->setEnabled(false);
  vertexesShown = false;
  smoothVertexes = true;
  brokenEdges = false;
  showLines = true;
  orth = false;
  lineW = 1;
  vertexW = 8;
  color.setRgbF(1.0f, 1.0f, 1.0f, 1.0f);
  back_color.setRgbF(0.0f, 0.0f, 0.0f, 1.0f);
  vertex_color.setRgbF(1.0f, 0.0f, 1.0f, 1.0f);
  connect(ui->mDown, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->mUp, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->mLeft, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->mRight, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->mBackward, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->mForward, SIGNAL(clicked()), this, SLOT(translateBy()));
  connect(ui->rDown, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->rUp, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->rLeft, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->rRight, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->rzUp, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->rzDown, SIGNAL(clicked()), this, SLOT(rotateBy()));
  connect(ui->showLines, SIGNAL(clicked()), this, SLOT(displayLines()));
  connect(ui->vertex_t, SIGNAL(clicked()), this, SLOT(on_vertex_t_clicked()));
  connect(ui->close_vertex_wid, SIGNAL(clicked()), this,
          SLOT(vertex_wid_clicked()));  // here
  dir = QDir::homePath();
  loadSettings();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Browse_clicked() {
  maxface = 0;
  OpenAndParseFile();
  VertexesToVec();
  IndicesToVec();
  destroy_gigachads(&bigstructarray);
  if (maxface > vertexPositions.size() / 3) {
    std::cout << maxface << std::endl << vertexPositions.size();
    return;
  }
  /*----------------------------------------------------------------------------------------------------------------------*/
  if (glWidget) {
    ui->ViewerLayout->removeWidget(glWidget);
    ui->model_name->setText("");
    delete glWidget;
  }
  glWidget = new OpenGLWidget(vertexPositions, indices, color, back_color,
                              vertex_color, medianX, medianY, medianZ, lineW,
                              minx, maxx, miny, maxy, minz, maxz,
                              smoothVertexes, vertexesShown, brokenEdges, orth,
                              showLines, vertexW, this);
  ui->ViewerLayout->addWidget(glWidget);
  ui->model_name->setText(
      filename.mid(filename.lastIndexOf("/") + 1).chopped(4) + "\n" +
      "Vertexes: " + QString::number(vertexPositions.size() / 3) +
      " Edges: " + QString::number(indices.size() / 2));
}

void MainWindow::closeEvent(QCloseEvent *event) {
  saveSettings();
  event->accept();
}

void MainWindow::saveSettings() {
  QJsonObject settings;
  settings["color_r"] = color.red();
  settings["color_g"] = color.green();
  settings["color_b"] = color.blue();
  settings["color_a"] = color.alpha();
  settings["back_color_r"] = back_color.red();
  settings["back_color_g"] = back_color.green();
  settings["back_color_b"] = back_color.blue();
  settings["back_color_a"] = back_color.alpha();
  settings["vertex_color_r"] = vertex_color.red();
  settings["vertex_color_g"] = vertex_color.green();
  settings["vertex_color_b"] = vertex_color.blue();
  settings["vertex_color_a"] = vertex_color.alpha();
  settings["lineW"] = lineW;
  settings["smoothVertexes"] = smoothVertexes;
  settings["vertexesShown"] = vertexesShown;
  settings["brokenEdges"] = brokenEdges;
  settings["orth"] = orth;
  settings["showLines"] = showLines;
  settings["vertexW"] = vertexW;

  QJsonDocument doc(settings);
  QFile file(dir.absolutePath() + "/Desktop/viewer/settings.json");
  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

void MainWindow::loadSettings() {
  QFile life(dir.absolutePath() + "/Desktop/viewer/settings.json");

  if (life.open(QIODevice::ReadOnly)) {
    QJsonDocument jsonchik = QJsonDocument::fromJson(life.readAll());
    QJsonObject settings = jsonchik.object();
    color.setRed(settings.value("color_r").toInt());
    color.setGreen(settings.value("color_g").toInt());
    color.setBlue(settings.value("color_b").toInt());
    color.setAlpha(settings.value("color_a").toInt());
    back_color.setRed(settings.value("back_color_r").toInt());
    back_color.setGreen(settings.value("back_color_g").toInt());
    back_color.setBlue(settings.value("back_color_b").toInt());
    back_color.setAlpha(settings.value("back_color_a").toInt());
    vertex_color.setRed(settings.value("vertex_color_r").toInt());
    vertex_color.setGreen(settings.value("vertex_color_g").toInt());
    vertex_color.setBlue(settings.value("vertex_color_b").toInt());
    vertex_color.setAlpha(settings.value("vertex_color_a").toInt());
    lineW = settings.value("lineW").toInt();
    vertexW = settings.value("vertexW").toInt();
    smoothVertexes = settings.value("smoothVertexes").toBool();
    vertexesShown = settings.value("vertexesShown").toBool();
    brokenEdges = settings.value("brokenEdges").toBool();
    orth = settings.value("orth").toBool();
    showLines = settings.value("showLines").toBool();
    life.close();
  }
}

void MainWindow::VertexesToVec() {
  int j = 0;
  for (int i = 0; i < bigstructarray.numVertices; i++) {
    vertexPositions.push_back(bigstructarray.vertices[i]);
    if (j == 0) {
      if (minx > bigstructarray.vertices[i])
        minx = bigstructarray.vertices[i];
      else if (maxx < bigstructarray.vertices[i])
        maxx = bigstructarray.vertices[i];
    } else if (j == 1) {
      if (miny > bigstructarray.vertices[i])
        miny = bigstructarray.vertices[i];
      else if (maxy < bigstructarray.vertices[i])
        maxy = bigstructarray.vertices[i];
    } else {
      if (minz > bigstructarray.vertices[i])
        minz = bigstructarray.vertices[i];
      else if (maxz < bigstructarray.vertices[i])
        maxz = bigstructarray.vertices[i];
    }
    j += j < 2 ? 1 : -2;
  }
  medianX = (minx + maxx) / 2;
  medianY = (miny + maxy) / 2;
  medianZ = (minz + maxz) / 2;
}

void MainWindow::IndicesToVec() {
  for (int i = 0; i < bigstructarray.numFaces; i++)
    for (int j = 0; j < bigstructarray.faces[i].vertexes_per_faceline; j++) {
      indices.push_back(bigstructarray.faces[i].vertex_index[j] - 1);
      if (maxface < (bigstructarray.faces[i].vertex_index[j] - 1))
        maxface = bigstructarray.faces[i].vertex_index[j] - 1;
    }
}

void MainWindow::OpenAndParseFile() {
  filename = QFileDialog::getOpenFileName(
      this, "Open File", dir.absolutePath() + "/Desktop/viewer/models/",
      "obj files (*.obj)");
  if (!filename.isEmpty()) {
    ui->ScaleSlider->setSliderPosition(100);
    ui->ScaleSlider->setEnabled(true);
    std::string filee = filename.toStdString();
    const char *file = filee.data();
    parseObjFile(file, &bigstructarray);
    if (!indices.empty()) {
      indices.clear();
      vertexPositions.clear();
    }
  }
}

void MainWindow::on_color_clicked() {
  QColorDialog colorDialog(this);
  color = colorDialog.getColor(Qt::white, this);
  if (!color.isValid()) color = QColorConstants::White;
  if (glWidget) glWidget->setEdgesColorAndUpdate(color);
}

void MainWindow::on_color_2_clicked() {
  QColorDialog colorDialog(this);
  back_color = colorDialog.getColor(Qt::white, this);
  if (!back_color.isValid()) back_color = QColorConstants::Black;
  if (glWidget) glWidget->setBackgroundColorAndUpdate(back_color);
}

void MainWindow::on_color_3_clicked() {
  QColorDialog colorDialog(this);
  vertex_color = colorDialog.getColor(Qt::white, this);
  if (!vertex_color.isValid()) vertex_color = QColorConstants::Red;
  if (glWidget) glWidget->setVertexColorAndUpdate(vertex_color);
}

void MainWindow::on_ScaleSlider_sliderMoved(int position) {
  if (glWidget) {
    glWidget->scaleModel(position);
  }
}

void MainWindow::on_line_thicc_sliderMoved(int position) {
  lineW = position;
  if (glWidget) glWidget->scaleLines(position);
}

void MainWindow::on_vertex_thicc_sliderMoved(int position) {
  vertexW = position;
  if (glWidget) glWidget->scaleVertex(position);
}

void MainWindow::on_line_t_clicked() {
  ui->line_thicc->setVisible(true);
  ui->line_thicc->setEnabled(true);
  ui->close_line_wid->setVisible(true);
  ui->close_line_wid->setEnabled(true);
}

void MainWindow::on_vertex_t_clicked() {
  ui->vertex_thicc->setVisible(true);
  ui->vertex_thicc->setEnabled(true);
  ui->close_vertex_wid->setVisible(true);
  ui->close_vertex_wid->setEnabled(true);
}

void MainWindow::vertex_wid_clicked() {
  ui->vertex_thicc->setVisible(false);
  ui->vertex_thicc->setEnabled(false);
  ui->close_vertex_wid->setVisible(false);
  ui->close_vertex_wid->setEnabled(false);
}

void MainWindow::on_close_line_wid_clicked() {
  ui->line_thicc->setVisible(false);
  ui->line_thicc->setEnabled(false);
  ui->close_line_wid->setVisible(false);
  ui->close_line_wid->setEnabled(false);
}

void MainWindow::translateBy() {
  if (glWidget) {
    glWidget->translateModel(
        qobject_cast<QPushButton *>(sender())->text() == "↑"   ? 0
        : qobject_cast<QPushButton *>(sender())->text() == "→" ? 1
        : qobject_cast<QPushButton *>(sender())->text() == "↓" ? 2
        : qobject_cast<QPushButton *>(sender())->text() == "←" ? 3
        : qobject_cast<QPushButton *>(sender())->text() == "⇧" ? 4
                                                               : 5,
        ui->translateBy->text().toFloat());
  }
}

void MainWindow::rotateBy() {
  if (glWidget) {
    glWidget->rotateModel(
        qobject_cast<QPushButton *>(sender())->text() == "⇡"   ? 0
        : qobject_cast<QPushButton *>(sender())->text() == "⇢" ? 1
        : qobject_cast<QPushButton *>(sender())->text() == "⇣" ? 2
        : qobject_cast<QPushButton *>(sender())->text() == "⇢" ? 3
        : qobject_cast<QPushButton *>(sender())->text() == "↖" ? 4
                                                               : 5,
        ui->rotateBy->text().toFloat());
  }
}

void MainWindow::on_centerModel_clicked() {
  if (glWidget) {
    glWidget->ceterModel();
  }
}

void MainWindow::on_gif_clicked() {
  if (glWidget) {
    imagecounter = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(makeScreenshot()));
    timer.start(100);
  }
}

void MainWindow::on_takeJpeg_clicked() {
  if (glWidget) {
    imagecounter = -1;
    makeScreenshot();
  }
}

void MainWindow::on_takeBmp_clicked() {
  if (glWidget) {
    imagecounter = -2;
    makeScreenshot();
  }
}

void MainWindow::on_changePerspective_clicked() {
  if (glWidget) {
    glWidget->changePerspective();
  }
  orth = !orth;
}

void MainWindow::makeScreenshot() {
  QPixmap pixmap = glWidget->grab();
  QImage image = pixmap.toImage();
  jiff.append(
      image.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  imagecounter++;
  if (imagecounter >= 50) {
    timer.stop();
    makeVidya();
  } else if (imagecounter == 0 || imagecounter == -1) {
    image.save(dir.absolutePath() + "/Desktop/viewer/screenshot_" +
               QString::number(screenshotcounter++) +
               (imagecounter == 0 ? ".jpeg" : ".bmp"));
    imagecounter = 0;
  }
}

void MainWindow::makeVidya() {
  QGifImage *gifim = new QGifImage();
  gifim->setDefaultDelay(100);
  for (const QImage &img : jiff) {
    gifim->addFrame(img);
  }
  gifim->save(dir.absolutePath() + "/Desktop/viewer/output.gif");
  delete gifim;
  imagecounter = 0;
  jiff.clear();
}

void MainWindow::on_showVertexes_clicked() {
  if (glWidget) glWidget->showVert();
  vertexesShown = !vertexesShown;
}

void MainWindow::on_showVertexes_2_clicked() {
  if (glWidget) glWidget->changeVertDisplay();
  smoothVertexes = !smoothVertexes;
}

void MainWindow::on_brokenLines_clicked() {
  if (glWidget) glWidget->changeEdgeDisplay();
  brokenEdges = !brokenEdges;
}

void MainWindow::displayLines() {
  if (glWidget) glWidget->disLines();
  showLines = !showLines;
}
