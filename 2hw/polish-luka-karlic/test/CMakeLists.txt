add_executable("testPP" test.cpp ../evaluate_prefix.cpp ../evaluate_postfix.cpp)
target_link_libraries("testPP"  googletest pthread)

add_test(NAME testPP COMMAND testPP)