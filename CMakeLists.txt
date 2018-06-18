cmake_minimum_required(VERSION 3.7)

project(pacman)

# if(POLICY CMP0025)
#   cmake_policy(SET CMP0025 NEW)
# endif()
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cc)
add_executable(pacman ${SRC_FILES})
target_link_libraries(pacman ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
