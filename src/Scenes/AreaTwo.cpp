
#include "AreaTwo.h"
#include "../Data/Enemies/Fly.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Enemies/Saugi.h"
#include "../Data/Enemies/SpiderBot.h"
#include "../Data/Enemies/SpringHog.h"
#include "../Data/Enemies/ToastCat.h"
#include "../Data/Enemies/Howler.h"
#include "../Data/Deathzone.h"

AreaTwo::AreaTwo(SceneEnums lastScene) : Scene(SceneEnums::AreaTwo) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_Two_Tilemap.json");
    Vector2 tempVec= {96*32,46*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::TraitorBoss, sceneName));

    tempVec = {66*32,102*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {57*32,102*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {52*32,71*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {66*32,72*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {71*32,57*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Medium));
    tempVec = {40*32,99*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {96*32,88*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {88*32,76*32};
    enemies.emplace_back(std::make_unique<Howler>(tempVec,EnemyLevel::Low));
    tempVec = {77*32,110*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {73*32,103*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {85*32,76*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Medium));
    tempVec = {71*32,103*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {39*32,99*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {62*32,103*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {69*32,90*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Medium));
    tempVec = {92*32,112*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {51*32,90*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Medium));
    tempVec = {101*32,112*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {51*32,90*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

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
