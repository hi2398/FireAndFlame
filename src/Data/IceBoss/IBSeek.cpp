#include "IBSeek.h"
#include "IBMelee.h"
#include "IBRanged.h"
#include "IBMinions.h"

IBSeek::IBSeek() {
    //decide on next action upon construction: melee, ranged, spawn minions(only if player has less than 50% health)
}

std::shared_ptr<State> IBSeek::Update(Actor &actor) {
    //if player health is under 50%, spawn minions with a chance
    return std::make_shared<IBMinions>();
    //if next action is ranged and player is reachable, fire at him
    return std::make_shared<IBRanged>();
    //if next action is melee and player is in reach, attack
    return std::make_shared<IBMelee>();
    //if next action is melee, continue moving to player
    return shared_from_this();
}

void IBSeek::Draw(Actor &actor) {

}
