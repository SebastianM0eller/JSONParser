//
// Created by sebastian on 1/9/26.
//

#pragma once
#include "JSONValue.h"
#include "Token.h"

/**
 * @class Parser
 * @brief A utility class for parsing JSON data represented as a sequence of tokens.
 *
 * The Parser class provides methods to parse tokens into a structured JSONValue.
 * It supports parsing JSON objects, arrays, strings, numbers, booleans, and null values.
 */
class Parser
{
public:
  static JSONValue Parse(std::vector<Token> Tokens);

private:
  Parser(const std::vector<Token>& tokens) : m_tokens(tokens), m_index(0) {}
  ~Parser() = default;

  std::vector<Token> m_tokens;
  unsigned int m_index;

  JSONValue ParseValue();
  JSONValue ParseObject();
  JSONValue ParseArray();

  [[nodiscard]] Token Peek() const;
  void Next();
  void Expect(TokenType type) const;
};
