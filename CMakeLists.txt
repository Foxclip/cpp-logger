cmake_minimum_required(VERSION 3.10)
project(cpp-logger)

set(CMAKE_CXX_STANDARD 20)

add_library(logger ${PROJECT_SOURCE_DIR}/src/logger.cpp)
target_include_directories(logger PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(tests ${PROJECT_SOURCE_DIR}/tests/main.cpp)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests logger)
