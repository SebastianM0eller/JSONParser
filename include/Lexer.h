//
// Created by sebastian on 1/8/26.
//

#pragma once

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

