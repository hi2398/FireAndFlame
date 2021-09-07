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
    textureRec={};
    currentAttackTimer=attackTimer;
}

std::shared_ptr<EState> MBRangedState::Update(Enemy &enemy) {
    if (windup){
        return Windup(enemy);
    } else {
        return Attack(enemy);
    }
}

void MBRangedState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture(), textureRec);
    if (!windup){
        minerBoss.DrawDirectional({currentAttackCenter.x-16, currentAttackCenter.y-16}, minerBoss.GetTexture(), throwRec);
    }
}

std::shared_ptr<EState> MBRangedState::Attack(Enemy& enemy) {
    --timer;
    currentAttackCenter = Vector2Lerp(attackStart, attackEnd, 1.f-timer/startTimer);
    if (returning){
        if (timer<=10){
            throwRec={192, 64,32, 32};
        }else if (timer<=20){
            throwRec={224, 64,32, 32};
        } else if (timer<=30){
        throwRec={256, 64,32, 32};
        }else {
            throwRec={288, 64,32, 32};
        }
    } else {
        if (timer<=10){
            throwRec={288, 64,32, 32};
        }else if (timer<=20){
            throwRec={256, 64,32, 32};
        } else if (timer<=30){
            throwRec={224, 64,32, 32};
        }else {
            throwRec={192, 64,32, 32};
        }
    }

    if (!playerCharacter->IsInvulnerable()){
        if (CheckCollisionCircleRec(currentAttackCenter, dmgRadius, playerCharacter->playerHitbox)){
            playerCharacter->SetHealth(playerCharacter->GetHealth()-dmg);
            playerCharacter->SetInvulnerable(true);
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

std::shared_ptr<EState> MBRangedState::Windup(Enemy &enemy) {
    --currentAttackTimer;
    if (currentAttackTimer<=15){
        textureRec={160, 64,32, 32};
    }else if (currentAttackTimer<=30){
        textureRec={128, 64,32, 32};
    } else {
        textureRec={96, 64,32, 32};
    }
    if (currentAttackTimer==0){
        throwRec={192, 64,32, 32};
        windup=false;
    }
    return shared_from_this();
}
