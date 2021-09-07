#pragma once

#include "../Core/Scene.h"
#include "../Data/Spawner.h"

class MinerBossScene : public Scene {
public:
    MinerBossScene(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~MinerBossScene() override = default;

    void EnableDebrisLower();
    void EnableDebrisUpper();
    void OnBossDeath();

protected:


private:
    const Vector2 playerStart{27*32, 90*32};
    const Vector2 bossStart{55*32, 90*32};
    bool bossActivated{false};
    bool lowerDebrisEnabled{false};
    bool upperDebrisEnabled{false};
    bool bossDefeated{false};
    Texture2D debrisTexture;
    Vector2 lowerDebrisLoc{57*32, 90*32};
    Vector2 upperDebrisLocA{51*32, 60*32};
    Vector2 upperDebrisLocB{52*32, 60*32};
    Vector2 upperDebrisLocC{53*32, 60*32};
    Vector2 upperDebrisLocD{54*32, 60*32};
    Vector2 upperDebrisLocE{55*32, 60*32};
    std::vector<std::unique_ptr<Spawner>> spawner;
    Texture2D bridge;
    Rectangle bridgeRec = {0,32 * 4, 32 * 5, 32};
    Texture2D sceneChanger;
    Vector2 sceneChangerVec;
};


