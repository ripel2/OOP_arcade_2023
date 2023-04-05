file(GLOB SRC_SDL2 *.cpp)

add_library(arcade_sdl2 SHARED ${SRC_SDL2} ${SRC_SHARED})

target_include_directories(arcade_sdl2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")

set_target_properties(arcade_sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(arcade_sdl2 SDL2 SDL2_image)
