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

        //if player health is under 50%, spawn minions with a chance, instantly switch state cause spawn point is fixed
        if (playerCharacter->GetHealth() < playerCharacter->GetMaxHealth()/2){
            if (IceBoss::Decide()) return std::make_shared<IBMinions>();
        }
        //for melee and ranged only set next action, then either move to player in this state for melee or move away for ranged
        if (IceBoss::Decide()) nextAction=NextSeekAction::Melee;
        else {
            nextAction=NextSeekAction::Ranged;
            //if next ranged spot hasnt been set, then set it so the boss dashes backwards
                switch (actor.GetDirection()) {
                    case LEFT:
                        rangedSpot=&rightRangedSpot;
                        break;
                    case RIGHT:
                        rangedSpot=&leftRangedSpot;
                        break;
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
            throw std::logic_error("should not be able to reach decide action at this point in IBSeek");
    }
}


void IBSeek::Draw(Actor &actor) {

}

std::shared_ptr<State> IBSeek::MeleeApproach(Actor& actor) {

    //get player location, check distance from boss and make direction out of that
    auto playerPos = playerCharacter->GetPosition();
    auto distance = Vector2Subtract(playerPos, actor.GetPosition());
    auto direction = Vector2Normalize(distance);
    auto xPos=actor.GetPosition().x + (direction.x * IceBoss::GetMovementSpeed() * IceBoss::SpeedMultiplier());
    Vector2 posNextFrame{xPos, actor.GetPosition().y};
    actor.SetPosition(posNextFrame);

    //if close enough, execute attack
    if (Vector2Distance(playerCharacter->GetPosition(), actor.GetPosition())<=32){
        return std::make_shared<IBMelee>();
    }
    //otherwise, continue next frame
    return shared_from_this();
}

std::shared_ptr<State> IBSeek::RangedMove(Actor& actor) {

    //if close enough to the ranged spot, switch state and null out pointer
    if (rangedSpot) {
        if (Vector2Distance(actor.GetPosition(), *rangedSpot) <= 10.f) {
            rangedSpot = nullptr;
            return std::make_shared<IBRanged>();
        }
        if (Vector2Distance(actor.GetPosition(), *rangedSpot) <= 64.f) { //if is in range of two tiles, dash fast instead
            auto direction = Vector2Normalize(Vector2Add(actor.GetPosition(), *rangedSpot));
            auto xPos = actor.GetPosition().x + (direction.x * IceBoss::GetMovementSpeed() * IceBoss::SpeedMultiplier() * 2.f);
            actor.SetPosition({xPos, actor.GetPosition().y});
            return shared_from_this();
        } else {
            //timestep the move, return self
            //jump backwards to ranged spot, then shoot
            auto direction = Vector2Normalize(Vector2Add(actor.GetPosition(), *rangedSpot));
            auto xPos = actor.GetPosition().x + (direction.x * IceBoss::GetMovementSpeed() * IceBoss::SpeedMultiplier());
            actor.SetPosition({xPos, actor.GetPosition().y});
            return shared_from_this();
        }
    } else throw std::invalid_argument("Invalid Pointer in IceBoss Ranged Spot");

}
