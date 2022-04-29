cmake_minimum_required(VERSION 3.11)

add_library(scenes STATIC scenes.h menu_scene.h menu_scene.cpp game_scene.h game_scene.cpp pause_scene.cpp pause_scene.h)

target_include_directories(scenes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(scenes raylib raylib_cpp core)
