#pragma once
#include "../Core/Scene.h"
#include "raylib.h"
#include "../Core/Enemy.h"
#include "../Data/Coal.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/DialogObject.h"
#include <vector>
#include "../Core/Tilemap.h"
#include "../Core/Actor.h"



class NeutralArea : public Scene {
public:
    NeutralArea();
 
    void Update() override;
    void Draw() override;
    ~NeutralArea() override = default;


protected:
    
private:
    Rectangle exp = { 0 };


    
    Rectangle ground = { -1000, 40, 2100, 300};
    int coalTimer=30;
    int generalTimer = 0;
};
