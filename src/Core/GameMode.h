#pragma once
#include "PlayerCharacter.h"
#include "HUD.h"


class GameMode {
public:
    GameMode(std::shared_ptr<PlayerCharacter> playerCharacter, std::shared_ptr<HUD> hud);
    std::shared_ptr<PlayerCharacter> GetPlayerCharacter();

    virtual ~GameMode() = default;

protected:

private:
    std::shared_ptr<PlayerCharacter> playerCharacter;
    std::shared_ptr<HUD> hud;

};


