#pragma once

#include "../Core/Scene.h"

class TraitorBossScene : public Scene {
public:
    TraitorBossScene();
    void Update() override;
    void Draw() override;
    ~TraitorBossScene() override = default;

protected:


private:
    const Vector2 playerStart{26*32, 104*32};

};
