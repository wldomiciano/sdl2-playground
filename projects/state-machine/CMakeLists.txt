get_filename_component(directory_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

add_executable(
  ${directory_name}
    main.c
    SceneManager.c
    scene1.c
    scene2.c
    scene3.c
    window.c
)

target_link_libraries(${directory_name} PRIVATE $<$<BOOL:${MINGW}>:mingw32> tinyframework)

