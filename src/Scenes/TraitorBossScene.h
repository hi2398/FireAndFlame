#pragma once

#include "../Core/Scene.h"


class TraitorBossScene : public Scene {
public:
    TraitorBossScene(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~TraitorBossScene() override = default;

protected:


private:
    void CheckBossDeath();
    const Vector2 playerStart{26*32, 104*32};
    bool bossActivated{ false };
    bool bossDefeated{ false };
    static constexpr Vector2 bossSpawn = { 61 * 32, 88 * 32 };

    Vector2 door1[2];
    Vector2 door2[2];
    bool doorActive{ false };

    Sound doorSFX;

};
