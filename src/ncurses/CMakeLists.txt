file(GLOB SRC_NCURSES *.cpp)

add_library(arcade_ncurses SHARED ${SRC_NCURSES} ${SRC_SHARED})

target_include_directories(arcade_ncurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_ncurses PROPERTIES PREFIX "")

set_target_properties(arcade_ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(arcade_ncurses ncurses)
