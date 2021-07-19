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

    static constexpr Rectangle healthDecreasingCollider = {40*32,45*32,128,128}; // If player collides he will start losing health

    Vector2 door1[2];
    bool door1Active = true;
    bool tutorial1 = false;
    int attackCounter = 0;
    int attackTicker = 123;
    Rectangle tutorial1Trigger = {67*32,75*32,32,64};

    Vector2 door2[2];
    bool door2Active = true;
    bool tutorial2 = false;
    int heavyAttackTicker = 0;
    Rectangle tutorial2Trigger = {58*32,75*32,32,64};

    Vector2 door3[2];
    bool door3Active = true;
    bool tutorial3 = false;
    Rectangle tutorial3Trigger = {49*32,75*32,32,64};

protected:
};