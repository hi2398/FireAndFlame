#pragma once
#include "../Core/Scene.h"

class DeathScreen : public Scene {
public:
    DeathScreen(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~DeathScreen() override = default;

private:
    Texture2D background;
protected:
    
};
