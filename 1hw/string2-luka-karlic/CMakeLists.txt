cmake_minimum_required(VERSION 3.3)
project(string2)

enable_testing()

find_package(GTest REQUIRED)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(string2 src/main.cpp src/strutils.cpp)
