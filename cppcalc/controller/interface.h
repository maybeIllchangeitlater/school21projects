#ifndef CPP3_SMART_CALC_V_2_0_CONTROLLER_INTERFACE_H
#define CPP3_SMART_CALC_V_2_0_CONTROLLER_INTERFACE_H

#include <memory>
#include <string>
namespace s21 {
class ControllerInterface {
 public:
  /**
   * @brief Virtual destructor for the ControllerInterface class.
   */
  virtual ~ControllerInterface(){};
  /**
   * @brief Calculate the result of an expression.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   */
  virtual void Calculate(std::byte* expression, size_t& length) = 0;
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
  virtual void MakeGraph(std::byte* expression, size_t& length,
                         const std::byte* xystep,
                         std::unique_ptr<std::byte[]>& res,
                         std::unique_ptr<std::byte[]>& res_size) = 0;
  /**
   * @brief Perform calculations based on deposit settings.
   *
   * @param deposit_settings Pointer to the deposit settings data.
   */
  virtual void DepositCalc(std::unique_ptr<std::byte[]>& deposit_settings) = 0;
  /**
   * @brief Perform calculations based on credit information.
   *
   * @param credit_info Pointer to the credit information data.
   */
  virtual void CreditCalc(std::byte* credit_info) = 0;
};
}  // namespace s21
#endif  // CPP3_SMART_CALC_V_2_0_CONTROLLER_INTERFACE_H
