//
// Created by sebastian on 1/6/26.
//

#include "JSON.h"
#include <iostream>

int main()
{
  // Test String with negative values
  std::string source = R"(
{
    "sci_int": 1e3,
    "sci_negative_exp": 1.5e-2,
    "sci_uppercase": 5E+2,
    "sci_signed": -4.2e1,
    "sci_zero": 10e0
}
)";

  JSONValue val = JSON::Parse(source);

  std::cout << static_cast<double>(val["sci_int"]) << std::endl;
  std::cout << static_cast<double>(val["sci_negative_exp"]) << std::endl;
  std::cout << static_cast<double>(val["sci_uppercase"]) << std::endl;
  std::cout << static_cast<double>(val["sci_signed"]) << std::endl;
  std::cout << static_cast<double>(val["sci_zero"]) << std::endl;
}
