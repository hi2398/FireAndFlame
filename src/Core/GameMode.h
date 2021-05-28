#pragma once
#include "PlayerCharacter.h"
#include "PlayerController.h"
#include "HUD.h"


class GameMode {
public:
    GameMode(std::shared_ptr<PlayerCharacter> playerCharacter, std::shared_ptr<PlayerController> playerController, std::shared_ptr<HUD> hud);
    GameMode() = delete;
    [[nodiscard]] const std::shared_ptr<PlayerCharacter> &GetPlayerCharacter() const;
    [[nodiscard]] const std::shared_ptr<PlayerController> &GetPlayerController() const;
    [[nodiscard]] const std::shared_ptr<HUD> &GetHud() const;
    virtual ~GameMode() = default;

protected:

private:
    std::shared_ptr<PlayerCharacter> playerCharacter;
    std::shared_ptr<PlayerController> playerController;
    std::shared_ptr<HUD> hud;

};


