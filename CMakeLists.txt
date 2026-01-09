cmake_minimum_required(VERSION 3.30)
project(JSONParser)

# Standard C++ Version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main executable
add_executable(${PROJECT_NAME} main.cpp)

# Include files
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Source files
target_sources(${PROJECT_NAME} PRIVATE
    source/Lexer.cpp
    source/Parser.cpp
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