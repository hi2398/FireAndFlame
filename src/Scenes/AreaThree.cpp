
#include "AreaThree.h"
#include "../Data/Enemies/Fly.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Enemies/Saugi.h"
#include "../Data/Enemies/SpiderBot.h"
#include "../Data/Enemies/SpringHog.h"
#include "../Data/Enemies/ToastCat.h"
#include "../Data/Enemies/Howler.h"
#include "../Data/Deathzone.h"

AreaThree::AreaThree(SceneEnums lastScene) : Scene(SceneEnums::AreaThree) {
    this->lastScene = lastScene;
    playerCharacter->SetHealth(100);
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Three_Tilemap.json");
    Vector2 tempVec= {80*25,24*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::FinalBoss, sceneName));

    tempVec = {50*32,96*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {58*32,92*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {65*32,92*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {81*32,89*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::High));
    tempVec = {39*32,112*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {48*32,55*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {51*32,55*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Medium));
    tempVec = {47*32,99*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::High));
    tempVec = {88*32,77*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::High));
    tempVec = {81*32,89*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {81*32,89*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {73*32,90*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {64*32,71*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {43*32,68*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {91*32,89*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {52*32,68*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

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

    soundManager->PlayTrack(TRACK::AREA_THREE);
}

void AreaThree::Update() {
    Scene::Update();
    soundManager->UpdateTrack(TRACK::AREA_THREE);
}

void AreaThree::Draw() {

}
