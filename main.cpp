//
// Created by sebastian on 1/6/26.
//

#include <iostream>
#include "Lexer.h"

int main()
{
  std::string source = R"(
{
    "user_id": 42,
    "score": 98.6,
    "is_active": true,
    "history": [ null, 0, 10.50 ],
    "mode": "advanced"
}
)";

  std::vector Tokens = Lexer::Tokenize(source);
  for (auto token : Tokens)
  {
    std::cout << token.ToString() << "  " << token.value << std::endl;
  }
}