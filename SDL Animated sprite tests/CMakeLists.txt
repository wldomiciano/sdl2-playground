cmake_minimum_required(VERSION 3.10)
project(teste C)

set(CMAKE_C_STANDARD 11)
find_package(SDL2)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})