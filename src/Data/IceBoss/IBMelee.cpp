#include <iostream>
#include "IBMelee.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "../../Global.h"

IBMelee::IBMelee() {

}

std::shared_ptr<State> IBMelee::Update(Actor &actor) {

    if (meleeTimer==0) return std::make_shared<IBSeek>();
    //TODO: melee
    --meleeTimer;
    Vector2 attackCenter= {actor.GetPosition().x+16*actor.GetDirection(), actor.GetPosition().y+16};
    if (CheckCollisionCircleRec(attackCenter, attackCollisionRad, playerCharacter->playerHitbox) && !playerHit) {
        playerCharacter->SetHealth(playerCharacter->GetHealth()-meleeDamage);
        playerHit=true;
    }
    //as long as melee attack isnt done, continue returning from this
    return shared_from_this();
}

void IBMelee::Draw(Actor &actor) {
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    iceBoss.DrawDirectional(iceBoss.GetPosition(), iceBoss.GetMovingTexture());
}
