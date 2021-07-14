#pragma once

#include "../Core/Scene.h"

class IceBossScene : public Scene {
public:

    IceBossScene();
    void Update() override;
    void Draw() override;
    ~IceBossScene() override = default;

protected:


private:
static constexpr Vector2 playerStart{20*32, 37*32};

};


