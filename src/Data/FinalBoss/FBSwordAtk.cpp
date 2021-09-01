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
    activeFrame = {0,0,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBSwordAtk::Update(Actor &actor) {
    --decideCounter;
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
    if(decideCounter <= 0){
        return std::make_shared<FBIdleFly>();
    }
    return shared_from_this();;
}

void FBSwordAtk::Draw(Actor &actor) {
    DrawTextureRec(bossMap,activeFrame,actor.GetPosition(),WHITE);
}
