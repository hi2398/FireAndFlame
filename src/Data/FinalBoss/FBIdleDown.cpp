//
// Created by Ashty on 26.07.2021.
//

#include "FBIdleDown.h"
#include "FBBigSpearAtk.h"
#include "FBSpawnEDown.h"
#include "../../Global.h"
#include "BossRangedAttack.h"
#include "FinalBossEnemy.h"
#include "FBBossDying.h"

FBIdleDown::FBIdleDown() {

}

std::shared_ptr<State> FBIdleDown::Update(Actor &actor) {
    actor.SetPosition({94*32,76*32});
    FinalBossEnemy& boss = dynamic_cast<FinalBossEnemy&>(actor);
    if(boss.GetHealth() <= 0){
        return std::make_unique<FBBossDying>();
    }
    if(decideCounter <= 0){
        if(playerCharacter->GetHealth() <= 25){
            return std::make_shared<FBSpawnEDown>();
        }
        return std::make_unique<FBBigSpearAtk>();
    }
    if(attackCounter<=0){
        if(playerCharacter->GetPosition().y >= actor.GetPosition().y){
            Vector2 tempVec = actor.GetPosition();
            if(playerCharacter->GetPosition().x > actor.GetPosition().x){
                tempVec.x = tempVec.x + 300;
                boss.ChangeSwordPosition(tempVec);
            }else{
                tempVec.x = tempVec.x - 300;
                boss.ChangeSwordPosition(tempVec);
            }
            std::cout <<"SWORD";
        }
        else sceneManager->AddInteractable(std::make_unique<BossRangedAttack>(actor.GetPosition()));
        attackCounter = 120;
    }else attackCounter--;
    --decideCounter;
    return shared_from_this();;
}

void FBIdleDown::Draw(Actor &actor) {

}
