cmake_minimum_required(VERSION 3.7)

project(pacman)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cc)
add_executable(pacman ${SRC_FILES})
target_link_libraries(pacman ${SDL2_LIBRARY})
