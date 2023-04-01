file(GLOB SRC_ARCADE *.cpp)

add_executable(arcade ${SRC_ARCADE} ${SRC_SHARED})

target_compile_options(arcade PRIVATE -fno-gnu-unique)

target_link_libraries(arcade PRIVATE ${CMAKE_DL_LIBS})

target_include_directories(arcade PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})