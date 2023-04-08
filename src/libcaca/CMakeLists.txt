file(GLOB SRC_LIBCACA *.cpp)

add_library(arcade_libcaca SHARED ${SRC_LIBCACA} ${SRC_SHARED})

target_include_directories(arcade_libcaca PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../arcade)

set_target_properties(arcade_libcaca PROPERTIES PREFIX "")

set_target_properties(arcade_libcaca PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(arcade_libcaca PRIVATE caca)
