include_directories(${GTEST_INCLUDE_DIR})
add_executable(tests tests.cpp ../sequential.cpp ../sequential.h)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)
set_target_properties(tests
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)
#za ctest
add_test(NAME tests COMMAND tests)