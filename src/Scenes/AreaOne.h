#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"

class AreaOne : public Scene {
public:
    AreaOne();
    void Update() override;
    void Draw() override;
    ~AreaOne() override= default;
private:
protected:
};

