cmake_minimum_required(VERSION 3.25)
set(VCPKG_LIBRARY_LINKAGE static)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
#include(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

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

add_executable(main "main.cpp" "Engine.h" "Engine.cpp")
target_include_directories(main PRIVATE ${glfw3_INCLUDE_DIRS})
target_include_directories(main PRIVATE ${glm_INCLUDE_DIRS})
target_include_directories(main PRIVATE ${assimp_INCLUDE_DIRS})

add_subdirectory(core)
set(Core_DIR ${CMAKE_BINARY_DIR}/core)
find_package(Core CONFIG)
target_link_libraries(main PUBLIC Core)

add_subdirectory(render)
set(Render_DIR ${CMAKE_BINARY_DIR}/render)
find_package(Render CONFIG)
target_link_libraries(main PUBLIC Render)
