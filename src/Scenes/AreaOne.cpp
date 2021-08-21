//
// Created by Ashty on 06.07.2021.
//

#include "AreaOne.h"

AreaOne::AreaOne(){
    playerCharacter->SetPosition({19*32, 107 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_One_Tilemap.json");
    Vector2 tempVec= {47*25,29*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::MinerBoss));


    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaOne/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaOne/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaOne/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaOne/background.png");

    foregroundPos = { 0,-100 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 8;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 4;
    foregroundLoopY = 9;
    foregroundException = 8;
}

void AreaOne::Update() {
    Scene::Update();
}

void AreaOne::Draw() {
    
}
