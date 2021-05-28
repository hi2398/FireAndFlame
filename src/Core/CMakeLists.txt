cmake_minimum_required(VERSION 3.11)
add_executable(Core Object.h Object.cpp ObjectTypes.h Actor.cpp Actor.h Component.cpp Component.h PlayerCharacter.cpp
        PlayerCharacter.h Enemy.cpp Enemy.h Interactable.cpp Interactable.h SceneManager.cpp SceneManager.h GameMode.cpp GameMode.h HUD.cpp HUD.h)