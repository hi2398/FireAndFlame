#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"
#include "../Data/SceneChangerObject.h"

class AreaThree : public Scene {
public:
    AreaThree(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~AreaThree() override= default;
private:
    const Vector2 playerStart = {23*32,112*32};
protected:
};