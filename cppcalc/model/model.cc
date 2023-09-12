#include "model.h"
namespace s21 {
void Model::Calculate(std::byte* expression, size_t& length) {
  if (!InitialStringTransformation(expression, length) ||
      std::regex_search(expr_, std::regex("x")) || !Validate()) {
    expr_ = "ERROR";
  } else if (!ToRPN()) {
    expr_ = "ERROR";
  } else {
    Eval();
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(7) << operstack_.back().second;
    expr_ = stream.str();
  }

  length = expr_.length();
  auto data(expr_.c_str());
  std::memcpy(expression, data, length);
}

void Model::MakeGraph(std::byte* expression, size_t& length,
                      const std::byte* xystep,
                      std::unique_ptr<std::byte[]>& res,
                      std::unique_ptr<std::byte[]>& res_size) {
  InitialStringTransformation(expression, length);
  double graph_setting[5];
  std::memcpy(graph_setting, xystep, 5 * sizeof(double));
  graph_setting[4] = FixStep(graph_setting);
  if (!ValidateGraph(graph_setting) || !Validate()) {
    res = nullptr;
  } else if (!ToRPN()) {
    res = nullptr;
  } else {
    std::vector<double> xs;
    std::vector<double> ys;
    std::vector<size_t> indexes;
    FillGraphVectors(graph_setting, xs, ys, indexes);
    GraphToBytes(xs, ys, indexes, length, res, res_size);
  }
}

void Model::FromByteToString(std::byte* expression, size_t& length) {
  std::string decoded_expression(reinterpret_cast<char*>(expression), length);
  expr_ = decoded_expression;
}

void Model::Transform() {
  expr_ = std::regex_replace(
      expr_, std::regex("Asin\\(", std::regex_constants::icase), "@4(");
  expr_ = std::regex_replace(
      expr_, std::regex("Acos\\(", std::regex_constants::icase), "@5(");
  expr_ = std::regex_replace(
      expr_, std::regex("Atan\\(", std::regex_constants::icase), "@6(");
  expr_ = std::regex_replace(
      expr_, std::regex("sin\\(", std::regex_constants::icase), "@1(");
  expr_ = std::regex_replace(
      expr_, std::regex("cos\\(", std::regex_constants::icase), "@2(");
  expr_ = std::regex_replace(
      expr_, std::regex("tan\\(", std::regex_constants::icase), "@3(");
  expr_ = std::regex_replace(
      expr_, std::regex("ln\\(", std::regex_constants::icase), "@7(");
  expr_ = std::regex_replace(
      expr_, std::regex("log\\(", std::regex_constants::icase), "@8(");
  expr_ = std::regex_replace(
      expr_, std::regex("sqrt\\(", std::regex_constants::icase), "@9(");
  expr_ = std::regex_replace(
      expr_, std::regex("mod", std::regex_constants::icase), "%");
  expr_ = std::regex_replace(
      expr_, std::regex("e", std::regex_constants::icase), "*10^");
  expr_ = std::regex_replace(expr_,
                             std::regex(" ", std::regex_constants::icase), "");
  expr_ = std::regex_replace(expr_, std::regex("X"), "x");
  FixUnary();
}

void Model::FixUnary() {
  size_t str_size = expr_.size();
  std::string opers("+-*/%^(");
  if (expr_[0] == '+') {
    expr_.erase(0, 1);
    --str_size;
  }
  if (expr_[0] == '-') {
    expr_[0] = '~';
  }
  for (size_t i = 1; i < str_size; ++i) {
    if (expr_[i] == '-' && opers.find(expr_[i - 1]) != std::string::npos) {
      expr_[i] = '~';
    }
    if (expr_[i] == '+' && opers.find(expr_[i - 1]) != std::string::npos) {
      expr_.erase(i, 1);
      --str_size;
    }
  }
}

bool Model::Validate() const {
  if (expr_.size() > 255) return false;
  if (std::regex_match(
          expr_, std::regex("[*\\/\\%\\^].*|.*([\\*\\/\\+\\-\\%\\^\\~][\\*\\/"
                            "\\%\\^\\+\\-]|(@+@+)|\\d+\\.\\d+\\.).*")))
    return false;
  if (!std::regex_match(expr_, std::regex(".*((\\d)|(x))\\)*$"))) return false;
  if (std::regex_match(expr_, std::regex(".*(@\\d)\\)*$"))) return false;
  if (expr_.find_first_not_of("0123456789./*+-%^@()x~") != std::string::npos)
    return false;
  if (std::count(expr_.begin(), expr_.end(), '(') !=
      std::count(expr_.begin(), expr_.end(), ')'))
    return false;
  return true;
}

double Model::FixStep(double graph_set[]) const noexcept {
  return (((graph_set[1] - graph_set[0]) / graph_set[4]) > 200000)
             ? ((graph_set[1] - graph_set[0]) / 200000)
             : (graph_set[4]);
}

bool Model::ValidateGraph(const double graph_settings[]) const noexcept {
  return (graph_settings[0] < graph_settings[1]) &&
         (graph_settings[2] < graph_settings[3]) &&
         (graph_settings[4] < graph_settings[1] - graph_settings[0]) &&
         graph_settings[0] >= -1000000 && graph_settings[2] >= -1000000 &&
         graph_settings[1] <= 1000000 && graph_settings[3] <= 1000000;
}

void Model::GraphToBytes(std::vector<double>& xs, std::vector<double>& ys,
                         std::vector<size_t>& indexes, size_t& length,
                         std::unique_ptr<std::byte[]>& res,
                         std::unique_ptr<std::byte[]>& res_size) {
  xs.insert(xs.end(), ys.begin(), ys.end());
  length = xs.size();
  res = std::make_unique<std::byte[]>(length * sizeof(double));
  std::memcpy(res.get(), xs.data(), length * sizeof(double));
  length = indexes.size();
  res_size = std::make_unique<std::byte[]>(indexes.size() * sizeof(size_t));
  std::memcpy(res_size.get(), indexes.data(), length * sizeof(size_t));
  std::vector<size_t> indexess(length);
  std::memcpy(indexess.data(), res_size.get(), length * sizeof(size_t));
  length = indexes.size();
}

bool Model::InitialStringTransformation(std::byte* expression, size_t& length) {
  FromByteToString(expression, length);
  if (std::regex_search(expr_, std::regex("@"))) return false;
  Transform();
  numstack_.clear();
  operstack_.clear();
  return true;
}

void Model::FillGraphVectors(const double graph_settings[],
                             std::vector<double>& xs, std::vector<double>& ys,
                             std::vector<size_t>& indexes) {
  size_t ssize = 0;
  bool is_valid = true;
  for (double i = graph_settings[0]; i <= graph_settings[1];
       i += graph_settings[4]) {
    Eval(i);
    if (operstack_.back().second > graph_settings[3] ||
        operstack_.back().second < graph_settings[2]) {
      indexes.push_back(ssize);
      is_valid = false;
    }
    while ((operstack_.back().second > graph_settings[3] ||
            operstack_.back().second < graph_settings[2]) &&
           (i += graph_settings[4]) <= graph_settings[1]) {
      operstack_.clear();
      Eval(i);
    }
    if (i <= graph_settings[1]) {
      is_valid = true;
      xs.push_back(i);
      ys.push_back(operstack_.back().second);
      operstack_.clear();
      ++ssize;
    }
  }
  if (is_valid) indexes.push_back(ssize);  // its the last element index111
}

bool Model::ToRPN() {
  std::string nums("0123456789.x");
  while (!expr_.empty()) {
    if (nums.find(expr_[0]) != std::string::npos) {
      NumsToStack();
    } else if (expr_[0] == '(') {
      operstack_.push_back(std::make_pair(expr_[0], 0));
      expr_.erase(0, expr_[0] == '@' ? 2 : 1);
    } else if (expr_[0] == ')') {
      while (!operstack_.empty() && operstack_.back().first != '(') {
        FromOperToNumStack();
      }
      if (operstack_.empty()) {
        return false;
      } else {
        operstack_.pop_back();
      }
      expr_.erase(0, expr_[0] == '@' ? 2 : 1);
    } else {
      OpersToStack();
    }
  }
  while (!operstack_.empty()) {
    FromOperToNumStack();
  }
  return true;
}

void Model::NumsToStack() {
  numstack_.push_back(expr_[0] == 'x' ? std::make_pair('x', 0.0)
                                      : std::make_pair('?', std::stod(expr_)));
  size_t pos = expr_.find_first_not_of("0123456789.x");
  expr_.erase(0, pos == 0 ? expr_.size() : pos);
}

void Model::OpersToStack() {
  if (!operstack_.empty())
    while (!operstack_.empty() &&
           !(expr_[0] == '^' && operstack_.back().first == '^') &&
           Priority(expr_[0]) <= Priority(operstack_.back().first))
      FromOperToNumStack();

  operstack_.push_back(
      std::make_pair(expr_[0] == '@' ? expr_[1] : expr_[0], 0));
  expr_.erase(0, expr_[0] == '@' ? 2 : 1);
}

void Model::FromOperToNumStack() {
  numstack_.push_back(operstack_.back());
  operstack_.pop_back();
}

int Model::Priority(char ch) const noexcept {
  int prec(0);
  if ((ch <= '9' && ch >= '0') || ch == '@')
    prec = 6;
  else if (ch == '~')
    prec = 5;
  else if (ch == '^')
    prec = 4;
  else if (ch == '*' || ch == '/' || ch == '%')
    prec = 2;
  else if (ch == '+' || ch == '-')
    prec = 1;
  return prec;
}

void Model::Eval(double x_value) {
  double num;
  for (const auto& val : numstack_) {
    if (val.first == '?' || val.first == 'x') {
      num = val.first == 'x' ? x_value : val.second;
    } else if ((val.first >= '1' && val.first <= '9') || val.first == '~') {
      num = domath_[val.first](operstack_.back().second, 0);
      operstack_.pop_back();
    } else {
      char oper = val.first;
      num = operstack_.back().second;
      operstack_.pop_back();
      num = domath_[oper](operstack_.back().second, num);
      operstack_.pop_back();
    }
    operstack_.push_back(std::make_pair('?', num));
  }
}

void Model::CalculateDeposit(std::unique_ptr<std::byte[]>& deposit_settings) {
  double* settings[3];
  std::memcpy(settings, deposit_settings.get(), 3 * sizeof(double*));
  double amount(settings[0][0]), interest(settings[0][2]), tax(settings[0][3]),
      aquired_interst(settings[0][6]), aquired_taxes(settings[0][7]),
      aquired_deposit;
  int term(static_cast<int>(settings[0][1])),
      pereodicity(static_cast<int>(settings[0][4]));
  bool capitalization(static_cast<bool>(settings[0][5]));
  // 1 - replenishments
  // 2 - withdrawals
  aquired_deposit = amount;
  interest /= 100;
  tax /= 100;
  for (int i = 0, j = i; i < term; i += pereodicity) {
    double c_interest = capitalization ? aquired_deposit * interest
                                       : aquired_deposit * interest / 12;
    aquired_interst += c_interest;
    for (; j <= i; j++) aquired_deposit += settings[1][j] - settings[2][j];
    aquired_taxes += c_interest * tax;
  }
  aquired_deposit += aquired_interst - aquired_taxes;
  settings[0][6] = aquired_interst, settings[0][7] = aquired_taxes,
  settings[0][8] = aquired_deposit;
  std::memcpy(deposit_settings.get(), settings, 3 * sizeof(double*));
}

void Model::CalculateCredit(std::byte* credit_info) {
  std::vector<double> credit_vals(7);
  std::memcpy(credit_vals.data(), credit_info, 7 * sizeof(double));
  double total_credit(credit_vals[0]), interest_rate(credit_vals[1]), monthly,
      overpay, total_pay;
  int term(static_cast<int>(credit_vals[2]));
  bool type(static_cast<bool>(credit_vals[3]));
  interest_rate /= 100.0;
  float monthly_interest_rate(interest_rate / 12.0);

  if (type) {
    monthly = (total_credit * monthly_interest_rate *
               std::pow(1 + monthly_interest_rate, term)) /
              (std::pow(1 + monthly_interest_rate, term) - 1);
    total_pay = monthly * term;
    overpay = total_pay - total_credit;
  } else {
    monthly = total_credit / term;
    total_pay = 0.0;
    for (int i = 0; i < term; i++) {
      double interest = (total_credit - (i * monthly)) * monthly_interest_rate;
      total_pay += monthly + interest;
    }
    overpay = total_pay - total_credit;
  }
  credit_vals[4] = monthly, credit_vals[5] = overpay,
  credit_vals[6] = total_pay;
  std::memcpy(credit_info, credit_vals.data(), 7 * sizeof(double));
}
}  // namespace s21
