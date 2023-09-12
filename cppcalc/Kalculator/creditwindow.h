#ifndef CPP3_SMARTCALC_V2_KALCULATOR_CREDITWINDOW_H
#define CPP3_SMARTCALC_V2_KALCULATOR_CREDITWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <cstring>

#include "../controller/controller.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a CreditWindow object.
   * @param controller A reference to the s21::Controller instance for handling
   * calculations.
   * @param parent The parent QWidget (optional).
   */
  explicit CreditWindow(const s21::Controller &controller,
                        QWidget *parent = nullptr);
  /**
   * @brief Destructor for the CreditWindow.
   */
  ~CreditWindow();
 private slots:
  /**
   * @brief Slot for performing the credit calculation.
   *
   * This slot is connected to a UI action (e.g., button click) and triggers
   * the credit calculation process using the provided s21::Controller.
   */
  void CalcCred();

  /**
   * @brief Overridden function to handle the show event of the window.
   * @param event The QShowEvent being triggered.
   */
  void showEvent(QShowEvent *event) override;

 private:
  Ui::CreditWindow *ui;
  s21::Controller controller_;
};

#endif  // CPP3_SMARTCALC_V2_KALCULATOR_CREDITWINDOW_H
