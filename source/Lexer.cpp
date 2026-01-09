//
// Created by sebastian on 1/8/26.
//

#include "Lexer.h"

/**
 * Tokenizes the input source string into a series of tokens.
 *
 * This method processes the given source string and extracts tokens.
 * Tokens are sequentially extracted until the end of the source string
 * is reached, as indicated by the END_OF_FILE token type.
 *
 * @param source The input string to be tokenized, passed as a string view.
 *
 * @return A vector of tokens representing the tokens of the input source.
 */

std::vector<Token> Lexer::Tokenize(const std::string_view& source)
{
  std::vector<Token> tokens;
  Lexer instance(source);

  Token token = instance.nextToken();
  while (token.type != TokenType::END_OF_FILE)
  {
    tokens.push_back(token);
    token = instance.nextToken();
  }

  // Remember the EOF token
  tokens.push_back(token);

  return tokens;
}

/**
 * Skips over consecutive whitespace characters in the input source.
 *
 * This method advances the current parsing index past any sequence of
 * space (' ') characters in the source string. It stops at the first
 * non-whitespace character or when the end of the input source is reached.
 */
void Lexer::SkipWhitespace()
{
  while (m_index < m_source.size() && std::isspace(m_source[m_index]))
  {
    m_index++;
  }
}

/**
 * Extracts and returns the next token from the source input.
 *
 * This method analyzes the current position in the source string,
 * skips over whitespace, and attempts to identify the next valid token.
 * Tokens are categorized by type such as braces, brackets, numbers,
 * strings, booleans, or the end of the input. If no recognized token
 * is found, an UNKNOWN token is returned.
 *
 * @return The next token in the source input. If the end of the source
 *         is reached, a token of type END_OF_FILE is returned.
 */
Token Lexer::nextToken()
{
  SkipWhitespace();

  // Check if we have reached the end of the file
  if (m_index >= m_source.size())
  {
    return Token{TokenType::END_OF_FILE, ""};
  }

  const char c = m_source[m_index];
  switch (c)
  {
    case '{': return SimpleToken(TokenType::LEFT_BRACE);
    case '}': return SimpleToken(TokenType::RIGHT_BRACE);
    case '[': return SimpleToken(TokenType::LEFT_BRACKET);
    case ']': return SimpleToken(TokenType::RIGHT_BRACKET);
    case ':': return SimpleToken(TokenType::COLON);
    case ',': return SimpleToken(TokenType::COMMA);
    case '"': return StringToken();
    case '-': return NumberToken();

    default:
      if (std::isdigit(c)) return NumberToken();
      if (std::isalpha(c)) return BoolOrNullToken();

      return SimpleToken(TokenType::UNKNOWN);
  }
}

/**
 * Helper function for 1-char tokens (move index forward by one and return the token type)
 */

Token Lexer::SimpleToken(TokenType type)
{
  const unsigned int start = m_index;
  m_index++;
  return Token{type, m_source.substr(start, 1)};
}

/**
 * Extracts a string token from the source by processing content enclosed in double quotes.
 *
 * This method identifies and extracts a substring between two double-quote characters
 * from the current index in the source. The initial and final quotes are skipped during
 * processing. If the quotes are properly balanced, a token of type `TokenType::STRING`
 * is returned with the extracted string value.
 *
 * @return A `Token` object with `TokenType::STRING`, representing the extracted string,
 *         or an incomplete token if the input source ends unexpectedly.
 */
Token Lexer::StringToken()
{
  m_index++; // Skip the initial quote "
  const unsigned int start = m_index;
  while (m_source[m_index] != '"')
  {
    m_index++;
  }

  const std::string_view str = m_source.substr(start, m_index - start);

  if (m_index < m_source.length()) m_index++; // Skip the final quote "

  return Token{TokenType::STRING, str};
}

/**
 * Processes and extracts a numeric token (integer or decimal) from the source string.
 *
 * This method identifies and returns either an integer or a double token. If the number
 * starts with a negative sign ('-'), it will be included as part of the token. For decimal
 * numbers, the method identifies and processes the fractional part following a '.'.
 *
 * @return A Token object representing the numeric value. The token type will be
 *         TokenType::INT for integers or TokenType::DOUBLE for decimal numbers.
 */
Token Lexer::NumberToken()
{
  const unsigned int start = m_index;

  // Check if it was a negative number.
  if (m_source[m_index] == '-') m_index++;

  while (m_index < m_source.length() && std::isdigit(m_source[m_index]))
  {
    m_index++;
  }

  // Check if it's a decimal number
  if (m_index < m_source.length() && m_source[m_index] == '.')
  {
    m_index++; // Skip the decimal

    while (m_index < m_source.length() && std::isdigit(m_source[m_index]))
    {
      m_index++;
    }

    return Token(TokenType::DOUBLE, m_source.substr(start, m_index - start));
  }

  // if it wasn't a decimal number, it's an integer.
  return Token(TokenType::INT, m_source.substr(start, m_index - start));
}

/**
 * Extracts and returns a token representing a boolean value, null literal, or unknown.
 *
 * This method reads a sequence of alphanumeric characters from the input source
 * starting at the current index. If the sequence matches one of the keywords
 * "true", "false", or "null", a corresponding token is returned. If the sequence
 * does not match any of these literals, an UNKNOWN token is returned.
 *
 * @return A Token object representing a boolean value (TRUE or FALSE), a NULL_TYPE
 *         token for the "null" literal, or an UNKNOWN token if no match is found.
 */
Token Lexer::BoolOrNullToken()
{
  unsigned int start = m_index;

  while (m_index < m_source.length() && std::isalnum(m_source[m_index]))
  {
    m_index++;
  }

  const std::string_view str = m_source.substr(start, m_index - start);
  if (str == "true") return Token(TokenType::TRUE, str);
  if (str == "false") return Token(TokenType::FALSE, str);
  if (str == "null") return Token(TokenType::NULL_TYPE, str);

  return Token(TokenType::UNKNOWN, str);
}

