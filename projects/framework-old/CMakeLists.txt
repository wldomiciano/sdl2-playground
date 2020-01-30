get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(${directory_name} framework.c game.c sprite.c)
target_link_libraries(${directory_name} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

target_compile_options(${directory_name} PRIVATE -Wall -Wextra -Wpedantic)