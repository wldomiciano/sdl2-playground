get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(${directory_name} main.c)

target_link_libraries(${directory_name} PRIVATE SDL2::SDL2main SDL2::SDL2-static)
