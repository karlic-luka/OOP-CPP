add_executable("test_zad" test-zad.cpp test-vect.h ../src/vect.h ../src/vect_impl.h)
target_link_libraries("test_zad" googletest pthread)


#add_custom_command(
#        TARGET test_zad POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_SOURCE_DIR}/test/*.txt
#                ${CMAKE_CURRENT_BINARY_DIR})
add_test(
  NAME test_zad
  COMMAND test_zad
)
