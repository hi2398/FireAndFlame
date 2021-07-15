#pragma once

#include "../Core/Scene.h"
#include "../Data/IceBoss/IceBoss.h"

struct Blockade {
    Vector2 location;
    Texture2D texture;
    float rotation;
};

class IceBossScene : public Scene {
public:

    IceBossScene();
    void Update() override;
    void Draw() override;
    ~IceBossScene() override = default;

protected:


private:
    static constexpr Vector2 playerStart{20*32, 39*32};
    bool IsBossAlive();
    bool bossActivated{false};
    bool bossDefeated{false};
    static constexpr Rectangle bossSpawnTrigger{26*32, 32*32, 6*32, 6*32};
    static constexpr Vector2 bossSpawnPoint{33*32, 33*32};
    //offset entrance blockade location down because rotation pulls texture upwards
    Blockade entrance{20*32, 37*32+32,LoadTexture("assets/Bosses/IceBoss/Ice_Barrier.png"), -90.f};
    Blockade exit {38*32, 35*32,LoadTexture("assets/Bosses/IceBoss/Ice_Barrier.png"), 0.f};
};


