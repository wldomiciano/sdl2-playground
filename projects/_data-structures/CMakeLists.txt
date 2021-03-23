get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(data_structures src/main.c src/array.c src/list.c)

target_link_libraries(data_structures)

target_compile_options(data_structures PRIVATE -Wall -Wextra -Wpedantic)

target_include_directories(data_structures PRIVATE include)
