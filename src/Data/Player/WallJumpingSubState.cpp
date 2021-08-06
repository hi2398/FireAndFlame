#include <iostream>
#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

WallJumpingSubState::WallJumpingSubState(Actor& player) : PlayerStates(player) {
	player.SetJumpCommand(false);
}

std::shared_ptr<State> WallJumpingSubState::Update(Actor& player) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Wall Jump\n";
	}

	
	player.SetWallCounter(0);

	if (player.GetJumpCommand()) {
		player.SetWallJumpCommand(false);
		return std::make_shared<JumpingSubState>(player);
	}

	if (player.GetHeadCollision()) {
		player.SetJumpSpeed(5.0f);
		player.SetJumpBlocked(false);
		player.SetWallJumpCommand(false);
		return std::make_shared<FallingSubState>(player);
	}
	player.SetTimesJumped(1);

	//wall jump
	if (player.GetJumpSpeed() == 5.0f) wallJumpDirection = -player.GetDirection();
	player.SetPosition({ player.GetPosition().x + 3.0f * wallJumpDirection, player.GetPosition().y - player.GetJumpSpeed() });
	player.SetJumpSpeed(player.GetJumpSpeed() - 0.1f * player.GetGravityMultiplier());
	if (player.GetJumpSpeed() <= 0) {
		player.SetJumpSpeed(5.0f);
		player.SetWallJumpCommand(false);
		player.SetJumpCommand(false);
		player.SetJumpBlocked(false);
		return std::make_shared<FallingSubState>(player);
	}

	//quit wall jump when touching another wall
	if ((player.GetWallCollisionLeft() && player.GetDirection() == RIGHT) || (player.GetWallCollisionRight() && player.GetDirection() == LEFT)) {
		player.SetWallJumpCommand(false);
		player.SetJumpCommand(false);
		player.SetJumpBlocked(false);
		return std::make_shared<WallSlideSubState>(player);
	}

	
	activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32 * 3, (float)32 * wallJumpDirection ,32 };

	return shared_from_this();
}

void WallJumpingSubState::Draw(Actor& player) {
	DrawTextureRec(playerCharacter->lowerBody,
		activeFrame,
		player.GetPosition(),
		WHITE);
}