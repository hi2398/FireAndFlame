cmake_minimum_required(VERSION 3.11)

add_subdirectory(Player)
add_subdirectory(IceBoss)
add_subdirectory(Enemies)
add_library(Data STATIC Coal.h Coal.cpp HUD.h HUD.cpp SceneChangerObject.cpp SceneChangerObject.h DialogueObject.cpp DialogueObject.h FinalBoss/SpearAttack.cpp FinalBoss/SpearAttack.h)
target_link_libraries(Data raylib Core Player Scenes Observer Enemies)