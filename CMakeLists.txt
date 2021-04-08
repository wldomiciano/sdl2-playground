cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(sdl2-playground LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)

if (MSVC)
    add_compile_options(/W4 /WX)
elseif(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # add_compile_options(-stdlib=lstdc++)
endif()

# add_compile_options(
#   $<$<C_COMPILER_ID:GNU>:-Wall>
#   $<$<C_COMPILER_ID:GNU>:-Wextra>
#   $<$<C_COMPILER_ID:GNU>:-Wconversion>
#   $<$<C_COMPILER_ID:GNU>:-Werror>
#   $<$<C_COMPILER_ID:GNU>:-pedantic>
#   $<$<C_COMPILER_ID:GNU>:-Wno-unused-parameter>
# )

message(">>>${MSVC}---${CMAKE_COMPILER_IS_GNUCC}---${CMAKE_C_COMPILER_ID}---${CMAKE_CXX_COMPILER_ID}<<<")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB dirs projects/*)
foreach(dir IN LISTS dirs)
  add_subdirectory(${dir})
endforeach()

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
