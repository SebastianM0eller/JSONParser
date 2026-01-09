//
// Created by sebastian on 1/6/26.
//

#include "JSON.h"
#include <iostream>

int main()
{
  // Test String with negative values
  std::string source = R"(
{
    "temperature": -5,
    "latitude": -45.67,
    "coordinates": [ -100, 200, -30.5 ],
    "balance": -0.0
}
)";

  try
  {
    // 1. Parse
    JSONValue root = JSON::Parse(source);

    // 2. Extract Values
    int temp = root["temperature"];
    double lat = root["latitude"];
    int coordX = root["coordinates"][0];   // Should be -100
    double coordZ = root["coordinates"][2]; // Should be -30.5

    // 3. Print Results
    std::cout << "Temperature: " << temp << " (Expected: -5)" << std::endl;
    std::cout << "Latitude:    " << lat  << " (Expected: -45.67)" << std::endl;
    std::cout << "Coord X:     " << coordX << " (Expected: -100)" << std::endl;
    std::cout << "Coord Z:     " << coordZ << " (Expected: -30.5)" << std::endl;

  }
  catch (const std::exception& e)
  {
    std::cerr << "Test Failed: " << e.what() << std::endl;
  }

  return 0;
}
