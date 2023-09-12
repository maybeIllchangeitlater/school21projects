#ifndef CPP3_SMARTCALC_V2_KALCULATOR_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_KALCULATOR_MAINWINDOW_H

#include <qcustomplot.h>

#include <QMainWindow>
#include <QString>
#include <utility>
#include <vector>

#include "../controller/controller.h"
#include "../model/model.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main application window.
 *
 * This class is a QMainWindow that provides a graphical user interface for
 * interacting with the calculator application. It connects with the
 * s21::Controller and other related classes to manage calculations, data, and
 * various window components.
 */

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a MainWindow object.
   * @param controller A reference to the s21::Controller instance for handling
   * calculations.
   * @param parent The parent QWidget (optional).
   */
  explicit MainWindow(const s21::Controller& controller,
                      QWidget* parent = nullptr);
  /**
   * @brief Destructor for the MainWindow.
   */
  ~MainWindow();

 private slots:
  /**
   * @brief Adds from key to string
   */
  void MakeString();
  /**
   * @brief Removes one from string
   */
  void RemoveOne();
  /**
   * @brief Clear string
   */
  void RemoveAll();
  /**
   * @brief Adds from key to string, add bracket
   */
  void MakeStringAddsBracket();
  /**
   * @brief Call calc
   */
  void Equals();
  /**
   * @brief Call graph
   */
  void MakeGraph();
  /**
   * @brief Call deposit
   */
  void Deposit();
  /**
   * @brief Call credit
   */
  void Credit();

 private:
  /**
   * @brief Converts input string to bytes
   * @param byte_array_size - size of string
   * @param string_in_byte_array - string converted to bytes
   */
  void StringToBites(size_t& byte_array_size, std::byte* string_in_byte_array);
  /**
   * @brief Convertes byte array to x and y vectors, as well as index vector
   * @param byte_array_size - size of index array
   * @param res - xy array
   * @param res_size - index array
   * @param graph_settings - pointer to graph settings
   */
  void VecsToGraphW(size_t& byte_array_size, std::unique_ptr<std::byte[]>& res,
                    std::unique_ptr<std::byte[]>& res_size,
                    double* graph_settings);
  Ui::MainWindow* ui;
  s21::Controller controller_;
  CreditWindow* credit_ = new CreditWindow(controller_);
  DepositWindow* deposit_ = new DepositWindow(controller_);
};
#endif  // CPP3_SMARTCALC_V2_KALCULATOR_MAINWINDOW_H
