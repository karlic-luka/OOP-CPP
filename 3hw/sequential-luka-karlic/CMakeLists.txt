cmake_minimum_required(VERSION 3.2)
project(sequential)
 
enable_testing()
# Googletest mora biti instaliran
find_package(GTest REQUIRED)

#  Ako imate problema kompilirati googletest zakomentirajte find_package() liniju
# i odkomentirajte donji kod koji lokalno instalira i kompilira googletest.
# Napravite direktorij external, uđite u njega i izvedite naredbu
# git submodule add https://github.com/google/googletest
# To će dovući googletest u external/googletest direktorij.
## Compilation of googletest library #####
#set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")
#
#include_directories(
#    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
#    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
#    )
#
#set(GOOGLETEST_SOURCES
#    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
#    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
#    )
#
#foreach(_source ${GOOGLETEST_SOURCES})
#    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
#endforeach()
#
#add_library(googletest ${GOOGLETEST_SOURCES})
##########################################




add_executable(sequential main.cpp sequential.cpp sequential.h) 

set_target_properties(sequential
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)

add_subdirectory(test)