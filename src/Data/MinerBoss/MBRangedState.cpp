#include "MBRangedState.h"
#include "MinerBoss.h"
#include "MBDecisionState.h"
#include "../../Global.h"
#include "raymath.h"

MBRangedState::MBRangedState(Enemy &enemy) : EState(enemy) {
    if constexpr(DEBUG_ENEMY_STATES){
        std::cout << "Miner Boss State Transition to: Ranged\n";
    }
    //determine direction to attack
    if ((playerCharacter->GetPosition().x-enemy.GetPosition().x) >=0){
        enemy.SetDirection(RIGHT);
    } else  {
        enemy.SetDirection(LEFT);
    }

    attackStart=enemy.GetPosition();
    attackEnd=enemy.GetPosition();
    attackStart.x+=16;
    attackStart.y+=16;
    attackEnd.x+=(reach+16)*enemy.GetDirection();
    attackEnd.y+=16;

    timer=startTimer;
}

std::shared_ptr<EState> MBRangedState::Update(Enemy &enemy) {
    --timer;
    currentAttackCenter = Vector2Lerp(attackStart, attackEnd, 1.f-timer/startTimer);

    if (!playerHit){
        if (CheckCollisionCircleRec(currentAttackCenter, dmgRadius, playerCharacter->playerHitbox)){
            playerCharacter->SetHealth(playerCharacter->GetHealth()-dmg);
            playerHit = true;
        }
    }


    if (timer==0){

        if (!returning){
            std::swap(attackStart, attackEnd);
            timer = startTimer;
            returning = true;
        } else {
            return std::make_shared<MBDecisionState>(enemy);
        }
    }
    return shared_from_this();
}

void MBRangedState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
    DrawCircleV(currentAttackCenter, dmgRadius, RED);
}
