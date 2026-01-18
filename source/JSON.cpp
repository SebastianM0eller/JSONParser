//
// Created by sebastian on 1/9/26.
//

#include "JSON.h"

#include <filesystem>

#include "Lexer.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Converts the JSONValue instance into its string representation.
 *
 * The output format depends on the type of the contained value:
 * - A numeric value is converted to its string equivalent.
 * - A boolean value is converted to "true" or "false".
 * - A string value is enclosed in double quotes.
 * - A JSON array is represented as a comma-separated list enclosed in square brackets.
 * - A JSON object is represented as a comma-separated list of key-value pairs enclosed in curly braces,
 *   where keys are strings enclosed in double quotes.
 *
 * @return A string representation of the JSONValue instance.
 */
std::string JSONValue::ToString() const
{
  if (IsDouble()) return std::to_string(AsDouble());

  if (IsBool()) return AsBool() ? "true" : "false";

  if (IsString()) return "\"" + AsString() + "\"";

  if (IsJSONArray())
  {
    std::string result = "[";
    for (const auto& element : AsArray())
    {
      result += element.ToString() + ", ";
    }
    return result.substr(0, result.size() - 2) + "]";
  }

  if (IsJSONObject())
  {
    std::string result = "{";
    for (const auto& [key, value] : AsObject())
    {
      result += "\"" + key + "\": " + value.ToString() + ", ";
    }
    return result.substr(0, result.size() - 2) + "}";
  }
  return "";
}

/**
 * Parses a JSON string and returns its corresponding JSONValue representation.
 *
 * @param source The JSON-encoded string to be parsed.
 * @return A JSONValue object representing the parsed JSON.
 * @throws std::runtime_error If the input cannot be tokenized or parsed properly.
 */
JSONValue JSON::Parse(const std::string& source)
{
  auto tokens = Lexer::Tokenize(source);
  return Parser::Parse(tokens);
}

/**
 * Loads and parses a JSON file from the specified file path.
 *
 * @param filepath The path to the JSON file to be loaded.
 * @return A JSONValue object representing the parsed JSON content.
 * @throws std::runtime_error If the file could not be opened or its contents could not be parsed.
 */
JSONValue JSON::LoadFromFile(const std::string& filepath)
{
  std::ifstream file(filepath);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not open file");
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return Parse(buffer.str());
}

void JSON::SaveToFile(const std::string& filepath, const JSONValue& value)
{
  // Make sure the path exist
  std::filesystem::path path(filepath);
  std::filesystem::path dir = path.parent_path();

  if (!dir.empty() && !std::filesystem::exists(dir))
  {
    std::filesystem::create_directories(dir);
  }

  const std::string json = value.ToString();

  std::ofstream file(filepath, std::ios::out | std::ios::trunc);

  if (!file.is_open())
  {
    std::cerr << "Could not open file: " + filepath << std::endl;
  }

  file << json;
  file.close();
}
