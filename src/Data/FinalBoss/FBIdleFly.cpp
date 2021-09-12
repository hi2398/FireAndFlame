//
// Created by Ashty on 26.07.2021.
//

#include "FBIdleFly.h"
#include "FBSpearAtk.h"
#include "FBSwordAtk.h"
#include "FBEnergyAtk.h"
#include "FBFlyDown.h"
#include <iostream>
#include "../../Global.h"
#include "FinalBossEnemy.h"
#include "FBChangeStates.h"

FBIdleFly::FBIdleFly() {
    activeFrame = {0,0,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBIdleFly::Update(Actor &actor) {
    actor.SetPosition({94*32,73*32});
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    if(counter == 0){
        counter = 40;
        switch ((int)activeFrame.x) {
            case 0: activeFrame = {64,0,64,64};
                break;
            case 32: activeFrame = {128,0,64,64};
                break;
            case 64: activeFrame = {0,0,64,64};
                break;
            default:
                break;

        }
    }else {counter--;}
    if(boss.GetHealth()<= 20){
        return std::make_shared<FBChangeStates>();
    }
    if(decideCounter <= 0){
        if(playerCharacter->GetHealth() <= 25){
            return std::make_shared<FBFlyDown>();
        }
        int randomVal = GetRandomValue(0,2);
        switch (randomVal) {
            case 0: return std::make_shared<FBSpearAtk>();
            case 1: return std::make_shared<FBEnergyAtk>();
            case 2: return std::make_shared<FBSwordAtk>();
            default: std::cout << "ERROR IN FBIdleFly.cpp";
        }
    }
    --decideCounter;
    return shared_from_this();;
}


void FBIdleFly::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}

FBIdleFly::~FBIdleFly()
{
    UnloadTexture(bossMap);
}
