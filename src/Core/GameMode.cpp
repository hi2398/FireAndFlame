//
// Created by Adrian on 28/05/2021.
//

#include "GameMode.h"

#include <utility>

GameMode::GameMode(std::unique_ptr<PlayerCharacter> playerCharacter, std::unique_ptr<PlayerController> playerController,
                   std::unique_ptr<HUD> hud) : playerCharacter(std::move(playerCharacter)), playerController(std::move(playerController)), hud(std::move(hud)) {

}

const std::shared_ptr<PlayerCharacter> &GameMode::GetPlayerCharacter() const {
    return playerCharacter;
}

const std::shared_ptr<PlayerController> &GameMode::GetPlayerController() const {
    return playerController;
}

const std::shared_ptr<HUD> &GameMode::GetHud() const {
    return hud;
}

