#pragma once
#include "PlayerCharacter.h"
#include "PlayerController.h"
#include "HUD.h"


class GameMode {
public:
    GameMode(std::unique_ptr<PlayerCharacter> playerCharacter, std::unique_ptr<PlayerController> playerController, std::unique_ptr<HUD> hud);
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


