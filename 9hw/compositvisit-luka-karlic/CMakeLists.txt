cmake_minimum_required(VERSION 3.4)

project(compositVisit CXX)
enable_testing()
find_package(GTest REQUIRED)

add_subdirectory("src")
add_subdirectory("test")

