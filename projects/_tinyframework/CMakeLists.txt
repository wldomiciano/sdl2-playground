list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_library(
  tinyframework
    src/initialization.c
    src/context.c
    src/events.c
    src/sprite.c
    src/miscellaneous.c
    src/vector.c
)

target_link_libraries(tinyframework PUBLIC $<$<BOOL:MINGW>:mingw32> SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image)

target_include_directories(tinyframework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
