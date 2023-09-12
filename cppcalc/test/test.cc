#include <gtest/gtest.h>
#include "../model/model.h"
#include <string>
#include <iostream>

TEST(CALC, true){
    std::string aboba = "+(-Sin(0.5) + Cos(0.5) + Tan(0.5) + ATan(0.5) + ACos(0.5) + ASin(0.5)*5)/0.3^2+sqrt(9)-7mod3--5 + ln(3) - log(2)";
    double og = (-sin(0.5) + cos(0.5) + tan(0.5) + atan(0.5) + acos(0.5) + asin(0.5)*5)/pow(0.3,2)+sqrt(9)-7%3+5 + log(3) - log10(2);
    std::string amogus = "-1 * + 5";
    s21::Model m;
    size_t byte_array_size = aboba.size();
    std::byte string_in_byte_array[byte_array_size + 10];
    size_t byte_array_size2 = amogus.size();
    std::byte string_in_byte_array2[byte_array_size2 + 10];
    auto data = aboba.c_str();
    auto data2 = amogus.c_str();
    std::memcpy(string_in_byte_array, data, byte_array_size);
    m.Calculate(string_in_byte_array, byte_array_size);
    std::string abuba(reinterpret_cast<char *>(string_in_byte_array), byte_array_size);
    std::memcpy(string_in_byte_array2, data2, byte_array_size2);
    m.Calculate(string_in_byte_array2, byte_array_size2);
    std::string abubas(reinterpret_cast<char *>(string_in_byte_array2), byte_array_size2);
    abuba.erase(abuba.size()-1);
    ASSERT_TRUE(abuba == std::to_string(og));
    ASSERT_TRUE(abubas == "-5.0000000");
}

TEST(CALC, false){
    std::string aboba = "(.)/(.)";
    std::string abiba = "sadfio";
    std::string booba = "(1))";
    std::string boooba = "1*/1";
    std::string booooba = "1*a+5";
    s21::Model m;
    size_t byte_array_size = aboba.size();
    size_t byte_array_size2 = abiba.size();
    size_t byte_array_size3 = booba.size();
    size_t byte_array_size4 = boooba.size();
    size_t byte_array_size5 = booooba.size();
    std::byte string_in_byte_array[byte_array_size + 10];
    std::byte string_in_byte_array2[byte_array_size2 + 10];
    std::byte string_in_byte_array3[byte_array_size3 + 10];
    std::byte string_in_byte_array4[byte_array_size4 + 10];
    std::byte string_in_byte_array5[byte_array_size5 + 10];
    auto data = aboba.c_str();
    auto data2 = abiba.c_str();
    auto data3 = booba.c_str();
    auto data4 = boooba.c_str();
    auto data5 = booooba.c_str();
    std::memcpy(string_in_byte_array, data, byte_array_size);
    std::memcpy(string_in_byte_array2, data2, byte_array_size2);
    std::memcpy(string_in_byte_array3, data3, byte_array_size3);
    std::memcpy(string_in_byte_array4, data4, byte_array_size4);
    std::memcpy(string_in_byte_array5, data5, byte_array_size5);
    m.Calculate(string_in_byte_array, byte_array_size);
    std::string abuba(reinterpret_cast<char *>(string_in_byte_array), byte_array_size);
    m.Calculate(string_in_byte_array2, byte_array_size2);
    std::string boba(reinterpret_cast<char *>(string_in_byte_array2), byte_array_size2);
    m.Calculate(string_in_byte_array3, byte_array_size3);
    std::string kuba(reinterpret_cast<char *>(string_in_byte_array3), byte_array_size3);
    m.Calculate(string_in_byte_array4, byte_array_size4);
    std::string suba(reinterpret_cast<char *>(string_in_byte_array4), byte_array_size4);
    m.Calculate(string_in_byte_array5, byte_array_size5);
    std::string konosuba(reinterpret_cast<char *>(string_in_byte_array5), byte_array_size5);
    ASSERT_TRUE(abuba == "ERROR");
    ASSERT_TRUE(boba == "ERROR");
    ASSERT_TRUE(kuba == "ERROR");
    ASSERT_TRUE(suba == "ERROR");
    ASSERT_TRUE(konosuba == "ERROR");
}

TEST(GRAPH, true){
  std::string aboba("tan(x)");
  size_t size = aboba.size();
  double settings[] = {-10.0, 10.0, -10.0, 10.0, 1};
  std::unique_ptr<std::byte[]> output;
  std::unique_ptr<std::byte[]> output_size;
  std::byte graph_settings_to_byte_array[5 * sizeof(double)];
  std::byte expression[size + 10];
  std::memcpy(graph_settings_to_byte_array, settings, 5 * sizeof(double));
  auto data = aboba.c_str();
  std::memcpy(expression, data, size);
  s21::Model m;
  m.MakeGraph(expression, size, graph_settings_to_byte_array, output, output_size);
   std::vector<size_t> indexes(size);
        std::memcpy(indexes.data(), output_size.get(), size* sizeof(size_t));
        size_t xysize = indexes[indexes.size()-1];
        std::vector<double> q_ys(xysize);
        std::vector<double> q_xs(xysize);
        std::memcpy(q_xs.data(), output.get(), xysize*sizeof(double));
        std::memcpy(q_ys.data(), output.get() + xysize*sizeof(double), xysize*sizeof(double));
        std::vector<std::vector<double>> qv_ys;
        std::vector<std::vector<double>> qv_xs;
        size_t to_start = 0, j = 0;
        for(size_t i = 0; i < xysize;){
            i = indexes[j++];
            qv_ys.push_back(std::vector<double>(q_ys.begin() + to_start, q_ys.begin()+i));
            qv_xs.push_back(std::vector<double>(q_xs.begin() + to_start, q_xs.begin()+i));
            to_start = i;
        }
   
  ASSERT_TRUE(qv_xs.at(0)[0] + 10.0 < 1e-6);
  ASSERT_TRUE(qv_ys.at(0)[0] + 0.648360 < 1e-6);
}

TEST(DEPOSIT_CAL, true){
  double deposit_info[]{123.0, 12.0, 4.0, 2.0, 1.0, 1.0, 0.0, 0.0, 0.0};
  double rep[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double with[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   double * deposits[]{deposit_info, rep, with};
  std::unique_ptr<std::byte[]> deposit_settings =
      std::make_unique<std::byte[]>(3 * sizeof(double*));
  std::memcpy(deposit_settings.get(), deposits,
              3 * sizeof(double*));
  s21::Model m;
  m.CalculateDeposit(deposit_settings);
  ASSERT_TRUE(static_cast<int>(deposits[0][6]) == 59);
}

TEST(CREDIT_CAL, true){
  std::byte credit_info[7 * sizeof(double)];
  std::vector<double> credits{123.0,
                              12.0,
                              12.0,
                              1.0,
                              0.0,
                              0.0,
                              0.0};
  std::memcpy(credit_info, credits.data(), 7 * sizeof(double));
  s21::Model m;
  m.CalculateCredit(credit_info);
  std::memcpy(credits.data(), credit_info, 7 * sizeof(double));
  ASSERT_TRUE(static_cast<int>(credits[6]) == 131);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
