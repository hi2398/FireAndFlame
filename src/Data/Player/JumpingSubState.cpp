#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallSlideSubState.h"
#include "../../Global.h"

std::shared_ptr<State> JumpingSubState::Update(Actor& actor) {
	const auto actorPos = actor.GetPosition(); //func alias

	if constexpr (DEBUG_BUILD) {
		std::cout << "New State: Jumping\n";
	}

	actor.SetWallCounter(0);

	//go to falling state if hit head
	if (actor.GetHeadCollision()) {
		actor.SetJumpSpeed(5.0f);
		return std::make_shared<FallingSubState>();
	}

	//move sideways while airborne
	switch (actor.GetNextMovement())
	{
	case MOVEMENT::MOVE_LEFT:

		if (actor.GetIsRunning()) {
			actor.SetPosition({ actor.GetPosition().x - 5.0f, actor.GetPosition().y });
		}
		else {
			actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
		}
		break;
	case MOVEMENT::MOVE_RIGHT:

		if (actor.GetIsRunning()) {
			actor.SetPosition({ actor.GetPosition().x + 5.0f, actor.GetPosition().y });
		}
		else {
			actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
		}
		break;
	case MOVEMENT::DASH_LEFT:
		actor.Dash(LEFT);
		actor.SetJumpSpeed(5.0f);
		actor.SetJumpCommand(false);
		return std::make_shared<FallingSubState>();
		break;
	case MOVEMENT::DASH_RIGHT:
		actor.Dash(RIGHT);
		actor.SetJumpSpeed(5.0f);
		actor.SetJumpCommand(false);
		return std::make_shared<FallingSubState>();
		break;
	}



	if (actor.GetJumpCommand() && !actor.GetIsDashing()) {
		//check if actor is allowed to perform Double Jump
		if (actor.GetCanDoubleJump()) {
			switch (actor.GetTimesJumped())
			{
			case 1:
				actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
				actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
				if (actor.GetJumpSpeed() <= 0) {
					actor.SetJumpSpeed(5.0f);
					actor.SetJumpCommand(false);
					return std::make_shared<FallingSubState>();
				}
				break;
			case 2:
				actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
				actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
				if (actor.GetJumpSpeed() <= 0) {
					actor.SetJumpSpeed(5.0f);
					actor.SetJumpCommand(false);
					return std::make_shared<FallingSubState>();
				}
				break;
			default:
				break;
			}
		}
		else { //actor can only jump once
			if (actor.GetTimesJumped() == 1) {
				actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
				actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
				if (actor.GetJumpSpeed() <= 0) {
					actor.SetJumpSpeed(5.0f);
					actor.SetJumpCommand(false);
					return std::make_shared<FallingSubState>();
				}
			}

		}
		return shared_from_this();
	}
	else {
		if constexpr (DEBUG_BUILD) {
			std::cout << "New State: Falling    " << std::endl;
		}
		actor.SetJumpSpeed(5.0f);
		return std::make_shared<FallingSubState>();
	}

}

void JumpingSubState::Draw(Actor& actor) {
	switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	}
}