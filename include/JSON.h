//
// Created by sebastian on 1/9/26.
//

#pragma once
#include "JSONValue.h"

/**
 * @class JSON
 * @brief A utility class for working with JSON data. Provides methods to parse and load JSON strings into JSONValue objects.
 *
 * The JSON class offers static methods to handle JSON data represented as text. It supports parsing and loading JSON strings,
 * converting them into a JSONValue object for further manipulation.
 */
class JSON
{
public:
  static JSONValue Parse(const std::string& source);
  static JSONValue Load(const std::string& filepath);
};
