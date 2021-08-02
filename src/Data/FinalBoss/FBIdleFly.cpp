//
// Created by Ashty on 26.07.2021.
//

#include "FBIdleFly.h"
#include "FBSpearAtk.h"
#include "FBSwordAtk.h"
#include "FBEnergyAtk.h"
#include "FBFlyDown.h"
#include "FBIdleDown.h"
#include <iostream>
#include "../../Global.h"
#include "FinalBossEnemy.h"

FBIdleFly::FBIdleFly() {
}

std::shared_ptr<State> FBIdleFly::Update(Actor &actor) {
    actor.SetPosition({94*32,73*32});
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    if(boss.GetHealth()<= 2){
        return std::make_shared<FBIdleDown>();
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

}