//
// Created by Ashty on 26.07.2021.
//

#include "FBEnergyAtk.h"
#include "../../Global.h"
#include "EnergyAttack.h"
#include "FBIdleFly.h"
#include "FinalBossEnemy.h"

FBEnergyAtk::FBEnergyAtk() {
    soundManager->PlaySfx(SFX::FB_SPEECH1);
    activeFrame = {0,0,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

std::shared_ptr<State> FBEnergyAtk::Update(Actor &actor) {
    --attackCounter;
    Vector2 tempVec;
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
    if(attackCounter == 150){
        Vector2 tempVec = {89*32,73*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter == 100){
        Vector2 tempVec = {92*32,73*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter == 50){
        Vector2 tempVec = {98*32,73*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter == 0){
        Vector2 tempVec = {102*32,73*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter == -50){
        Vector2 tempVec = {106*32,76*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter == -100){
        Vector2 tempVec = {85*32,76*32};
        sceneManager->AddInteractable(std::make_unique<EnergyAttack>(tempVec));
    }
    if(attackCounter <= -120){
        return std::make_shared<FBIdleFly>();
    }
    return shared_from_this();;
}

void FBEnergyAtk::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}
