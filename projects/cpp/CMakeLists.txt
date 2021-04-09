get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(
  ${directory_name}
    src/main.cpp
    src/Window.cpp
)

target_include_directories(${directory_name} PRIVATE include)

target_link_libraries(
  ${directory_name}
    PRIVATE 
      $<$<BOOL:${MINGW}>:mingw32>
      SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image
)
