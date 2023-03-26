file(GLOB SRC_SNAKE *.cpp)

add_library(arcade_snake SHARED ${SRC_SNAKE} ${SRC_SHARED})

target_include_directories(arcade_snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_snake PROPERTIES PREFIX "")

set_target_properties(arcade_snake PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
