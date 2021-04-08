get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(${directory_name} framework.c game.c sprite.c)

target_link_libraries(${directory_name} PRIVATE $<$<BOOL:MINGW>:mingw32> SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image)
