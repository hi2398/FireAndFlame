//
// Created by Ashty on 26.07.2021.
//

#include "FBSpawnEDown.h"
#include "../../Global.h"
#include "../../Data/Enemies/Miner.h"
#include "FBIdleDown.h"
#include "FinalBossEnemy.h"

FBSpawnEDown::FBSpawnEDown() {
    Vector2 tempVec = {89*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {92*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {98*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {101*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    activeFrame = {320,192,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBSpawnEDown::Update(Actor &actor) {
    if(waitCounter <= 0){
        return std::make_shared<FBIdleDown>();
    }
    --waitCounter;
    return shared_from_this();
}

void FBSpawnEDown::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}
