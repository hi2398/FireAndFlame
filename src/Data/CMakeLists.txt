cmake_minimum_required(VERSION 3.11)

add_subdirectory(Player)
add_library(Data STATIC Coal.h Coal.cpp HUD.h HUD.cpp SceneChangerObject.cpp SceneChangerObject.h Miner.cpp Miner.h ToastCat.cpp ToastCat.h DialogueObject.cpp DialogueObject.h)
target_link_libraries(Data raylib Core Player Scenes Observer)