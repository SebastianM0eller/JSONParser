# JSONParser

> A simple C++23 JSON parsing library.

## About
The aim of this project is to learn more about C++ and JSONs.
* **Standard:** C++23
* **BuildSystem:** CMake 3.30+


### Integration

It's recommended to add it as a Git Submodule.

**Add the submodule:**
Run this in your project's root directory:
```bash
git submodule add https://github.com/SebastianM0eller/JSONParser Path/To/Destination
git submodule update --init --recursive
```

**Link the library:**
```cmake
# In your CMakeLists.txt
add_subdirectory(path/to/JSONParser)
target_link_libraries(MyApp PRIVATE JSONParser)
```


### Usage

**Include:** You only need to include the main header.

```C++
#include <JSON.h>
// JSONValue.h is automatically included
```
**Parsing a string:**
```C++
#include "JSON.h"
#include <iostream>

int main() {
    std::string raw_json = R"({ "name": "Sebastian", "score": 100 })";

    try {
        JSONValue root = JSON::Parse(raw_json);
        
        // Access values
        std::string name = root["name"];
        int score = root["score"];
        
        std::cout << name << ": " << score << std::endl;
    } 
    catch (const std::exception& e) {
        std::cerr << "Parsing failed: " << e.what() << std::endl;
    }
}
```

**Loading from a file:**
```C++
JSONValue val = JSON::Load("filename.json");
```

## Todo:
- [ ] Add support for scientific notation e.g. 3e10, 1.3e-5 or -0.5e+2.
- [ ] Add some tests to validate the library.
- [ ] Add support for all standard escape sequences.
- [ ] Add documentation on how to access data in the JSONValue.