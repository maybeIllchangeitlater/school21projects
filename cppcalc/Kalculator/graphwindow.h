#ifndef CPP3_SMARTCALC_V2_KALCULATOR_GRAPHWINDOW_H
#define CPP3_SMARTCALC_V2_KALCULATOR_GRAPHWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphWIndow;
}

class GraphWIndow : public QMainWindow {
  Q_OBJECT
  /**
   * @brief The GraphWindow class represents a window for displaying graphs.
   *
   * This class is a QMainWindow that provides a user interface for displaying
   * graphs based on provided data. It allows the user to visualize data points
   * using graphs with customizable settings.
   */
 public:
  /**
   * @brief Constructs a GraphWindow object.
   * @param xs A QVector of QVectors representing the x-coordinates of data
   * points for each graph.
   * @param ys A QVector of QVectors representing the y-coordinates of data
   * points for each graph.
   * @param graph_settings Pointer to graph settings (specific details to be
   * provided).
   * @param parent The parent QWidget (optional).
   */
  explicit GraphWIndow(const QVector<QVector<double>>& xs,
                       const QVector<QVector<double>>& ys,
                       double* graph_settings, QWidget* parent = nullptr);
  /**
   * @brief Destructor for the GraphWindow.
   */
  ~GraphWIndow();

  Ui::GraphWIndow* ui;
};

#endif  // CPP3_SMARTCALC_V2_KALCULATOR_GRAPHWINDOW_H
