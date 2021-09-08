#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/DialogueObject.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"



class NeutralArea : public Scene {
public:
    NeutralArea(SceneEnums lastScene);
 
    void Update() override;
    void Draw() override;
    ~NeutralArea() override = default;


protected:
    
private:
    Rectangle exp = { 0 };
    static constexpr Vector2 playerStart{ 59 * 32, 111 * 32 };
    Texture2D sceneChanger;
    Vector2 sceneChangerVec1;
    Vector2 sceneChangerVec2;
    Rectangle sceneChangerFrame1;
    Rectangle sceneChangerFrame2;
    bool activateShake = false;

    const Vector2 checkpointA{61*32, 102*32};
};
