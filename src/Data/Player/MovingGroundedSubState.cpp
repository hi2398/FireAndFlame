#include <iostream>
#include "MovingGroundedSubState.h"
#include "IdleGroundedSubState.h"
#include "../../Global.h"

MovingGroundedSubState::MovingGroundedSubState(Actor& player) : PlayerStates(player) {
	activeFrame.y = 32;
}

std::shared_ptr<State> MovingGroundedSubState::Update(Actor& player) {



	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Moving Grounded\n";
	}


	switch (player.GetNextMovement())
	{
	case MOVEMENT::MOVE_LEFT:
		
			if (player.GetIsRunning()) {
				player.SetPosition({ player.GetPosition().x - 5.0f, player.GetPosition().y });
			}
			else {
				player.SetPosition({ player.GetPosition().x - 3.0f, player.GetPosition().y });
			}
			activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32, -32, 32};
			break;
	case MOVEMENT::MOVE_RIGHT:
		
			if (player.GetIsRunning()) {
				player.SetPosition({ player.GetPosition().x + 5.0f, player.GetPosition().y });
			}
			else {
				player.SetPosition({ player.GetPosition().x + 3.0f, player.GetPosition().y });
			}
			activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(),32, 32, 32 };
			break;
	case MOVEMENT::IDLE:
		return std::make_shared<IdleGroundedSubState>(player);
	case MOVEMENT::DASH_LEFT:
		player.Dash(LEFT);
		frameCounterDash++;
		activeFrame = { (float)-32 * frameCounterDash, 32* 2, -32, 32 };
		break;
	case MOVEMENT::DASH_RIGHT:
		player.Dash(RIGHT);
		frameCounterDash++;
		activeFrame = { (float)32 * frameCounterDash, 32* 2, 32, 32};
		break;
	}
	return shared_from_this();
}

void MovingGroundedSubState::Draw(Actor& player) {
	
	/*if (player.GetIsSwiping()) {
		DrawTextureRec(playerCharacter->spriteSheetMagmos, activeFrame, { player.GetPosition().x, player.GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->spriteSheetMagmos, activeFrame, { player.GetPosition().x, player.GetPosition().y }, WHITE);
	}*/

	if (player.GetIsDashing()) {
		DrawTextureRec(playerCharacter->upperBody, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->lowerBody, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
}