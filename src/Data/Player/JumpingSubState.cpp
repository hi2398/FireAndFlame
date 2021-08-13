#include <iostream>
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallSlideSubState.h"
#include "../../Global.h"



JumpingSubState::JumpingSubState(Actor& player) : PlayerStates(player)
{
	if (player.GetIsDashing()) {
		activeFrame.y = 32 * 2;
	}
}

std::shared_ptr<State> JumpingSubState::Update(Actor& player) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Jumping\n";
	}

	enterWallSlideCounter++;
	player.SetWallCounter(0);

	//go to falling state if hit head
	if (player.GetHeadCollision()) {
		player.SetJumpSpeed(5.0f);
		return std::make_shared<FallingSubState>(player);
	}

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
		/*if (player.GetWallCollisionLeft() && enterWallSlideCounter >= 15) {
			player.SetJumpSpeed(5.0f);
			player.SetJumpCommand(false);
			return std::make_shared<WallSlideSubState>(player);
		}*/

		activeFrame = { 0,32 * 3, -32, 32 };
		break;
	case MOVEMENT::MOVE_RIGHT:

		if (player.GetIsRunning()) {
			player.SetPosition({ player.GetPosition().x + 5.0f, player.GetPosition().y });
		}
		else {
			player.SetPosition({ player.GetPosition().x + 3.0f, player.GetPosition().y });
		}
		/*if (player.GetWallCollisionRight() && enterWallSlideCounter >= 15) {
			player.SetJumpSpeed(5.0f);
			player.SetJumpCommand(false);
			return std::make_shared<WallSlideSubState>(player);
		}*/

		activeFrame = { 0,32 * 3, 32, 32 };
		break;
	case MOVEMENT::DASH_LEFT:
		player.Dash(LEFT);
		player.SetJumpSpeed(5.0f);
		player.SetJumpCommand(false);
		frameCounterDash++;
		activeFrame = { (float)-32 * frameCounterDash, 32 * 2, -32, 32 };
		return std::make_shared<FallingSubState>(player);
		break;
	case MOVEMENT::DASH_RIGHT:
		player.Dash(RIGHT);
		player.SetJumpSpeed(5.0f);
		player.SetJumpCommand(false);
		frameCounterDash++;
		activeFrame = { (float)32 * frameCounterDash, 32 * 2, -32, 32 };
		return std::make_shared<FallingSubState>(player);
		break;
	default:
		activeFrame = {0,32 * 3,(float)32* player.GetDirection(), 32};
		break;
	}



	if (player.GetJumpCommand() && !player.GetIsDashing()) {
		//check if actor is allowed to perform Double Jump
		if (player.GetCanDoubleJump()) {
			switch (player.GetTimesJumped())
			{
			case 1:
				player.SetPosition({ player.GetPosition().x, player.GetPosition().y - player.GetJumpSpeed() });
				player.SetJumpSpeed(player.GetJumpSpeed() - 0.1f * player.GetGravityMultiplier());
				if (player.GetJumpSpeed() <= 0) {
					player.SetJumpSpeed(5.0f);
					player.SetJumpCommand(false);
					return std::make_shared<FallingSubState>(player);
				}
				break;
			case 2:
				player.SetPosition({ player.GetPosition().x, player.GetPosition().y - player.GetJumpSpeed() });
				player.SetJumpSpeed(player.GetJumpSpeed() - 0.1f * player.GetGravityMultiplier());
				if (player.GetJumpSpeed() <= 0) {
					player.SetJumpSpeed(5.0f);
					player.SetJumpCommand(false);
					return std::make_shared<FallingSubState>(player);
				}
				break;
			default:
				break;
			}
		}
		else { //actor can only jump once
			if (player.GetTimesJumped() == 1) {
				player.SetPosition({ player.GetPosition().x, player.GetPosition().y - player.GetJumpSpeed() });
				player.SetJumpSpeed(player.GetJumpSpeed() - 0.1f * player.GetGravityMultiplier());
				if (player.GetJumpSpeed() <= 0) {
					player.SetJumpSpeed(5.0f);
					player.SetJumpCommand(false);
					return std::make_shared<FallingSubState>(player);
				}
			}

		}
		return shared_from_this();
	}
	else {
		if constexpr (DEBUG_PLAYER_STATES) {
			std::cout << "New State: Falling    " << std::endl;
		}
		player.SetJumpSpeed(5.0f);
		return std::make_shared<FallingSubState>(player);
	}

}

void JumpingSubState::Draw(Actor& player) {
	DrawTextureRec(playerCharacter->lowerBody, activeFrame, { player.GetPosition().x, player.GetPosition().y }, WHITE);
}