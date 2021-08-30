#pragma once

#include "../Core/Scene.h"

class MinerBossScene : public Scene {
public:
    MinerBossScene(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~MinerBossScene() override = default;

    void EnableDebrisLower();
    void EnableDebrisUpper();

protected:


private:
    const Vector2 playerStart{27*32, 90*32};
    const Vector2 bossStart{55*32, 90*32};
    bool bossActivated{false};
    bool lowerDebrisEnabled{false};
    bool upperDebrisEnabled{false};
    Texture2D debrisTexture;
    Vector2 lowerDebrisLoc{57*32, 90*32};
    Vector2 upperDebrisLocA{51*32, 60*32};
    Vector2 upperDebrisLocB{52*32, 60*32};
    Vector2 upperDebrisLocC{53*32, 60*32};
    Vector2 upperDebrisLocD{54*32, 60*32};
    Vector2 upperDebrisLocE{55*32, 60*32};

};


