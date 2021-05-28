//
// Created by Adrian on 28/05/2021.
//

#include "GameMode.h"

#include <utility>

GameMode::GameMode(std::shared_ptr<PlayerCharacter> playerCharacter, std::shared_ptr<PlayerController> playerController,
                   std::shared_ptr<HUD> hud) : playerCharacter(std::move(playerCharacter)), playerController(std::move(playerController)), hud(std::move(hud)) {

}

std::shared_ptr<PlayerCharacter> GameMode::GetPlayerCharacter() const {
    return playerCharacter;
}

std::shared_ptr<PlayerController> GameMode::getPlayerController() const {
    return playerController;
}

std::shared_ptr<HUD> GameMode::getHud() const {
    return hud;
}
