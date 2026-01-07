//
// Created by sebastian on 1/7/26.
//

#pragma once
#include <variant>
#include <vector>
#include <map>
#include <string>

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
};