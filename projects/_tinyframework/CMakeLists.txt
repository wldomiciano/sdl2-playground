list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(
  tinyframework
    src/initialization.c
    src/context.c
    src/events.c
    src/sprite.c
    src/miscellaneous.c
    src/vector.c
)

target_link_libraries(tinyframework PRIVATE m ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})

target_include_directories(
  tinyframework
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${SDL2_INCLUDE_DIR}
      ${SDL2_TTF_INCLUDE_DIR}
      ${SDL2_IMAGE_INCLUDE_DIR}
)
