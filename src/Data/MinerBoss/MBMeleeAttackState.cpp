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
    textureRec={0, 0, 32, 32};

}

std::shared_ptr<EState> MBMeleeAttackState::Update(Enemy &enemy) {


    if (inReach){
        return Attack(enemy);
    }
    return Approach(enemy);


}

void MBMeleeAttackState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);

    Vector2 drawPos=minerBoss.GetPosition();
    if (inReach){
        drawPos.y-=32;
        if (minerBoss.GetDirection()==LEFT){
            drawPos.x-=32;
        }
    }


    minerBoss.DrawDirectional(drawPos, minerBoss.GetTexture(), textureRec);



}

std::shared_ptr<EState> MBMeleeAttackState::Attack(Enemy &enemy) {
    --timer;
    if (timer==0) {
        return std::make_shared<MBDecisionState>(enemy);
    }


    if (timer==20){
        textureRec={160, 0, 64, 64};
    }
    if (timer==10){
        textureRec={224, 0, 64, 64};
    }

    Vector2 hitCenter=enemy.GetPosition();
    hitCenter.x+=16;
    hitCenter.y+=16;
    hitCenter.x+= enemy.GetDirection() * 32.f;
    if (!playerHit && CheckCollisionCircleRec(hitCenter, dmgRadius, playerCharacter->playerHitbox)){
        playerCharacter->SetHealth(playerCharacter->GetHealth()-meleeDamage);
        playerHit=true;
    }
    return shared_from_this();
}

std::shared_ptr<EState> MBMeleeAttackState::Approach(Enemy &enemy) {
    if (abs(playerCharacter->GetPosition().x-enemy.GetPosition().x)<=32){
        inReach=true;
        timer=30;
        textureRec={96, 0, 64, 64};
        return shared_from_this();
    }
    //determine direction to attack
    if ((playerCharacter->GetPosition().x-enemy.GetPosition().x) >=0){
        enemy.SetDirection(RIGHT);
    } else  {
        enemy.SetDirection(LEFT);
    }

    if (timer==30){
        textureRec={0, 0, 32, 32};
    }
    --timer;

    if (timer==20){
        textureRec={0, 32, 32, 32};
    }
    if (timer==10) {
        textureRec={0, 64, 32, 32};
    }
    if (timer==0){
        timer=30;
        textureRec={0, 0, 32, 32};
    }

    enemy.SetPosition({enemy.GetPosition().x+enemy.GetEnemyMovementSpeed()*enemy.GetDirection(), enemy.GetPosition().y});

    return shared_from_this();

}
