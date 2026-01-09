//
// Created by sebastian on 1/7/26.
//

#pragma once
#include <variant>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>

/**
 * @struct JSONValue
 * @brief Represents a JSON-compatible data structure that can hold various types of values.
 *
 * The JSONValue structure is used to represent JSON data. It supports the following types:
 * - Null values
 * - Integers
 * - Floating-point numbers
 * - Boolean values
 * - Strings
 * - JSON arrays (std::vector<JSONValue>)
 * - JSON objects (std::map<std::string, JSONValue>)
 */
struct JSONValue
{
  std::variant<std::monostate, int, double, bool, std::string, std::vector<JSONValue>, std::map<std::string, JSONValue>> data;

  // Helpers to determine the type of data.
  [[nodiscard]] bool IsNull() const { return std::holds_alternative<std::monostate>(data); }
  [[nodiscard]] bool IsInt() const { return std::holds_alternative<int>(data); }
  [[nodiscard]] bool IsDouble() const { return std::holds_alternative<double>(data); }
  [[nodiscard]] bool IsBool() const { return std::holds_alternative<bool>(data); }
  [[nodiscard]] bool IsString() const { return std::holds_alternative<std::string>(data); }
  [[nodiscard]] bool IsJSONArray() const { return std::holds_alternative<std::vector<JSONValue>>(data); }
  [[nodiscard]] bool IsJSONObject() const { return std::holds_alternative<std::map<std::string, JSONValue>>(data); }

  // Accessing JSONArray
  JSONValue& operator[](const unsigned int index)
  {
    if (!IsJSONArray()) throw std::runtime_error("Cannot access element of non-array JSON value");
    return std::get<std::vector<JSONValue>>(data).at(index);
  }

  // Accessing JSONObject
  JSONValue& operator[](const std::string& key)
  {
    if (!IsJSONObject()) throw std::runtime_error("Cannot access element of non-object JSON value");
    return std::get<std::map<std::string, JSONValue>>(data).at(key);
  }

  // Handling the c-style string
  JSONValue& operator[](const char* key)
  {
    return (*this)[std::string(key)];
  }


  // Implicit conversions for regular data
  operator std::string() const
  {
    if (!IsString()) throw std::runtime_error("Cannot convert non-string JSON value to string");
    return std::get<std::string>(data);
  }

  operator int() const
  {
    if (!IsInt()) throw std::runtime_error("Cannot convert non-integer JSON value to int");
    return std::get<int>(data);
  }

  operator double() const
  {
    if (!IsDouble()) throw std::runtime_error("Cannot convert non-double JSON value to double");
    return std::get<double>(data);
  }

  operator bool() const
  {
    if (!IsBool()) throw std::runtime_error("Cannot convert non-bool JSON value to bool");
    return std::get<bool>(data);
  }




};