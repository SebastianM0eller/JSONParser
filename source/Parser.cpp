//
// Created by sebastian on 1/9/26.
//

#include "Parser.h"
#include <stdexcept>
#include <bits/locale_facets_nonio.h>

JSONValue Parser::Parse(std::vector<Token> Tokens)
{
  Parser instance(Tokens);

  while (instance.Peek().type != TokenType::END_OF_FILE)
  {
    // ToDo:
    return {};
  }

}

JSONValue Parser::ParseValue()
{
  Token token = Peek();

  switch (token.type)
  {
  case TokenType::LEFT_BRACE:
    {
      //return ParseObject();
    }

  case TokenType::LEFT_BRACKET:
    {
      //return ParseArray();
    }

  case TokenType::STRING:
    {
      Next();
      std::string value = std::string(token.value);
      return JSONValue(value);
    }

  case TokenType::INT:
    {
      Next();
      int value = std::stoi(std::string(token.value));
      return JSONValue(value);
    }

  case TokenType::DOUBLE:
    {
      Next();
      double value = std::stod(std::string(token.value));
      return JSONValue(value);
    }

  case TokenType::TRUE:
    {
      Next();
      return JSONValue(true);
    }

  case TokenType::FALSE:
    {
      Next();
      return JSONValue(false);
    }
  case TokenType::NULL_TYPE:
    {
      Next();
      return JSONValue(); // std::monostate
    }

  default:
    {
      throw std::runtime_error("Unexpected token type" + std::string(token.value));
    }
  }
}

JSONValue Parser::ParseObject()
{
  Expect(TokenType::LEFT_BRACE);
  Next(); // Eat beginning brace

  std::map<std::string, JSONValue> value;

  while (Peek().type != TokenType::RIGHT_BRACE)
  {
    Expect(TokenType::STRING);
    std::string key = std::string(Peek().value);
    Next();

    Expect(TokenType::COLON);
    Next();

    value[key] = ParseValue();

    if (Peek().type != TokenType::RIGHT_BRACE)
    {
      Expect(TokenType::COMMA);
      Next();
    }
  }

  Next(); // Eat the ending brace
  return JSONValue{value};
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
