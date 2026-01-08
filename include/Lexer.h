//
// Created by sebastian on 1/8/26.
//

#pragma once
#include <string>
#include <vector>

/**
 * @enum TokenType
 * @brief Represents the different types of tokens that can be identified by the lexer.
 *
 * The TokenType enum is used to classify various parts of input
 * (e.g., JSON structures or syntax) into corresponding token types.
 */
enum class TokenType
{
  LEFT_BRACE,     // {
  RIGHT_BRACE,    // }
  LEFT_BRACKET,   // [
  RIGHT_BRACKET,  // ]
  COLON,          // :
  COMMA,          // ,
  STRING,         // "string"
  NUMBER,         // 3, 2.71828
  TRUE,           // true
  FALSE,          // false
  NULL_TYPE,      // null
  END_OF_FILE     // Only used to mark the end
};

/**
 * @struct Token
 * @brief Represents a single token identified by the lexer.
 *
 * The Token struct encapsulates the type of token and its associated string value.
 *
 * @details
 * - The `type` field indicates the category of the token (e.g., braces, strings, numbers).
 * - The `value` field contains the textual representation of the token,
 */
struct Token
{
  TokenType type;
  std::string value;
};
