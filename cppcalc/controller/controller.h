
#ifndef CPP3_SMART_CALC_V_2_0_CONTROLLER_CONTROLLER_H
#define CPP3_SMART_CALC_V_2_0_CONTROLLER_CONTROLLER_H

#include "../model/model.h"
#include "interface.h"
namespace s21 {
class Controller : public ControllerInterface {
 public:
  /**
   * @brief Explicit constructor for the Controller class.
   *
   * @param model Reference to the Model object associated with the Controller.
   */
  explicit Controller(const Model& model);
  /**
   * @brief Destructor for the Controller class.
   */
  ~Controller() override;
  /**
   * @brief Calculate the result of an expression.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   */
  void Calculate(std::byte* expression, size_t& length) override;
  /**
   * @brief Calculate arrays for graph from an expression based on settings
   * stored in xystep.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   * @param xystep Pointer to the minx, maxx, miny, maxy and step data for the
   * graph.
   * @param res Pointer to the resulting graph data.
   * @param res_size Pointer to indexes for resulting graph data.
   */
  void MakeGraph(std::byte* expression, size_t& length, const std::byte* xystep,
                 std::unique_ptr<std::byte[]>& res,
                 std::unique_ptr<std::byte[]>& res_size) override;

  /**
   * @brief Perform calculations based on deposit settings.
   *
   * @param deposit_settings Pointer to the deposit settings data.
   */
  void DepositCalc(std::unique_ptr<std::byte[]>& deposit_settings) override;
  /**
   * @brief Perform calculations based on credit information.
   *
   * @param credit_info Pointer to the credit information data.
   */
  void CreditCalc(std::byte* credit_info) override;

 private:
  Model model_;
};
}  // namespace s21
#endif  // CPP3_SMART_CALC_V_2_0_CONTROLLER_CONTROLLER_H
