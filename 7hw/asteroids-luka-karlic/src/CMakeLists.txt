add_executable("main" main.cpp game.cpp textureHolder.cpp entities.cpp
                               game.h textureHolder.h entities.h)
#target_link_libraries("main" sfml-graphics sfml-window sfml-system)
target_link_libraries("main" ${SFML_LIBRARIES})
target_compile_features(main PRIVATE cxx_range_for)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/*
                ${CMAKE_CURRENT_BINARY_DIR} )
