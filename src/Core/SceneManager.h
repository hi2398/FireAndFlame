#pragma once
#include <memory>
#include "Scene.h"
#include "PlayerCharacter.h"
#include "PlayerController.h"
#include "HUD.h"
#include "BackgroundManager.h"

extern std::shared_ptr<PlayerCharacter> playerCharacter;
extern std::shared_ptr<PlayerController> playerController;
extern std::shared_ptr<HUD> hud;


class SceneManager {
public:
    explicit SceneManager(std::shared_ptr<Scene> initialScene);
    void Tick();
    void SetNextScene(std::unique_ptr<Scene> nextScene);
    void SceneParallax(int direction);

protected:

private:
    std::shared_ptr<Scene> activeScene;
    std::shared_ptr<Scene> nextScene;
    std::shared_ptr<BackgroundManager> background = std::make_shared<BackgroundManager>();
};


