#include "widget.h"

#include <iostream>

OpenGLWidget::OpenGLWidget(std::vector<float> vertexPositions,
                           std::vector<uint> indices, QColor color,
                           QColor back_color, QColor vertex_color,
                           float medianX, float medianY, float medianZ,
                           int lineWposition, float minX, float maxX,
                           float minY, float maxY, float minZ, float maxZ,
                           bool smoothV, bool vShown, bool bEdges, bool ort,
                           bool lShown, int vertexT, QWidget *parent)
    : QOpenGLWidget(parent),
      m_vertexPositions(vertexPositions),
      m_indices(indices),
      m_color(color),
      m_back_color(back_color),
      m_vertex_color(vertex_color),
      m_minX(minX),
      m_minY(minY),
      m_minZ(minZ),
      m_maxX(maxX),
      m_maxY(maxY),
      m_maxZ(maxZ),
      m_medianX(medianX),
      m_medianY(medianY),
      m_medianZ(medianZ),
      lineThickness(lineWposition),
      smoothVertexes(smoothV),
      vertexesShown(vShown),
      lineStrip(bEdges),
      ortho(ort),
      linesShown(lShown),
      vertexThickness(vertexT) {
  setMouseTracking(true);
  backgroundChanged = true;
  vertexRecolored = true;
  lineThicknessChanged = lineThickness == 1 ? false : true;
  vertexThicknessChanged = true;
  lastMousePos = QPoint(0, 0);
  lastRmousePos = QPoint(0, 0);
  scaleBy = 1.0f;
  translationZ = 0.0f;
  translationX = 0.0f;
  translationY = 0.0f;
  rotationAngleX = 0.0f;
  rotationAngleY = 0.0f;
  rotationAngleZ = 0.0f;
  scrollDelta = 0;
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::setEdgesColorAndUpdate(QColor t_color) {
  m_color = t_color;
  shaderProgram.bind();
  shaderProgram.setUniformValue("color", m_color);
  shaderProgram.release();
  update();
}

void OpenGLWidget::setBackgroundColorAndUpdate(QColor b_color) {
  backgroundChanged = m_back_color == b_color ? false : true;
  m_back_color = b_color;
  update();
}

void OpenGLWidget::setVertexColorAndUpdate(QColor v_color) {
  m_vertex_color = v_color;
  update();
}

void OpenGLWidget::scaleModel(int position) {
  scaleBy = static_cast<float>(position) / 100;
  update();
}

void OpenGLWidget::scaleLines(int scale) {
  lineThickness = scale;
  lineThicknessChanged = true;
  update();
}

void OpenGLWidget::scaleVertex(int position) {
  vertexThickness = position;
  vertexThicknessChanged = true;
  update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    QPoint delta = event->pos() - lastMousePos;
    rotationAngleX += delta.x();
    rotationAngleY += delta.y();
    update();
    lastMousePos = event->pos();
  } else if (event->buttons() & Qt::RightButton) {
    QPoint delta = event->pos() - lastRmousePos;
    translationX += delta.x() / 100.0f;
    translationY -= delta.y() / 100.0f;
    update();
    lastRmousePos = event->pos();
  }
}

void OpenGLWidget::translateModel(int direction, float amount) {
  if (direction == 0)
    translationY += amount;
  else if (direction == 1)
    translationX += amount;
  else if (direction == 2)
    translationY -= amount;
  else if (direction == 3)
    translationX -= amount;
  else if (direction == 4)
    translationZ -= amount;
  else if (direction == 5)
    translationZ += amount;
  update();
}

void OpenGLWidget::rotateModel(int direction, float amount) {
  if (direction == 0)
    rotationAngleY += amount;
  else if (direction == 1)
    rotationAngleX += amount;
  else if (direction == 2)
    rotationAngleY -= amount;
  else if (direction == 3)
    rotationAngleX -= amount;
  else if (direction == 4)
    rotationAngleZ -= amount;
  else if (direction == 5)
    rotationAngleZ += amount;
  update();
}

void OpenGLWidget::ceterModel() {
  translationZ = -m_medianZ * scaleBy;
  translationX = -m_medianX * scaleBy;
  translationY = -m_medianY * scaleBy;
  update();
}

void OpenGLWidget::changePerspective() {
  ortho = !ortho;

  resizeGL(OpenGLWidget::width(), OpenGLWidget::height());
}

void OpenGLWidget::showVert() {
  vertexesShown = !vertexesShown;
  update();
}

void OpenGLWidget::disLines() {
  linesShown = !linesShown;
  update();
}

void OpenGLWidget::changeVertDisplay() {
  smoothVertexes = !smoothVertexes;
  update();
}

void OpenGLWidget::changeEdgeDisplay() {
  lineStrip = !lineStrip;
  update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) lastMousePos = event->pos();
  if (event->button() == Qt::RightButton) lastRmousePos = event->pos();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
  scrollDelta = event->angleDelta().y();
  translationZ += static_cast<float>(scrollDelta) / 120.0f;
  update();
}

void OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(m_back_color.redF(), m_back_color.greenF(), m_back_color.blueF(),
               m_back_color.alphaF());
  glEnable(GL_DEPTH_TEST);
  /*----------------------------------------------------------------------------------------------------------------------*/
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                        vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        fragmentShaderSource);
  shaderProgram.link();
  shaderProgram.bind();
  /*----------------------------------------------------------------------------------------------------------------------*/
  shaderProgram.setUniformValue("color", m_color);
  /*----------------------------------------------------------------------------------------------------------------------*/
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertexPositions.size(),
               m_vertexPositions.data(), GL_STATIC_DRAW);
  glGenBuffers(1, &indexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(),
               m_indices.data(), GL_STATIC_DRAW);
  /*----------------------------------------------------------------------------------------------------------------------*/

  GLuint positionLocation = shaderProgram.attributeLocation("position");
  glEnableVertexAttribArray(positionLocation);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  shaderProgram.release();
  /*----------------------------------------------------------------------------------------------------------------------*/
}

void OpenGLWidget::resizeGL(int w, int h) {
  /*----------------------------------------------------------------------------------------------------------------------*/
  aspectRatio = static_cast<float>(w) / (h);
  glViewport(0, 0, w, h);
  projectionMatrix.setToIdentity();
  ortho ? projectionMatrix.ortho(m_minX < 0 ? m_minX * 2 : m_minX / 2,
                                 m_maxX > 0 ? m_maxX * 2 : m_maxX / 2,
                                 m_minY < 0 ? m_minY * 2 : m_minY / 2,
                                 m_maxY > 0 ? m_maxY * 2 : m_maxY / 2,
                                 m_minZ < 0 ? m_minZ * 2 : m_minZ / 2,
                                 m_maxZ > 0 ? m_maxZ * 2 : m_maxZ / 2)
        : projectionMatrix.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
  /*----------------------------------------------------------------------------------------------------------------------*/
}

void OpenGLWidget::paintGL() {
  /*----------------------------------------------------------------------------------------------------------------------*/
  if (backgroundChanged) {
    glClearColor(m_back_color.redF(), m_back_color.greenF(),
                 m_back_color.blueF(), m_back_color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    backgroundChanged = false;
  }
  shaderProgram.bind();
  shaderProgram.setUniformValue("dashed", false);
  shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
  modelViewMatrix.setToIdentity();
  modelViewMatrix.translate(translationX, translationY, -2.5 + translationZ);
  modelViewMatrix.scale(scaleBy);
  if (lineThicknessChanged) {
    glLineWidth(static_cast<float>(lineThickness));
    lineThicknessChanged = false;
  }
  if (vertexThicknessChanged) {
    glPointSize(vertexThickness);
    vertexThicknessChanged = false;
  }
  modelViewMatrix.rotate(rotationAngleY, 1.0, 0.0, 0.0f);
  modelViewMatrix.rotate(rotationAngleX, 0.0, 1.0, 0.0f);
  modelViewMatrix.rotate(rotationAngleZ, 0.0, 0.0, 1.0f);
  shaderProgram.setUniformValue("modelViewMatrix", modelViewMatrix);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  smoothVertexes ? glEnable(GL_POINT_SMOOTH) : glDisable(GL_POINT_SMOOTH);
  if (vertexesShown) {
    shaderProgram.setUniformValue("color", m_vertex_color);
    glDrawElements(GL_POINTS, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    shaderProgram.setUniformValue("color", m_color);
  }
  lineStrip ? shaderProgram.setUniformValue("dashed", true)
            : shaderProgram.setUniformValue("dashed", false);
  if (linesShown)
    glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
  shaderProgram.release();
  /*----------------------------------------------------------------------------------------------------------------------*/
}
