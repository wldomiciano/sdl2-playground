cmake_minimum_required(VERSION 3.16)

project(sdl2-playground)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

# add_subdirectory(projects/circle-drawing)
# add_subdirectory(projects/paint-clone)
# add_subdirectory(projects/matrix-effect)
# add_subdirectory(projects/game-loop)
# add_subdirectory(projects/parallax-effect)

# add_subdirectory(projects/pathfinding)
# add_subdirectory(projects/animated-sprite)
# add_subdirectory(projects/rotated-fire)


file(GLOB xxx projects/*)
foreach(dir IN LISTS xxx)
  add_subdirectory(${dir})
endforeach()

