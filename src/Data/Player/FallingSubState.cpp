#include <iostream>
#include "FallingSubState.h"
#include "../../Global.h"
#include "JumpingSubState.h"
#include "WallSlideSubState.h"

std::shared_ptr<State> FallingSubState::Update(Actor& actor) {
	const auto actorLastPos = actor.GetLastPosition(); //func alias
	const auto actorPos = actor.GetPosition(); //func alias

	if constexpr (DEBUG_BUILD) {
		std::cout << "New State: Falling\n";
	}


	actor.SetJumpSpeed(5.0f);
	actor.SetWallJumpCommand(false);
	if (actor.GetTimesJumped() == 0) actor.SetTimesJumped(1);
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
		if (actor.GetWallCollisionLeft()) {
			return std::make_shared<WallSlideSubState>();
		}
		break;
	case MOVEMENT::MOVE_RIGHT:
		if (actor.GetIsRunning()) {
			actor.SetPosition({ actor.GetPosition().x + 5.0f, actor.GetPosition().y });
		}
		else {
			actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
		}
		if (actor.GetWallCollisionRight()) {
			return std::make_shared<WallSlideSubState>();
		}
		break;
	case MOVEMENT::DASH_LEFT:
		actor.Dash(LEFT);
		break;
	case MOVEMENT::DASH_RIGHT:
		actor.Dash(RIGHT);
		break;
	}

	if (!actor.GetJumpCommand() && !actor.GetIsDashing()) {
		actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y + actor.GetFallingSpeed() });
		if (actor.GetFallingSpeed() < 8.0f) actor.SetFallingSpeed(actor.GetFallingSpeed() + 0.1f * actor.GetGravityMultiplier());
		if (actor.GetFallingSpeed() >= 8.0f)actor.SetFallingSpeed(8.0f);
		return shared_from_this();
	}
	else {
		actor.SetFallingSpeed(0.0f);
		return std::make_shared<JumpingSubState>();
	}
	
}

void FallingSubState::Draw(Actor& actor) {
	switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		
		break;
	}
}
