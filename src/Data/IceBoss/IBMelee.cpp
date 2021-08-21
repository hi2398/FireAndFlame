#include <iostream>
#include "IBMelee.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "../../Global.h"

IBMelee::IBMelee(Enemy& enemy) : EState(enemy) {

}

std::shared_ptr<EState> IBMelee::Update(Enemy &enemy) {

    if (meleeTimer==0) return std::make_shared<IBSeek>(enemy);
    //TODO: melee
    --meleeTimer;
    Vector2 attackCenter= {enemy.GetPosition().x + 16 * enemy.GetDirection(), enemy.GetPosition().y + 16};
    if (CheckCollisionCircleRec(attackCenter, attackCollisionRad, playerCharacter->playerHitbox) && !playerHit) {
        playerCharacter->SetHealth(playerCharacter->GetHealth()-meleeDamage);
        playerHit=true;
    }
    //as long as melee attack isnt done, continue returning from this
    return shared_from_this();
}

void IBMelee::Draw(Enemy &enemy) {
    auto& iceBoss=dynamic_cast<IceBoss&>(enemy);
    iceBoss.DrawDirectional(iceBoss.GetPosition(), iceBoss.GetTexture());
}
