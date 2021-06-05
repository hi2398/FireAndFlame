cmake_minimum_required(VERSION 3.11)

add_executable(Core Object.h Object.cpp ObjectTypes.h Actor.cpp Actor.h Component.cpp Component.h PlayerCharacter.cpp
        PlayerCharacter.h Enemy.cpp Enemy.h Interactable.cpp Interactable.h SceneManager.cpp SceneManager.h
         HUD.cpp HUD.h PlayerController.cpp PlayerController.h Scene.cpp Scene.h)
target_link_libraries(Core raylib)