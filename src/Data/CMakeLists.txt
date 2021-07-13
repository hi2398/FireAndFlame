cmake_minimum_required(VERSION 3.11)

add_subdirectory(Player)
add_subdirectory(Enemies)
add_library(Data STATIC Coal.h Coal.cpp HUD.h HUD.cpp SceneChangerObject.cpp SceneChangerObject.h DialogObject.cpp DialogObject.h)
target_link_libraries(Data raylib Core Player Scenes Observer Enemies)