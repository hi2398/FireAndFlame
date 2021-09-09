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
#include "../Data/Spawner.h"
#include "../Data/Speechbubble.h"


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
    std::vector<std::unique_ptr<Spawner>> spawner;

    Texture2D npc1Tex;
    Texture2D npc2Tex;
    Texture2D npc3Tex;
    Texture2D npc4Tex;
    Texture2D npc5Tex;

    Vector2 npc1Pos = { 28 * 32,96 * 32 };
    Vector2 npc2Pos = { 54 * 32,95 * 32 };
    Vector2 npc3Pos = { 57.5 * 32 ,102 * 32 };
    Vector2 npc4Pos = { 87.5 * 32,102 * 32 };
    Vector2 npc5Pos = { 65 * 32,111 * 32 };
    std::vector<std::unique_ptr<Speechbubble>> speech;
};
