#include "IdleActionState.h"
#include "../../Global.h"
#include "MeleeActionState.h"
#include "RangedActionState.h"
#include <stdexcept>
#include <iostream>

IdleActionState::IdleActionState(Actor& player) : PlayerStates(player) {

}

std::shared_ptr<State> IdleActionState::Update(Actor& player) {
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
		if (!player.GetActionBlocked() && !player.GetIsDashing()) {
			return std::make_shared<MeleeActionState>(player);
		}
		else return shared_from_this();
		break;
	case ACTION::RANGED_ATTACK:
		if constexpr (DEBUG_PLAYER_STATES) {
			std::cout << "new state: ranged" << std::endl;
		}
		if (!player.GetActionBlocked() && !player.GetIsDashing()) {
			return std::make_shared<RangedActionState>(player);
		}
		else return shared_from_this();
		break;
	case ACTION::NONE:
		
		
		if (player.IsGrounded()) {
			switch (player.GetNextMovement())
			{
			case MOVEMENT::MOVE_LEFT:
				activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 3, -32, 32 };
				break;
			case MOVEMENT::MOVE_RIGHT:
				activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 3, 32, 32 };
				break;
			case MOVEMENT::IDLE:
				activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 0, (float)32 * player.GetDirection(), 32 };
				break;
			default:
				break;
			}
		}
		else if (player.GetJumpCommand() || player.GetWallJumpCommand()) {
			if (player.GetWallJumpCommand()) wallJumpDirection = -1;
			else wallJumpDirection = 1;
			activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 6, (float)32 * player.GetDirection() * wallJumpDirection, 32 };
		}
		else if (!player.GetJumpCommand()){
			activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 5, (float)32 * player.GetDirection(), 32 };
		}
		

		return shared_from_this();
	default:
		break;
	}
	throw std::invalid_argument("bad state");
}

void IdleActionState::Draw(Actor& player) {
	if (player.IsGrounded() && !player.GetIsDashing()) {
		//upper body while grounded
		switch (player.GetNextMovement())
		{
		case MOVEMENT::MOVE_LEFT:
			DrawTextureRec(playerCharacter->upperBody, activeFrame, { player.GetPosition() }, WHITE);
			break;
		case MOVEMENT::MOVE_RIGHT:
			DrawTextureRec(playerCharacter->upperBody, activeFrame, { player.GetPosition() }, WHITE);
			break;
		case MOVEMENT::IDLE:
			DrawTextureRec(playerCharacter->upperBody, activeFrame, {player.GetPosition()}, WHITE);
			break;
		default:
			break;
		}
	} // upper body while airborne
	else if (!player.IsGrounded() && !player.GetIsDashing() && !player.GetActionBlocked()) {
		DrawTextureRec(playerCharacter->upperBody, activeFrame, { player.GetPosition() }, WHITE);
	}
}
