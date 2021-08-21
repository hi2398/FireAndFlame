
#include "AreaTwo.h"

AreaTwo::AreaTwo(){
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Two_Tilemap.json");
    Vector2 tempVec= {96*32,46*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::TraitorBoss));

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaTwo/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaTwo/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaTwo/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaTwo/background.png");

    foregroundPos = { 0,0 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 10;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 5;
    foregroundLoopY = 9;
    foregroundException = 8;
}

void AreaTwo::Update() {
    Scene::Update();
}

void AreaTwo::Draw() {

}
