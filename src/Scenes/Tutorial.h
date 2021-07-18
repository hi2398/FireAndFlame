#pragma once
#include "../Core/Scene.h"

class Tutorial : public Scene {
public:
    Tutorial();

    void Update() override;

    void Draw() override;

    ~Tutorial() override = default;

private:
    bool preventHealthDecrease = true;

    Texture2D npc1Tex;
    Texture2D npc2Tex;
    Vector2 npc1Pos = {35*32,99*32};
    Vector2 npc2Pos = {81*32,76*32};
    Vector2 npc3Pos = {65*32,76*32};
    Vector2 npc4Pos = {56*32,76*32};
    Vector2 npc5Pos = {47*32,76*32};
    static constexpr Vector2 playerStart{ 32 * 32, 99 * 32 };

protected:
};