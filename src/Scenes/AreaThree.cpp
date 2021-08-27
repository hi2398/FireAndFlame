
#include "AreaThree.h"

AreaThree::AreaThree(SceneEnums lastScene) : Scene(SceneEnums::AreaThree) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Three_Tilemap.json");
    Vector2 tempVec= {80*25,24*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::FinalBoss, sceneName));

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/AreaThree/Upper_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/AreaThree/Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/AreaThree/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/AreaThree/background.png");

    foregroundPos = { 0,1100 };
    backgroundPos = { 0,0 };

    //fill background loop vector
    backgroundLoopX = 10;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 5;
    foregroundLoopY = 9;
    foregroundException = 0;

    //example for weathereffect
    sceneEffectActivated = true;
    sceneEffect = LoadTexture("assets/graphics/backgrounds/AreaThree/ash.png");
    effectPos1Start = { 0,0 };
    effectPos2Start = {0, -400 * 3};
    effectPos1 = effectPos1Start;
    effectPos2 = effectPos2Start;
}

void AreaThree::Update() {
    Scene::Update();
}

void AreaThree::Draw() {

}
