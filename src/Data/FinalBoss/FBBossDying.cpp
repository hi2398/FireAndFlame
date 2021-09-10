//
// Created by Ashty on 29.07.2021.
//

#include "FBBossDying.h"
#include "../../Global.h"
#include "FinalBossEnemy.h"
#include "../HitMarker.h"

FBBossDying::FBBossDying() {
    sceneManager->RemoveAllInteractables();
    sceneManager->GetActiveScene()->ToggleMusic();
    hud->IsBossFightActive(false);
    hud->executeEndscreenSwap();
    activeFrame = {320,192,64,64};
    bossMap = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
    sceneManager->ScreenShake(600);
}

std::shared_ptr<State> FBBossDying::Update(Actor &actor) {
    if(counter<=0){
        Vector2 tempVec;
        tempVec.x = GetRandomValue(actor.GetPosition().x,actor.GetPosition().x+32);
        tempVec.y = GetRandomValue(actor.GetPosition().y,actor.GetPosition().y+32);
        sceneManager->AddInteractable(std::make_unique<HitMarker>(tempVec));
    }else{counter--;}
    return shared_from_this();
}

void FBBossDying::Draw(Actor &actor) {
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    DrawTextureRec(bossMap,activeFrame,boss.GetPositionFix(),WHITE);
}