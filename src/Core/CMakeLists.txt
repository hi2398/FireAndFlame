cmake_minimum_required(VERSION 3.11)

add_library(Core STATIC Object.h Object.cpp ObjectTypes.h Actor.cpp Actor.h Component.cpp Component.h ../Data/PlayerCharacter.cpp
        ../Data/PlayerCharacter.h Enemy.cpp Enemy.h Interactable.cpp Interactable.h SceneManager.cpp SceneManager.h
        ../Data/HUD.cpp ../Data/HUD.h PlayerController.cpp PlayerController.h Scene.cpp Scene.h ../Data/Coal.h ../Data/Coal.cpp BackgroundManager.h BackgroundManager.cpp Tilemap.h Tilemap.cpp)
target_link_libraries(Core raylib)