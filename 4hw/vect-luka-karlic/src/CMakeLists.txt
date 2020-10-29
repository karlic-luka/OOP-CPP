#add_library("vect_lib" vect.h vect.cpp)
add_executable("vect" main.cpp vect.h vect_impl.h)
#target_link_libraries("vect" vect_lib)

#add_custom_command(
#        TARGET stl POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_SOURCE_DIR}/src/*.txt
#                ${CMAKE_CURRENT_BINARY_DIR})
