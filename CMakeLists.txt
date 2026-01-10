cmake_minimum_required(VERSION 3.30)
project(JSONParser)

# Standard C++ Version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the library
add_library(${PROJECT_NAME} STATIC)

# Sources
target_sources(${PROJECT_NAME} PRIVATE
        source/JSON.cpp
        source/Lexer.cpp
        source/Parser.cpp
        source/Lexer.h
        source/Parser.h
        source/Token.h
)

# Include files
target_include_directories(${PROJECT_NAME}
        PUBLIC include
        PRIVATE source
)

# Compile Options
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic
        >
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive-
        >
)

add_executable(JSONParserTest main.cpp)
target_link_libraries(JSONParserTest PRIVATE ${PROJECT_NAME})