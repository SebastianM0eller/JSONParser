//
// Created by sebastian on 1/9/26.
//

#include "JSON.h"
#include "Lexer.h"
#include "Parser.h"
#include <fstream>
#include <sstream>

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
