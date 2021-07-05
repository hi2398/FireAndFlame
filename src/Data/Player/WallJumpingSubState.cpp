#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> WallJumpingSubState::Update(Actor& actor) {

	if constexpr (DEBUG_BUILD) {
		std::cout << "New State: Wall Jump\n";
	}

	actor.SetTimesJumped(1);
	actor.SetJumpBlocked(true);
	actor.SetWallCounter(0);

	if (actor.GetHeadCollision()) {
		actor.SetJumpSpeed(5.0f);
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
		actor.SetJumpBlocked(true);
		return std::make_shared<FallingSubState>();
	}

	//quit wall jump when touching another wall
	if ((actor.GetWallCollisionLeft() && actor.GetDirection() == 1) || (actor.GetWallCollisionRight() && actor.GetDirection() == -1)) {
		actor.SetWallJumpCommand(false);
		actor.SetJumpCommand(false);

		return std::make_shared<WallSlideSubState>();
	}

	return shared_from_this();
}

void WallJumpingSubState::Draw(Actor& actor) {
	switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	}
}