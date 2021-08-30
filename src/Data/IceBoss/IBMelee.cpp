#include <iostream>
#include "IBMelee.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "../../Global.h"

IBMelee::IBMelee(Enemy& enemy) : EState(enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);

    //set rec to avoid buggy frame
    texRec={static_cast<float>(96*iceBoss->GetPhase()), 0, 32, 32};
}

std::shared_ptr<EState> IBMelee::Update(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);

    if (meleeTimer==0) return std::make_shared<IBSeek>(enemy);
    --meleeTimer;
    if (meleeTimer<=20){
        texRec={static_cast<float>(96*iceBoss->GetPhase()), 128, 64, 32};
        Vector2 attackCenter= {enemy.GetPosition().x + 16+32*enemy.GetDirection(), enemy.GetPosition().y + 16};
        DrawCircleV(attackCenter, attackCollisionRad, RED);
        if (CheckCollisionCircleRec(attackCenter, attackCollisionRad, playerCharacter->playerHitbox) && !playerHit) {
            playerCharacter->SetHealth(playerCharacter->GetHealth()-meleeDamage);
            playerHit=true;
        }
    } else if (meleeTimer<=40){
        texRec={static_cast<float>(96*iceBoss->GetPhase()), 96, 64, 32};
    } else {
        texRec={static_cast<float>(96*iceBoss->GetPhase()), 64, 64, 32};
    }


    //as long as melee attack isnt done, continue returning from this
    return shared_from_this();
}

void IBMelee::Draw(Enemy &enemy) {
    auto& iceBoss=dynamic_cast<IceBoss&>(enemy);
    Vector2 loc=iceBoss.GetPosition();
    if(iceBoss.GetDirection()==LEFT){
        loc.x-=32;
    }

    iceBoss.DrawDirectional(loc, iceBoss.GetTexture(), texRec);
}
