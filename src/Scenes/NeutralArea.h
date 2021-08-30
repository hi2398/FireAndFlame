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


};
