//
// Created by sebastian on 1/9/26.
//

#pragma once
#include "JSON.h"
#include "Token.h"

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
  Token Next();
  void Expect(TokenType type) const;
};
