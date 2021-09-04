#include "IBSeek.h"
#include "IBMelee.h"
#include "IBRanged.h"
#include "IBMinions.h"
#include "../../Global.h"
#include "IceBoss.h"
#include "raymath.h"
#include <stdexcept>

IBSeek::IBSeek(Enemy &enemy) : EState(enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);

    //set rec to avoid buggy frame if returning to IBMinions instantly
    texRec={static_cast<float>(96*iceBoss->GetPhase()), 0, 32, 32};
}

std::shared_ptr<EState> IBSeek::Update(Enemy &enemy) {

    enemy.LookAtPlayer(); //while seeking, always look at player
    if (delay==0){
        if (nextAction==NextSeekAction::Decide){
            //if player health is under 50%, spawn minions with a chance, instantly switch state cause spawn point is fixed
            if (playerCharacter->GetHealth() < playerCharacter->GetMaxHealth()/2){
                if (IceBoss::Decide()) return std::make_shared<IBMinions>(enemy);
            }
            //for melee and ranged only set next action, then either move to player in this state for melee or move away for ranged
            if (IceBoss::Decide()) nextAction=NextSeekAction::Melee;
            else {
                nextAction=NextSeekAction::Ranged;
                //set next ranged spot based on distance
                if (Vector2Distance(enemy.GetPosition(), rightRangedSpot) < Vector2Distance(enemy.GetPosition(), leftRangedSpot)){
                    rangedSpot=&rightRangedSpot;
                } else {
                    rangedSpot=&leftRangedSpot;
                }
            }
        }

        //move to player for melee, move away for ranged
        switch (nextAction) {
            case NextSeekAction::Melee:
                //move to player to attack him
                return MeleeApproach(enemy);

                case NextSeekAction::Ranged:
                    //move away from player and shoot
                    return RangedMove(enemy);
                    case NextSeekAction::Decide: default:
                        throw std::logic_error("should not be able to reach this point in IBSeek");

        }
    }
    --delay;
    return shared_from_this();
}


void IBSeek::Draw(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    iceBoss->DrawDirectional(iceBoss->GetPosition(), iceBoss->GetTexture(), texRec);
}

std::shared_ptr<EState> IBSeek::MeleeApproach(Enemy& enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    AnimateWalk(iceBoss);


    //to avoid weird chases, if player is above boss, decide new
    if (enemy.GetPosition().y-playerCharacter->GetPosition().y>10 && abs(enemy.GetPosition().x-playerCharacter->GetPosition().x) <64) {
        nextAction=NextSeekAction::Decide;
        return shared_from_this();
    }

    //first, check in which direction the player is
    CalcWalkingDirection(enemy, playerCharacter->GetPosition());
    //if player is in range, attack him
    if (CheckCollisionRecs(playerCharacter->playerHitbox, iceBoss->GetMeleeRange())) {
        return std::make_shared<IBMelee>(enemy);
    }
    //else continue moving towards him
    float nextPosX = enemy.GetPosition().x+enemy.GetDirection()*IceBoss::SpeedMultiplier()*IceBoss::GetMovementSpeed();
    enemy.SetPosition({nextPosX, enemy.GetPosition().y});
    return shared_from_this();
}

std::shared_ptr<EState> IBSeek::RangedMove(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    AnimateWalk(iceBoss);


    //if the jump is finished, execute the ranged attack
    if (rangedTimer==0) return std::make_shared<IBRanged>(enemy.GetPosition(), enemy);

    //check if boss is at the jump spot
    if (Vector2Distance(enemy.GetPosition(), jumpStart) <= 20 && !jumpStarted){
        jumpStarted = true;
    } else {
        //if not, check which direction to walk in and move there
        CalcWalkingDirection(enemy, jumpStart);
        float nextPosX = enemy.GetPosition().x + enemy.GetDirection() * IceBoss::SpeedMultiplier() * IceBoss::GetMovementSpeed();
        enemy.SetPosition({nextPosX, enemy.GetPosition().y});
    }
    if (jumpStarted) { //jump
        texRec={static_cast<float>(96*iceBoss->GetPhase()), 32, 32, 32};
        enemy.SetPosition(Vector2Lerp(jumpStart, *rangedSpot, 1.f - rangedTimer / 60.f));
        --rangedTimer;
    }
    return shared_from_this();
}

void IBSeek::CalcWalkingDirection(Actor &actor, Vector2 targetLoc) {
    if (Vector2Subtract(targetLoc, actor.GetPosition()).x <= 0) {
        actor.SetDirection(Direction::LEFT);
    } else {
        actor.SetDirection(Direction::RIGHT);
    }
}

void IBSeek::AnimateWalk(IceBoss* iceBoss) {
    ++currentFrameTimer;
    if (currentFrameTimer==frameTimer/4){
        activeFrame=0;
    }
    if (currentFrameTimer==frameTimer/4*2){
        activeFrame=1;
    }
    if (currentFrameTimer==frameTimer/4*3){
        activeFrame=2;
    }

    if (currentFrameTimer==frameTimer){
        activeFrame=3;
        currentFrameTimer=0;
    }

    if (iceBoss->GetPhase()==0) {
        texRec={static_cast<float>(0+32*activeFrame), 160, 32, 32};
    }
    if (iceBoss->GetPhase()==1) {
        texRec={static_cast<float>(64+32*activeFrame), 192, 32, 32};
    }
    if (iceBoss->GetPhase()==2) {
        texRec={static_cast<float>(192+32*activeFrame), 160, 32, 32};
    }
    if (iceBoss->GetPhase()==3) {
        texRec={static_cast<float>(256+32*activeFrame), 192, 32, 32};
    }

}
