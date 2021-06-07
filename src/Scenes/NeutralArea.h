#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include <vector>

class NeutralArea : public Scene {
public:
    NeutralArea();
    void Update() override;
    void Draw() override;
    ~NeutralArea() override = default;

protected:

private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    Rectangle ground = { -1000, 40, 2100, 300};
};

