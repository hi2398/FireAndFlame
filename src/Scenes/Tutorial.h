#pragma once
#include "../Core/Scene.h"

class Tutorial : public Scene {
public:
    Tutorial();

    void Update() override;

    void Draw() override;

    ~Tutorial() override = default;

private:
    Texture2D npc1Tex;
    Vector2 npc1Pos = {35*32,99*32};
    Vector2 npc2Pos = {81*32,76*32};
    static constexpr Vector2 playerStart{ 32 * 32, 99 * 32 };

protected:
};