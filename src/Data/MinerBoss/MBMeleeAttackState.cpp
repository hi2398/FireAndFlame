#include "MBMeleeAttackState.h"
#include "MinerBoss.h"
#include "../../Global.h"
#include "MBDecisionState.h"
#include "raymath.h"

MBMeleeAttackState::MBMeleeAttackState(Enemy &enemy) : EState(enemy) {
    if constexpr(DEBUG_ENEMY_STATES){
        std::cout << "Miner Boss State Transition to: Melee\n";
    }

    //determine direction to attack
    if ((playerCharacter->GetPosition().x-enemy.GetPosition().x) >=0){
        enemy.SetDirection(RIGHT);
    } else  {
        enemy.SetDirection(LEFT);
    }

}

std::shared_ptr<EState> MBMeleeAttackState::Update(Enemy &actor) {
    --timer;
    if (timer==0) {
        return std::make_shared<MBDecisionState>(actor);
    }

    Vector2 hitCenter=actor.GetPosition();
    hitCenter.x+=16;
    hitCenter.y+=16;
    hitCenter.x+=actor.GetDirection()*32.f;
    if (!playerHit && CheckCollisionCircleRec(hitCenter, dmgRadius, playerCharacter->playerHitbox)){
        playerCharacter->SetHealth(playerCharacter->GetHealth()-meleeDamage);
        playerHit=true;
        std::cout << "Player Hit\n";
    }

    return shared_from_this();
}

void MBMeleeAttackState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());


    Vector2 hitCenter=actor.GetPosition();
    hitCenter.x+=16;
    hitCenter.y+=16;
    hitCenter.x+=actor.GetDirection()*32.f;
    DrawCircleV(hitCenter, dmgRadius, RED);
}
