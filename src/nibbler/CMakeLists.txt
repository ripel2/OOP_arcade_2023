file(GLOB SRC_NIBBLER *.cpp)

add_library(arcade_nibbler SHARED ${SRC_NIBBLER} ${SRC_SHARED})

target_include_directories(arcade_nibbler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_nibbler PROPERTIES PREFIX "")

set_target_properties(arcade_nibbler PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
