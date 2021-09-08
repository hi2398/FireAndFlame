#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/Spawner.h"

class AreaTwo : public Scene {
public:
    AreaTwo(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~AreaTwo() override= default;
protected:

private:
    const Vector2 playerStart = {115*32,114*32};
    std::vector<std::unique_ptr<Spawner>> spawner;
    Texture2D sceneChanger;
    Vector2 sceneChangerVec;

    const Vector2 checkpointA{106*32, 114*32};
    const Vector2 checkpointB{95*32, 88*32};
    const Vector2 checkpointC{96*32, 56*32};
};

