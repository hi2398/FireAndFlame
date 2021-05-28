#pragma once
#include "PlayerCharacter.h"
#include "PlayerController.h"
#include "HUD.h"


class GameMode {
public:
    GameMode(std::shared_ptr<PlayerCharacter> playerCharacter, std::shared_ptr<PlayerController> playerController, std::shared_ptr<HUD> hud);

    const std::shared_ptr<PlayerCharacter> &getPlayerCharacter() const;

    const std::shared_ptr<PlayerController> &getPlayerController() const;

    const std::shared_ptr<HUD> &getHud() const;

    virtual ~GameMode() = default;

protected:

private:
    std::shared_ptr<PlayerCharacter> playerCharacter;
    std::shared_ptr<PlayerController> playerController;
    std::shared_ptr<HUD> hud;

};


