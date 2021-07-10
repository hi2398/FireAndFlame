#include "IdleActionState.h"
#include "../../Global.h"
#include "MeleeActionState.h"
#include "RangedActionState.h"
#include <stdexcept>
#include <iostream>

std::shared_ptr<State> IdleActionState::Update(Actor& actor) {
	//attack reset
	if (playerCharacter->attackState > 0) {
		playerCharacter->resetAttack++;
		if (playerCharacter->resetAttack >= 90) playerCharacter->attackState = 0;
	}


	switch (playerCharacter->GetNextAction()) {

	case ACTION::MELEE_ATTACK:
		if constexpr (DEBUG_PLAYER_STATES) {
			std::cout << "new state: melee" << std::endl;
		}
		if (!playerCharacter->GetActionBlocked()) {
			return std::make_shared<MeleeActionState>();
		}
		else return shared_from_this();

	case ACTION::RANGED_ATTACK:
		if constexpr (DEBUG_PLAYER_STATES) {
			std::cout << "new state: ranged" << std::endl;
		}
		if (!playerCharacter->GetActionBlocked()) {
			return std::make_shared<RangedActionState>();
		}
		else return shared_from_this();

	case ACTION::NONE:
	default:

		return shared_from_this();
	}
	throw std::invalid_argument("bad state");
}

void IdleActionState::Draw(Actor& actor) {

}
