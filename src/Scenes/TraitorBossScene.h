#pragma once
#include "../Data/Spawner.h"
#include "../Core/Scene.h"


class TraitorBossScene : public Scene {
public:
    TraitorBossScene(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~TraitorBossScene() override;

protected:


private:
    void CheckBossDeath();
    const Vector2 playerStart{26*32, 104*32};
    bool bossActivated{ false };
    bool bossDefeated{ false };
    static constexpr Vector2 bossSpawn = { 61 * 32, 81 * 32 };

    Vector2 door1[2];
    Vector2 door2[2];
    bool doorActive{ false };

    std::vector<std::unique_ptr<Spawner>> spawner;

    Texture2D sceneChanger;
    Vector2 sceneChangerVec;

    const Vector2 checkpointA{42*32, 88*32};
    const Vector2 checkpointB{75*32, 88*32};

    Music track;
    bool musicStarted{ false };
};
