cmake_minimum_required(VERSION 3.11)

add_subdirectory(Observer)
add_library(Core STATIC Object.h Object.cpp ObjectTypes.h Actor.cpp Actor.h
        Interactable.cpp Interactable.h SceneManager.cpp SceneManager.h PlayerController.cpp PlayerController.h Scene.cpp
        Scene.h BackgroundManager.h BackgroundManager.cpp Tilemap.h Tilemap.cpp State.h DialogueManager.cpp DialogueManager.h Enemy.h Enemy.cpp "EState.h" "EState.cpp" "PlayerStates.h" "PlayerStates.cpp")
target_link_libraries(Core raylib Observer Player Scenes Data Enemies)
