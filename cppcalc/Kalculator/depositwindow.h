#ifndef CPP3_SMARTCALC_V2_KALCULATOR_DEPOSITWINDOW_H
#define CPP3_SMARTCALC_V2_KALCULATOR_DEPOSITWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <cstring>

#include "../controller/controller.h"

namespace Ui {
class DepositWindow;
}
/**
 * @brief The DepositWindow class represents the main window for deposit-related
 * actions.
 *
 * This class is a QMainWindow that provides a user interface for performing
 * deposit-related actions, such as replenishing and withdrawing funds. It
 * interacts with the s21::Controller class to manage the underlying
 * calculations and data.
 */
class DepositWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a DepositWindow object.
   * @param controller A reference to the s21::Controller instance for handling
   * deposit actions.
   * @param parent The parent QWidget (optional).
   */
  explicit DepositWindow(const s21::Controller &controller,
                         QWidget *parent = nullptr);
  /**
   * @brief Destructor for the DepositWindow.
   */
  ~DepositWindow();

 private slots:
  /**
   * @brief Slot for replenishing the account balance.
   *
   * This slot is connected to a UI action and triggers the process of adding
   * funds to the account.
   */
  void ReplenishBalance();

  /**
   * @brief Slot for withdrawing funds from the account balance.
   *
   * This slot is connected to a UI action and triggers the process of deducting
   * funds from the account.
   */
  void WithdrawBalance();
  /**
   * @brief Slot for performing a deposit calculation.
   *
   * This slot is connected to a UI action and initiates the deposit calculation
   * process using the provided s21::Controller.
   */
  void CalcDeposit();
  /**
   * @brief Overridden function to handle the show event of the window.
   * @param event The QShowEvent being triggered.
   */
  void showEvent(QShowEvent *event) override;

 private:
  Ui::DepositWindow *ui;
  std::vector<double> replenish_;
  std::vector<double> withdrawl_;
  s21::Controller controller_;
};

#endif  // CPP3_SMARTCALC_V2_KALCULATOR_CREDITWINDOW_H
