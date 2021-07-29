//
// Created by Ashty on 26.07.2021.
//

#include "FBSwordAtk.h"
#include "FBIdleFly.h"
#include "../../Global.h"
#include "BossEnergySwordAttack.h"

FBSwordAtk::FBSwordAtk() {
    Vector2 tempVec = {104*32,74*32};
    sceneManager->AddInteractable(std::make_unique<BossEnergySwordAttack>(tempVec,true,120));
    tempVec = {85*32,68*32};
    sceneManager->AddInteractable(std::make_unique<BossEnergySwordAttack>(tempVec,false,200));
}

std::shared_ptr<State> FBSwordAtk::Update(Actor &actor) {
    --decideCounter;
    if(decideCounter <= 0){
        return std::make_shared<FBIdleFly>();
    }
    return shared_from_this();;
}

void FBSwordAtk::Draw(Actor &actor) {

}
