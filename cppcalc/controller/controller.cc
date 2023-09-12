#include "controller.h"
namespace s21 {
Controller::Controller(const Model& model) : model_(model) {}

Controller::~Controller() = default;

void Controller::Calculate(std::byte* expression, size_t& length) {
  model_.Calculate(expression, length);
}

void Controller::MakeGraph(std::byte* expression, size_t& length,
                           const std::byte* xystep,
                           std::unique_ptr<std::byte[]>& res,
                           std::unique_ptr<std::byte[]>& res_size) {
  model_.MakeGraph(expression, length, xystep, res, res_size);
}

void Controller::DepositCalc(std::unique_ptr<std::byte[]>& deposit_settings) {
  model_.CalculateDeposit(deposit_settings);
}

void Controller::CreditCalc(std::byte* credit_info) {
  model_.CalculateCredit(credit_info);
}
}  // namespace s21
