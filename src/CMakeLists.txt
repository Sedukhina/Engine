cmake_minimum_required(VERSION 3.25)
project(Engine VERSION 0.1)

message("generator is set to ${CMAKE_GENERATOR}")

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "Clang")
set(CMAKE_CXX_COMPILER "Clang")
message("compilers are set to ${CMAKE_C_COMPILER}/${CMAKE_CXX_COMPILER}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(main main.cpp logger.hpp logger.cpp)
