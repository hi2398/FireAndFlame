cmake_minimum_required(VERSION 3.11)

add_subdirectory(Observer)
add_library(Core STATIC Object.h Object.cpp ObjectTypes.h Actor.cpp Actor.h Component.cpp Component.h Enemy.cpp Enemy.h
        Interactable.cpp Interactable.h SceneManager.cpp SceneManager.h PlayerController.cpp PlayerController.h Scene.cpp
        Scene.h BackgroundManager.h BackgroundManager.cpp Tilemap.h Tilemap.cpp)
target_link_libraries(Core raylib Observer)