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


class AreaOne : public Scene {
public:
    AreaOne(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~AreaOne() override = default;
private:
    std::vector<std::unique_ptr<Spawner>> spawner;
    Texture2D sceneChanger;
    Vector2 sceneChangerVec;
protected:
};

