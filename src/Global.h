#pragma once
#include "Core/SceneManager.h"

extern std::shared_ptr<PlayerCharacter> playerCharacter;
extern std::shared_ptr<PlayerController> playerController;
extern std::shared_ptr<HUD> hud;
extern std::shared_ptr<SceneManager> sceneManager;

constexpr bool DEBUG_BUILD = true;
constexpr bool DEBUG_PLAYER_STATES = false;
constexpr bool DEBUG_ENEMY_STATES = false;
constexpr bool DEBUG_PLAYER_POSITION = false;

/*
 * Example Usage, also see main.cpp:
 * if  constexpr(DEBUG_BUILD){ //<-constexpr ensures compile-time evaluation
 * std::cout << "\n=============================\n";
 * std::cout << "\n=====DEBUG BUILD ENABLED=====\n";
 * std::cout << "\n=============================\n";
 * }
 */
