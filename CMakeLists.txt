cmake_minimum_required(VERSION 3.10)

project(arcade)

set(CMAKE_CXX_STANDARD 17)

include_directories(shared)

file(GLOB SRC_SHARED shared/*.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-unique")

add_subdirectory(src/arcade)
add_subdirectory(src/ncurses)
add_subdirectory(src/libcaca)
add_subdirectory(src/sfml)
add_subdirectory(src/sdl2)
add_subdirectory(src/snake)
add_subdirectory(src/nibbler)
