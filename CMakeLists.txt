cmake_minimum_required(VERSION 3.10)
project(cpp-logger)

set(CMAKE_CXX_STANDARD 20)

add_library(logger src/logger.cpp)
target_include_directories(logger PRIVATE include/logger)
add_executable(tests tests/main.cpp)
target_link_libraries(tests logger)
