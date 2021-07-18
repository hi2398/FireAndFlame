#pragma once
#include "../Core/Scene.h"

class Tutorial : public Scene {
public:
    Tutorial();

    void Update() override;

    void Draw() override;

    ~Tutorial() override = default;

private:
    Texture2D npcTex;
    Vector2 npc1Pos = {34*32,99*32};
    static constexpr Vector2 playerStart{ 32 * 32, 99 * 32 };

protected:
};