#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"
#include "../Data/SceneChangerObject.h"

class AreaTwo : public Scene {
public:
    AreaTwo();
    void Update() override;
    void Draw() override;
    ~AreaTwo() override= default;
private:
    const Vector2 playerStart = {115*32,114*32};
protected:
};

