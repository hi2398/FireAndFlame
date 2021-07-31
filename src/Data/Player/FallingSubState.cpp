#include <iostream>
#include "FallingSubState.h"
#include "../../Global.h"
#include "JumpingSubState.h"
#include "WallSlideSubState.h"

FallingSubState::FallingSubState(Actor& player) : PlayerStates(player)
{
	if (player.GetIsDashing()) {
		activeFrame.y = 32 * 2;
	}
}

std::shared_ptr<State> FallingSubState::Update(Actor& player) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Falling\n";
	}

	
	player.SetJumpSpeed(5.0f);
	player.SetWallJumpCommand(false);
	if (player.GetTimesJumped() == 0) player.SetTimesJumped(1);
	//move sideways while airborne
	switch (player.GetNextMovement())
	{
	case MOVEMENT::MOVE_LEFT:
		if (player.GetIsRunning()) {
			player.SetPosition({ player.GetPosition().x - 5.0f, player.GetPosition().y });
		}
		else {
			player.SetPosition({ player.GetPosition().x - 3.0f, player.GetPosition().y });
		}
		if (player.GetWallCollisionLeft()) {
			return std::make_shared<WallSlideSubState>(player);
		}

		activeFrame = { 0,0, -32, 32 };
		break;
	case MOVEMENT::MOVE_RIGHT:
		if (player.GetIsRunning()) {
			player.SetPosition({ player.GetPosition().x + 5.0f, player.GetPosition().y });
		}
		else {
			player.SetPosition({ player.GetPosition().x + 3.0f, player.GetPosition().y });
		}
		if (player.GetWallCollisionRight()) {
			return std::make_shared<WallSlideSubState>(player);
		}

		activeFrame = { 0,0, 32, 32 };
		break;
	case MOVEMENT::DASH_LEFT:
		stateFrameCounter++;
		activeFrame = { (float)-32 * stateFrameCounter, 32 * 2, -32, 32 };
		player.Dash(LEFT);
		
		break;
	case MOVEMENT::DASH_RIGHT:
		player.Dash(RIGHT);
		stateFrameCounter++;
		activeFrame = { (float)32 * stateFrameCounter, 32 * 2, 32, 32 };
		break;
	default:
		activeFrame = { 0,0,(float)32 * player.GetDirection(), 32 };
		break;
	}

	if (!player.GetJumpCommand() && !player.GetIsDashing()) {
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y + player.GetFallingSpeed() });
		if (player.GetFallingSpeed() < 8.0f) player.SetFallingSpeed(player.GetFallingSpeed() + 0.1f * player.GetGravityMultiplier());
		if (player.GetFallingSpeed() >= 8.0f)player.SetFallingSpeed(8.0f);
		return shared_from_this();
	}
	else if (player.GetJumpCommand() && !player.GetIsDashing()){
		player.SetFallingSpeed(0.0f);
		return std::make_shared<JumpingSubState>(player);
	}

	return shared_from_this();
	
}

void FallingSubState::Draw(Actor& player) {
	if (player.GetIsDashing()) {
		DrawTextureRec(playerCharacter->upperBody, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->lowerBody, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
}


