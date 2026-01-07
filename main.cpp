//
// Created by sebastian on 1/6/26.
//

#include <iostream>
#include "JSON.h"

int main()
{
  JSONValue test;
  test.data = 4;

  std::cout << std::get<int>(test.data);
}