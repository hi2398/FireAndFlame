#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Core/Coal.h"
#include <vector>
#include "../Core/Tilemap.h"

class NeutralArea : public Scene {
public:
    NeutralArea() = default;
 
    void Update() override;
    void Draw() override;
    ~NeutralArea() override = default;

protected:

private:

    std::vector<std::shared_ptr<Enemy>> enemies;
    //std::vector<std::shared_ptr<Coal>> coals;
    std::shared_ptr<Coal>coals = std::make_shared<Coal>();
    std::unique_ptr<Tilemap> tilemap;
    Rectangle ground = { -1000, 40, 2100, 300};
    int coalTimer=30;
    int generalTimer = 0;

};

