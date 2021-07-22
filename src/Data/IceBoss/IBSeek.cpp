#include "IBSeek.h"
#include "IBMelee.h"
#include "IBRanged.h"
#include "IBMinions.h"
#include "../../Global.h"
#include "IceBoss.h"
#include "raymath.h"
#include <stdexcept>

IBSeek::IBSeek() {

}

std::shared_ptr<State> IBSeek::Update(Actor &actor) {

    actor.LookAtPlayer(); //while seeking, always look at player

    if (nextAction==NextSeekAction::Decide){
        std::cout << "Deciding";
        //if player health is under 50%, spawn minions with a chance, instantly switch state cause spawn point is fixed
        if (playerCharacter->GetHealth() < playerCharacter->GetMaxHealth()/2){
            if (IceBoss::Decide()) return std::make_shared<IBMinions>();
        }
        //for melee and ranged only set next action, then either move to player in this state for melee or move away for ranged
        if (IceBoss::Decide()) nextAction=NextSeekAction::Melee;
        else {
            nextAction=NextSeekAction::Ranged;
            //set next ranged spot based on distance
            if (Vector2Distance(actor.GetPosition(), rightRangedSpot)<Vector2Distance(actor.GetPosition(), leftRangedSpot)){
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
            return MeleeApproach(actor);

        case NextSeekAction::Ranged:
            //move away from player and shoot
            return RangedMove(actor);
        case NextSeekAction::Decide: default:
            throw std::logic_error("should not be able to reach this point in IBSeek");

    }
    throw std::logic_error("should not be able to reach this point in IBSeek");
}


void IBSeek::Draw(Actor &actor) {
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    DrawTextureRec(iceBoss.GetMovingTexture(),
                   { 0,
                     0,
                     (float) iceBoss.GetMovingTexture().width * iceBoss.GetDirection(),
                     (float) iceBoss.GetMovingTexture().height },
                   iceBoss.GetPosition(),
                   WHITE);
}

std::shared_ptr<State> IBSeek::MeleeApproach(Actor& actor) {
    //to avoid weird chases, if player is above boss, decide new
    if (actor.GetPosition().y-playerCharacter->GetPosition().y>10 && abs(actor.GetPosition().x-playerCharacter->GetPosition().x) <64) {
        nextAction=NextSeekAction::Decide;
        return shared_from_this();
    }

    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    //first, check in which direction the player is
    CalcWalkingDirection(actor, playerCharacter->GetPosition());
    //if player is in range, attack him
    if (CheckCollisionRecs(playerCharacter->playerHitbox, iceBoss.GetMeleeRange())) {
        return std::make_shared<IBMelee>();
    }
    //else continue moving towards him
    float nextPosX = actor.GetPosition().x+actor.GetDirection()*IceBoss::SpeedMultiplier()*IceBoss::GetMovementSpeed();
    actor.SetPosition({nextPosX, actor.GetPosition().y});
    return shared_from_this();
}

std::shared_ptr<State> IBSeek::RangedMove(Actor& actor) {
    //if the jump is finished, execute the ranged attack
    if (rangedTimer==0){
        return std::make_shared<IBRanged>(actor.GetPosition());
    }
    //check if boss is at the jump spot
    if (Vector2Distance(actor.GetPosition(), jumpStart) <= 20 && !jumpStarted){
        jumpStarted = true;
    } else { //if not, check which direction to walk in
        CalcWalkingDirection(actor, jumpStart);
        float nextPosX = actor.GetPosition().x+actor.GetDirection()*IceBoss::SpeedMultiplier()*IceBoss::GetMovementSpeed();
        actor.SetPosition({nextPosX, actor.GetPosition().y});
    }
    if (jumpStarted) { //jump
        Vector2Lerp(jumpStart, *rangedSpot, 1.f-rangedTimer/60.f);
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
