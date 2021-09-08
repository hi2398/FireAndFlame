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

class AreaThree : public Scene {
public:
    AreaThree(SceneEnums lastScene);
    void Update() override;
    void Draw() override;

    ~AreaThree() override;

protected:


private:
    const Vector2 playerStart = {23*32,112*32};
    std::vector<std::unique_ptr<Spawner>> spawner;

    Music track;
    
    const Vector2 checkpointA{28*32, 112*32};
    const Vector2 checkpointB{55*32, 55*32};

};