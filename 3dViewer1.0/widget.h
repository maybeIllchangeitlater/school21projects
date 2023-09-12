#ifndef WIDGET_H
#define WIDGET_H

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QVector3D>
#include <QWidget>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
#include "./parser/parser.h"
#ifdef __cplusplus
}
#endif

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  OpenGLWidget(std::vector<float> vertexPositions, std::vector<uint> indices,
               QColor color, QColor back_color, QColor vertex_color,
               float medianX, float medianY, float medianZ, int lineWposition,
               float minX, float maxX, float minY, float maxY, float minZ,
               float maxZ, bool smoothV, bool Vshown, bool bEdges, bool ort,
               bool lShown, int vertexT, QWidget* parent = nullptr);
  ~OpenGLWidget();
  void setEdgesColorAndUpdate(QColor t_color);
  void setBackgroundColorAndUpdate(QColor b_color);
  void setVertexColorAndUpdate(QColor v_color);
  void scaleModel(int position);
  void scaleVertex(int position);
  void scaleLines(int scale);
  void translateModel(int direction, float amount);
  void rotateModel(int direction, float amount);
  void ceterModel();
  void changePerspective();
  void showVert();
  void changeVertDisplay();
  void changeEdgeDisplay();
  void disLines();

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void mousePressEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 private:
  QPoint lastMousePos;
  QPoint lastRmousePos;
  bool backgroundChanged;
  bool ortho;
  bool vertexRecolored;
  bool smoothVertexes;
  bool lineThicknessChanged;
  bool vertexesShown;
  bool linesShown;
  bool lineStrip;
  int scrollDelta;
  int lineThickness;
  int vertexThickness;
  bool vertexThicknessChanged;
  float m_medianX;
  float m_medianY;
  float m_medianZ;
  float m_minX;
  float m_maxX;
  float m_minY;
  float m_maxY;
  float m_minZ;
  float m_maxZ;
  QColor m_color;
  QColor m_back_color;
  QColor m_vertex_color;
  std::vector<float> m_vertexPositions;
  std::vector<uint> m_indices;
  QOpenGLShaderProgram shaderProgram;
  QMatrix4x4 projectionMatrix;
  QMatrix4x4 modelViewMatrix;
  GLuint texCoordLocation;
  GLuint indexBuffer;
  GLuint vertexBuffer;
  GLuint textureBuffer;
  GLuint normalBuffer;
  GLfloat translationX;
  GLfloat translationY;
  GLfloat translationZ;
  GLfloat rotationAngleX;
  GLfloat rotationAngleY;
  GLfloat rotationAngleZ;
  float scaleBy;
  float aspectRatio;
  const char* vertexShaderSource =
      "attribute vec3 position;\n"
      "uniform mat4 projectionMatrix;\n"
      "uniform mat4 modelViewMatrix;\n"
      "void main()\n"
      "{\n"
      "    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, "
      "1.0);\n"
      "}\n";

  const char* fragmentShaderSource =
      "uniform vec4 color;\n"
      "uniform bool dashed;\n"
      "void main()\n"
      "{\n"
      "    if (dashed)\n"
      "    {\n"
      "        float dashSize = 0.3;\n"
      "        float gapSize = 0.3;\n"
      "        float t = mod(gl_FragCoord.x, (dashSize + gapSize)) / (dashSize "
      "+ gapSize);\n"
      "        if (t > 0.5)\n"
      "        {\n"
      "            gl_FragColor = color;\n"
      "        }\n"
      "        else\n"
      "        {\n"
      "            discard;\n"
      "        }\n"
      "    }\n"
      "    else\n"
      "    {\n"
      "        gl_FragColor = color;\n"
      "    }\n"
      "}\n";
};

#endif  // WIDGET_H
