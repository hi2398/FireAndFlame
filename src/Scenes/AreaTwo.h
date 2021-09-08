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
    ~AreaTwo() override;
private:
    const Vector2 playerStart = {115*32,114*32};
    std::vector<std::unique_ptr<Spawner>> spawner;
    Texture2D sceneChanger;
    Vector2 sceneChangerVec;
    Music track;
protected:
};

