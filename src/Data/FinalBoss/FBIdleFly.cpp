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

FBIdleFly::FBIdleFly() {

}

std::shared_ptr<State> FBIdleFly::Update(Actor &actor) {
    if(decideCounter <= 0){
        if(playerCharacter->GetHealth() <= 25){
            return std::make_shared<FBFlyDown>();
        }
        int randomVal = GetRandomValue(0,1);
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
