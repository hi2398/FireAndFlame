#include <iostream>
#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> WallJumpingSubState::Update(Actor& actor) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Wall Jump\n";
	}

	actor.SetTimesJumped(1);
	actor.SetJumpBlocked(true);
	actor.SetWallCounter(0);

	if (actor.GetHeadCollision()) {
		actor.SetJumpSpeed(5.0f);
		actor.SetJumpBlocked(false);
		return std::make_shared<FallingSubState>();
	}


	//wall jump
	if (actor.GetJumpSpeed() == 5.0f) wallJumpDirection = -actor.GetDirection();
	actor.SetPosition({ actor.GetPosition().x + 3.0f * wallJumpDirection, actor.GetPosition().y - actor.GetJumpSpeed() });
	actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
	if (actor.GetJumpSpeed() <= 0) {
		actor.SetJumpSpeed(5.0f);
		actor.SetWallJumpCommand(false);
		actor.SetJumpCommand(false);
		actor.SetJumpBlocked(false);
		return std::make_shared<FallingSubState>();
	}

	//quit wall jump when touching another wall
	if ((actor.GetWallCollisionLeft() && actor.GetDirection() == RIGHT) || (actor.GetWallCollisionRight() && actor.GetDirection() == LEFT)) {
		actor.SetWallJumpCommand(false);
		actor.SetJumpCommand(false);
		actor.SetJumpBlocked(false);
		return std::make_shared<WallSlideSubState>();
	}

	wallJumpFrameCounter++;
	if (wallJumpFrameCounter >= 15) {
		thisFrame++;
		wallJumpFrameCounter = 0;
	}
	activeFrame = { (float)32 * thisFrame, 0, (float)32 * wallJumpDirection ,32 };

	return shared_from_this();
}

void WallJumpingSubState::Draw(Actor& actor) {
	DrawTextureRec(playerCharacter->spriteSheetMagmos,
		activeFrame,
		playerCharacter->GetPosition(),
		WHITE);
}