//
// Created by sebastian on 1/9/26.
//

#include "Parser.h"

#include <stdexcept>

JSONValue Parser::Parse(std::vector<Token> Tokens)
{
  // Todo:
  return {};
}

Token Parser::Peek() const
{
  return m_tokens.at(m_index);
}

Token Parser::Next()
{
  return m_tokens.at(m_index++);
}

void Parser::Expect(const TokenType type) const
{
  if (m_tokens.at(m_index).type != type)
  {
    throw std::runtime_error("Unexpected token type");
  }
}
