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
                break;

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
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    //first, check in which direction the player is
    if(Vector2Subtract(playerCharacter->GetPosition(), iceBoss.GetPosition()).x <=0){
        std::cout << "Dir left\n";
        iceBoss.SetDirection(Direction::LEFT);
    } else {
        std::cout << "Dir right\n";
        iceBoss.SetDirection(Direction::RIGHT);
    }
    //if player is in range, attack him
    if (CheckCollisionRecs(playerCharacter->playerHitbox, iceBoss.GetMeleeRange())) {
        return std::make_shared<IBMelee>();
    }
    //else continue moving towards him

    return shared_from_this();
}

std::shared_ptr<State> IBSeek::RangedMove(Actor& actor) {
    //TODO: Implement
    return std::make_shared<IBRanged>();
}
