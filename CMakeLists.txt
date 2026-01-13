cmake_minimum_required(VERSION 3.10)
project(cpp-logger)

set(CMAKE_CXX_STANDARD 20)

add_library(logger ${PROJECT_SOURCE_DIR}/src/logger.cpp)
target_include_directories(logger PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(logger_tests ${PROJECT_SOURCE_DIR}/logger_tests/main.cpp)
target_include_directories(logger_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(logger_tests logger)
