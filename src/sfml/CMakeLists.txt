file(GLOB SRC_SFML *.cpp)

add_library(arcade_sfml SHARED ${SRC_SFML} ${SRC_SHARED})

target_include_directories(arcade_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_sfml PROPERTIES PREFIX "")

set_target_properties(arcade_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system)
