#pragma once

#include "../Core/Scene.h"

class MinerBossScene : public Scene {
public:
    MinerBossScene(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~MinerBossScene() override = default;

protected:


private:
    const Vector2 playerStart{27*32, 90*32};
    const Vector2 bossStart{55*32, 90*32};

};


