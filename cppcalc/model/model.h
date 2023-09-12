#ifndef CPP3_SMART_CALC_V_2_0_MODEL_MODEL_H_
#define CPP3_SMART_CALC_V_2_0_MODEL_MODEL_H_

#include <cmath>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace s21 {
/**
 * @brief The Model class that performs calculations.
 */
class Model {
 public:
  Model() = default;
  ~Model() = default;

  /**
   * @brief Calculate the result of an expression.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   */
  void Calculate(std::byte* expression, size_t& length);
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
                 std::unique_ptr<std::byte[]>& res_size);

  /**
   * @brief Perform calculations based on deposit settings.
   *
   * @param deposit_settings Pointer to the deposit settings data.
   */
  void CalculateDeposit(std::unique_ptr<std::byte[]>& deposit_settings);
  /**
   * @brief Perform calculations based on credit information.
   *
   * @param credit_info Pointer to the credit information data.
   */
  void CalculateCredit(std::byte* credit_info);

 protected:
  enum Mathematics {
    kSin = '1',
    kCos,
    kTan,
    kAsin,
    kAcos,
    kAtan,
    kLog,
    kLog10,
    kSqrt,
    kPow = '^',
    kPlus = '+',
    kMinus = '-',
    kMul = '*',
    kDiv = '/',
    kMod = '%',
    kUnary = '~'

  };
  /**
   * @brief Convert byte array to a string.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   */
  void FromByteToString(std::byte* expression, size_t& length);
  /**
   * @brief Transform the expression string.
   */
  void Transform();
  /**
   * @brief Transform unary minus and delete unary plus operators.
   */
  void FixUnary();
  /**
   * @brief Validate the expression.
   *
   * @return True if the expression is valid, false otherwise.
   */
  bool Validate() const;
  /**
   * @brief Fix step value of graph.
   *
   * @param graph settings array.
   * @return Fixed step value.
   */
  double FixStep(double array[]) const noexcept;
  /**
   * @brief Validate graph data.
   *
   * @param array Array of graph data.
   * @return True if the graph data is valid, false otherwise.
   */
  bool ValidateGraph(const double array[]) const noexcept;
  /**
   * @brief Convert graph data to byte arrays.
   *
   * @param xs X-axis values of the graph.
   * @param ys Y-axis values of the graph.
   * @param indexes Index values of the graph data.
   * @param length Length of the graph data.
   * @param res Pointer to the resulting graph data.
   * @param res_size Pointer to the size of the resulting graph data.
   */
  void GraphToBytes(std::vector<double>& xs, std::vector<double>& ys,
                    std::vector<size_t>& indexes, size_t& length,
                    std::unique_ptr<std::byte[]>& res,
                    std::unique_ptr<std::byte[]>& res_size);
  /**
   * @brief Transform the initial expression string.
   *
   * @param expression Pointer to the expression data.
   * @param length Length of the expression data.
   * @return True if successful, false otherwise.
   */
  bool InitialStringTransformation(std::byte* expression, size_t& length);

  /**
   * @brief Fill graph vectors with data.
   *
   * @param array Array of graph data.
   * @param xs Vector to store X-axis values.
   * @param ys Vector to store Y-axis values.
   * @param indexes Vector to store index values.
   */
  void FillGraphVectors(const double array[], std::vector<double>& xs,
                        std::vector<double>& ys, std::vector<size_t>& indexes);
  /**
   * @brief Convert infix expression to Reverse Polish Notation (RPN).
   *
   * @return True if successful, false otherwise.
   */
  bool ToRPN();
  /**
   * @brief Push numbers onto the stack during RPN conversion.
   */
  void NumsToStack();
  /**
   * @brief Push operators onto the stack during RPN conversion.
   */
  void OpersToStack();
  /**
   * @brief Convert operators to numbers during RPN conversion.
   */
  void FromOperToNumStack();
  /**
   * @brief Get operator priority.
   *
   * @param oper Operator character.
   * @return Priority value.
   */
  int Priority(char) const noexcept;

  /**
   * @brief Evaluate the expression and get the result.
   *
   * @param x_value X value for evaluation.
   */
  void Eval(double x_value = 0);

 private:
  std::string expr_ = "";
  std::map<char, std::function<double(double, double)>> domath_ = {
      {kSin, [](double x, double) { return std::sin(x); }},
      {kCos, [](double x, double) { return std::cos(x); }},
      {kTan, [](double x, double) { return std::tan(x); }},
      {kAsin, [](double x, double) { return std::asin(x); }},
      {kAcos, [](double x, double) { return std::acos(x); }},
      {kAtan, [](double x, double) { return std::atan(x); }},
      {kLog10, [](double x, double) { return std::log10(x); }},
      {kUnary, [](double x, double) { return -x; }},
      {kLog, [](double x, double) { return std::log(x); }},
      {kSqrt, [](double x, double) { return std::sqrt(x); }},
      {kPow, [](double x, double y) { return std::pow(x, y); }},
      {kPlus, [](double x, double y) { return x + y; }},
      {kMinus, [](double x, double y) { return x - y; }},
      {kMul, [](double x, double y) { return x * y; }},
      {kDiv, [](double x, double y) { return x / y; }},
      {kMod, [](double x, double y) { return std::fmod(x, y); }},

  };

  std::list<std::pair<char, double>> numstack_;
  std::list<std::pair<char, double>> operstack_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_MODEL_MODEL_H_
