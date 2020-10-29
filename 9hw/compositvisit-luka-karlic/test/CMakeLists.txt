include_directories(${GTEST_INCLUDE_DIR})
add_executable(tests tests.cpp ../src/composite.cpp)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)
#za ctest
add_test(NAME tests COMMAND tests)
