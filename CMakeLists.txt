cmake_minimum_required(VERSION 3.10)

project(arcade)

set(CMAKE_CXX_STANDARD 17)

include_directories(ArcadeShared)

file(GLOB SRC_SHARED src/*.cpp)

add_subdirectory(src/arcade)
add_subdirectory(src/ncurses)
add_subdirectory(src/sfml)
add_subdirectory(src/sdl2)
add_subdirectory(src/snake)
add_subdirectory(src/nibbler)
