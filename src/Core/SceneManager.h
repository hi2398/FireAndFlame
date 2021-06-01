#pragma once
#include <memory>
#include "Scene.h"
#include "PlayerCharacter.h"
#include "PlayerController.h"
#include "HUD.h"
#include "../Global.h"

class SceneManager {
public:
    explicit SceneManager(std::shared_ptr<Scene> initialScene);
    void Tick();
    void SetNextScene(std::unique_ptr<Scene> nextScene);


protected:

private:
    std::shared_ptr<Scene> activeScene;
    std::shared_ptr<Scene> nextScene;
};


