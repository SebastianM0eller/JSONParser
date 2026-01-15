//
// Created by sebastian on 1/6/26.
//

#include "JSON.h"
#include <iostream>

int main()
{
  // The Source JSON uses strictly ASCII characters (escaped unicode)
  std::string source = R"(
{
    "ascii_test": "\u0041",
    "latin_test": "\u00A9",
    "greek_test": "\u03A9",
    "currency_test": "\u20AC",
    "chinese_test": "\u4F60\u597D"
}
)";

  try
  {
    JSONValue root = JSON::Parse(source);

    // Expected values using raw UTF-8 literals
    // NOTE: Ensure this .cpp file is saved as UTF-8!
    std::map<std::string, std::string> expected = {
      {"ascii_test", "A"},            // \u0041
      {"latin_test", "©"},            // \u00A9
      {"greek_test", "Ω"},            // \u03A9
      {"currency_test", "€"},         // \u20AC
      {"chinese_test", "你好"}         // \u4F60 (Ni) + \u597D (Hao)
    };

    std::cout << "--- Unicode Escape Sequence Test ---" << std::endl;

    for (const auto& [key, val] : expected)
    {
      const std::string& parsedValue = root[key].ToString();

      if (parsedValue == val)
      {
        std::cout << "[PASS] " << key << ": " << parsedValue << std::endl;
      }
      else
      {
        std::cout << "[FAIL] " << key << "\n"
                  << "  Expected: " << val << "\n"
                  << "  Got:      " << parsedValue << std::endl;
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "[CRITICAL ERROR] " << e.what() << std::endl;
  }

  return 0;
}
