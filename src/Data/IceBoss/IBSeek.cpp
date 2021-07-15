#include "IBSeek.h"
#include "IBMelee.h"
#include "IBRanged.h"
#include "IBMinions.h"
#include "../../Global.h"
#include "IceBoss.h"
#include <stdexcept>

IBSeek::IBSeek() {

}

std::shared_ptr<State> IBSeek::Update(Actor &actor) {

    if (nextAction==NextSeekAction::Decide){

        //if player health is under 50%, spawn minions with a chance, instantly switch state cause spawn point is fixed
        if (playerCharacter->GetHealth() < playerCharacter->GetMaxHealth()/2){
            if (IceBoss::Decide()) std::cout << "Minions"; return std::make_shared<IBMinions>();
        }
        //for melee and ranged only set next action, then either move to player in this state for melee or move away for ranged
        if (IceBoss::Decide()) nextAction=NextSeekAction::Melee;
        else nextAction=NextSeekAction::Ranged;
    }

    //move to player for melee, move away for ranged
    switch (nextAction) {
        case NextSeekAction::Melee:
            //move to player to attack him
            return MeleeApproach();
        case NextSeekAction::Ranged:
            //move away from player and shoot
            return RangedMove();
        case NextSeekAction::Decide:
            throw std::invalid_argument("should not be able to reach decide action at this point in IBSeek");
    }
}

void IBSeek::Draw(Actor &actor) {

}

std::shared_ptr<State> IBSeek::MeleeApproach() {
    return shared_from_this();
}

std::shared_ptr<State> IBSeek::RangedMove() {
    return shared_from_this();
}
