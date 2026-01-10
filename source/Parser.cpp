//
// Created by sebastian on 1/9/26.
//

#include "Parser.h"
#include <stdexcept>

/**
 * @brief Parses a sequence of tokens into a JSONValue.
 *
 * This method takes a vector of tokens representing a JSON input and attempts to parse them
 * into a structured JSONValue. It validates the sequence of tokens and ensures that the
 * input adheres to JSON syntax rules.
 *
 * @param Tokens A vector of Token objects representing the lexed JSON input.
 * @return A JSONValue object representing the parsed JSON structure.
 * @throws std::runtime_error If the input contains unexpected data after the end of a valid JSON structure.
 */
JSONValue Parser::Parse(const std::vector<Token>& Tokens)
{
  Parser instance(Tokens);

  if (instance.Peek().type == TokenType::END_OF_FILE)
  {
    return {JSONValue()};
  }

  JSONValue value = instance.ParseValue();

  if (instance.Peek().type != TokenType::END_OF_FILE)
  {
    throw std::runtime_error("Unexpected data after end of JSON");
  }

  return value;
}

/**
 * @brief Parses the next token in the sequence into a JSONValue.
 *
 * This method examines the current token in the input stream and determines
 * its type to construct the appropriate JSONValue. It handles various JSON
 * value types, including objects, arrays, strings, integers, doubles, booleans,
 * and null values. Unexpected token types result in an exception.
 *
 * @return A JSONValue object representing the parsed value. The type of the
 *         JSONValue depends on the token being processed:
 *         - JSON object for LEFT_BRACE tokens
 *         - JSON array for LEFT_BRACKET tokens
 *         - String for STRING tokens
 *         - Integer for INT tokens
 *         - Double for DOUBLE tokens
 *         - Boolean for TRUE and FALSE tokens
 *         - Null for NULL_TYPE tokens
 * @throws std::runtime_error If the token type is unknown or unexpected.
 */
JSONValue Parser::ParseValue()
{
  Token token = Peek();

  switch (token.type)
  {
  case TokenType::LEFT_BRACE:
    {
      return ParseObject();
    }

  case TokenType::LEFT_BRACKET:
    {
      return ParseArray();
    }

  case TokenType::STRING:
    {
      Next();
      std::string value = ParseString(token.value);
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
      return {}; // std::monostate
    }

  default:
    {
      throw std::runtime_error("Unexpected token type" + std::string(token.value));
    }
  }
}

/**
 * @brief Parses a JSON object from the current sequence of tokens.
 *
 * This method extracts a JSON object structure from the token stream, ensuring that
 * all required syntax rules are followed. It assumes that the token at the current
 * position is a left brace ({) and processes until a matching right brace (}) is found.
 * Within the object, key-value pairs are parsed, where each key is expected to be a
 * string followed by a colon (:), and each value can be any valid JSON type. Keys are
 * unique within the object, and pairs are separated by commas (,).
 *
 * @return A JSONValue object representing the parsed JSON object, where the keys are
 *         mapped to their corresponding JSON values.
 * @throws std::runtime_error If the input tokens do not match the expected JSON object format
 *                            or if unexpected tokens are encountered.
 */
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

  Expect(TokenType::RIGHT_BRACE);
  Next(); // Eat the ending brace
  return JSONValue{value};
}

/**
 * @brief Parses a JSON array from the current token sequence.
 *
 * This method processes a sequence of tokens that represent a JSON array,
 * including handling nested arrays and validating the syntax. It expects the
 * current token to be the beginning of an array ('[') and iteratively parses
 * each array element until the closing bracket (']') is reached.
 *
 * @return A JSONValue object containing a vector of JSONValue elements
 *         representing the parsed array.
 * @throws std::runtime_error If the syntax is invalid, such as a missing
 *         closing bracket, or if any array element is improperly formatted.
 */
JSONValue Parser::ParseArray()
{
  Expect(TokenType::LEFT_BRACKET);
  Next(); // Eat beginning bracket

  std::vector<JSONValue> value;

  while (Peek().type != TokenType::RIGHT_BRACKET)
  {
    value.push_back(ParseValue());

    if (Peek().type != TokenType::RIGHT_BRACKET)
    {
      Expect(TokenType::COMMA);
      Next();
    }
  }

  Expect(TokenType::RIGHT_BRACKET);
  Next(); // Eat ending bracket
  return JSONValue{value};

}

std::string Parser::ParseString(const std::string_view& str)
{
  std::string value;
  value.reserve(str.size()); // Reserves memory for the worst case scenario.

  for (unsigned int i = 0; i < str.length(); i++)
  {
    if (str[i] == '\\' && i + 1 < str.length())
    {
      switch (str[i + 1]) // We check the char after the '\'
      {
        case '"': value += '"'; break;
        case 'n': value += '\n'; break;
        case 't': value += '\t'; break;
        case 'r': value += '\r'; break;
        case '\\': value += '\\'; break;
        default: value += str[i + 1];
      }
      i++; // Eat the char
    }
    else
    {
      value += str[i];
    }
  }
  return value;
}

/**
 * @brief Retrieves the current token at the parser's current position without advancing the index.
 *
 * This method provides a lookahead capability by returning the token currently pointed to
 * by the parser's index. It does not modify the state of the parser or move its position.
 *
 * @return The current Token object at the parser's position.
 * @throws std::out_of_range If the index is out of bounds of the token vector.
 */
Token Parser::Peek() const
{
  return m_tokens.at(m_index);
}

/**
 * @brief Advances the parser to the next token.
 */
void Parser::Next()
{
  m_index++;
}

/**
 * @brief Ensures that the next token in the sequence matches the expected type.
 *
 * This method verifies that the current token, as indicated by the parser's
 * internal index, has the specified type. If the token type does not match the
 * expected type, an exception is thrown, signaling that the input does not conform
 * to the expected format or syntax.
 *
 * @param type The expected token type to match against the current token.
 * @throws std::runtime_error If the current token type does not match the expected type.
 */
void Parser::Expect(const TokenType type) const
{
  if (m_tokens.at(m_index).type != type)
  {
    throw std::runtime_error("Unexpected token type");
  }
}
