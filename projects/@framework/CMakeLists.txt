get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_library(framework framework.c)

target_link_libraries(framework ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

target_compile_options(framework PRIVATE -Wall -Wextra -Wpedantic)
