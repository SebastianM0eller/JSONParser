//
// Created by sebastian on 1/8/26.
//

#pragma once
#include "Token.h"
#include <vector>

/**
 * @class Lexer
 * @brief A class responsible for tokenizing input strings.
 *
 * The Lexer class is used to process input strings and generate a sequence
 * of tokens based on predefined token types. It serves as a foundational
 * component for parsing and analyzing structured input.
 */
class Lexer
{
public:
  static std::vector<Token> Tokenize(const std::string_view& source);

private:
  Lexer(const std::string_view& source) : m_source(source), m_index(0) {}
  ~Lexer() = default;

  std::string_view m_source;
  unsigned int m_index;

  void SkipWhitespace();
  Token nextToken();
  Token SimpleToken(TokenType type);
  Token StringToken();
  Token NumberToken();
  Token BoolOrNullToken();
};