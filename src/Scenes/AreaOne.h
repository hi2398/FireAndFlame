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

    ~AreaOne() override;

protected:


private:
    std::vector<std::unique_ptr<Spawner>> spawner;
    Texture2D sceneChanger;
    Vector2 sceneChangerVec;

    Music track;
  
    const Vector2 checkpointA{31*32, 107*32};
    const Vector2 checkpointB{44*32, 69*32};
    const Vector2 checkpointC{40*32, 26*32};

};

