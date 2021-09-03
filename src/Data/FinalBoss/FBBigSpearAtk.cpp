//
// Created by Ashty on 26.07.2021.
//

#include "FBBigSpearAtk.h"
#include "../../Global.h"
#include "SpearAttack.h"
#include "FBIdleDown.h"
#include "EnergyAttack.h"
#include "FinalBossEnemy.h"

FBBigSpearAtk::FBBigSpearAtk() {
    Vector2 tempVec = {89*32,73*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {101*32,73*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {92*32,71*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {98*32,71*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {90*32,76*32};
    sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    tempVec = {100*32,76*32};
    sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    activeFrame = {320,192,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBBigSpearAtk::Update(Actor &actor) {
    --attackCounter;
    if(attackCounter <= 0 && !secondAttack){
        Vector2 tempVec = {89*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {101*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {89*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {101*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        secondAttack = true;
    }
    if(attackCounter<=-60){
        return std::make_unique<FBIdleDown>();
    }
    return shared_from_this();
}

void FBBigSpearAtk::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}
