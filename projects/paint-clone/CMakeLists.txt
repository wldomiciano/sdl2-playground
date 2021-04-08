get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(${directory_name} main.c game.c utils.c)

target_link_libraries(${directory_name} PRIVATE $<$<BOOL:MINGW>:mingw32> SDL2::SDL2main SDL2::SDL2-static)
