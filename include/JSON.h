//
// Created by sebastian on 1/9/26.
//

#pragma once
#include <variant>
#include <vector>
#include <map>
#include <stdexcept>

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

  // ##################################
  // Helper functions for the JSONArray
  // ##################################

  /// Return the data as a const std::vector<JSONValue> reference
  /// Throws an error if the data is not a JSONArray
  [[nodiscard]] const std::vector<JSONValue>& AsArray() const
  {
    if (!IsJSONArray()) throw std::runtime_error("Cannot access element of non-array JSON value");
    return std::get<std::vector<JSONValue>>(data);
  }

  /// Return the data as an std::vector<JSONValue> reference
  /// Throws an error if the data is not a JSONArray
  [[nodiscard]] std::vector<JSONValue>& AsArray()
  {
    if (!IsJSONArray()) throw std::runtime_error("Cannot access element of non-array JSON value");
    return std::get<std::vector<JSONValue>>(data);
  }

  /// Return a const reference to the data at the given index.
  /// Throws an error if the data is not a JSONArray
  const JSONValue& operator[](const int index) const
  {
    if (!IsJSONArray()) throw std::runtime_error("Cannot access element of non-array JSON value");
    return std::get<std::vector<JSONValue>>(data).at(index);
  }

  /// Return a reference to the data at the given index.
  /// Throws an error if the data is not a JSONArray
  JSONValue& operator[](const int index)
  {
    if (!IsJSONArray()) throw std::runtime_error("Cannot access element of non-array JSON value");
    return std::get<std::vector<JSONValue>>(data).at(index);
  }

  // ##################################
  // Helper functions for the JSONArray
  // ##################################

  /// Return the data as a const reference to std::map<std::string, JSONValue>
  /// Throws an error if the data is not a JSONObject
  [[nodiscard]] const std::map<std::string, JSONValue>& AsObject() const
  {
    if (!IsJSONObject()) throw std::runtime_error("Cannot access element of non-object JSON value");
    return std::get<std::map<std::string, JSONValue>>(data);
  }

  /// Return the data as a reference to std::map<std::string, JSONValue>
  /// Throws an error if the data is not a JSONObject
  [[nodiscard]] std::map<std::string, JSONValue>& AsObject()
  {
    if (!IsJSONObject()) throw std::runtime_error("Cannot access element of non-object JSON value");
    return std::get<std::map<std::string, JSONValue>>(data);
  }

  /// Return a const reference to the data at the given index.
  /// Throws an error if the data is not a JSONObject
  const JSONValue& operator[](const std::string& key) const
  {
    if (!IsJSONObject()) throw std::runtime_error("Cannot access element of non-object JSON value");
    return std::get<std::map<std::string, JSONValue>>(data).at(key);
  }

  /// Return a const reference to the data at the given index.
  /// Throws an error if the data is not a JSONObject
  const JSONValue& operator[](const char* key) const
  {
    return (*this)[std::string(key)];
  }

  /// Return a reference to the data at the given index.
  /// Throws an error if the data is not a JSONObject
  JSONValue& operator[](const std::string& key)
  {
    if (!IsJSONObject()) throw std::runtime_error("Cannot access element of non-object JSON value");
    return std::get<std::map<std::string, JSONValue>>(data).at(key);
  }

  /// Return a reference to the data at the given index.
  /// Throws an error if the data is not a JSONObject
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
    if (IsDouble())
    {
      return std::get<double>(data);
    }

    if (!IsInt()) throw std::runtime_error("Cannot convert non-integer JSON value to int");
    return std::get<int>(data);
  }

  operator double() const
  {
    if (IsInt())
    {
      return std::get<int>(data);
    }

    if (!IsDouble()) throw std::runtime_error("Cannot convert non-double JSON value to double");
    return std::get<double>(data);
  }

  operator bool() const
  {
    if (!IsBool()) throw std::runtime_error("Cannot convert non-bool JSON value to bool");
    return std::get<bool>(data);
  }
};

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