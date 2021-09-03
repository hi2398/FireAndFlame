//
// Created by Ashty on 06.07.2021.
//
#include "../Global.h"
#include "AreaOne.h"
#include "../Data/Enemies/Fly.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Enemies/Saugi.h"
#include "../Data/Enemies/SpiderBot.h"
#include "../Data/Enemies/SpringHog.h"
#include "../Data/Enemies/ToastCat.h"
#include "../Data/Deathzone.h"

AreaOne::AreaOne(SceneEnums lastScene) : Scene(SceneEnums::AreaOne) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition({19*32, 107 * 32});
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Area_One_Tilemap.json");
    Vector2 tempVec= {47*25,29*26};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::MinerBoss, sceneName));

    tempVec = {64*32,103*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Low));
    tempVec = {76*32,100*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Low));
    tempVec = {50*32,67*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Low));
    tempVec = {57*32,42*32};
    enemies.emplace_back(std::make_unique<Fly>(tempVec,EnemyLevel::Low));
    tempVec = {80*32,84*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {83*32,84*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {48*32,69*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {53*32,69*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {59*32,69*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {87*32,26*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec,EnemyLevel::Low));
    tempVec = {66*32,89*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {43*32,80*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {52*32,69*32};
    enemies.emplace_back(std::make_unique<Saugi>(tempVec));
    tempVec = {57*32,107*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Low));
    tempVec = {75*32,67*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Low));
    tempVec = {69*32,50*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Low));
    tempVec = {54*32,44*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Low));
    tempVec = {66*32,54*32};
    enemies.emplace_back(std::make_unique<SpiderBot>(tempVec,EnemyLevel::Low));
    tempVec = {77*32,38*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {75*32,84*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {63*32,84*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {62*32,48*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {77*32,26*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {69*32,26*32};
    enemies.emplace_back(std::make_unique<SpringHog>(tempVec,EnemyLevel::Low));
    tempVec = {73*32,84*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {61*32,84*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));
    tempVec = {74*32,38*32};
    enemies.emplace_back(std::make_unique<ToastCat>(tempVec));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));


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

    soundManager->PlayTrack(TRACK::AREA_ONE);
}

void AreaOne::Update() {
    soundManager->UpdateTrack(TRACK::AREA_ONE);
    Scene::Update();
}

void AreaOne::Draw() {
    
}