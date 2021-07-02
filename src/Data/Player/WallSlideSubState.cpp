#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> WallSlideSubState::Update(Actor& actor) {
	const auto actorLastPos = actor.GetLastPosition(); //func alias
	const auto actorPos = actor.GetPosition(); //func alias

	if constexpr (DEBUG_BUILD) {
		std::cout << "New State: Wall Slide\n";
	}

	//short delay when entering wall slide
	actor.SetWallCounter(actor.GetWallCounter() + 1);

	//Sliding Down Wall
	if (actor.GetWallCollisionLeft()) {
		//left side Wall
		switch (actor.GetNextMovement())
		{
		case MOVEMENT::MOVE_LEFT:
			if (actor.GetWallCounter() >= 15) {
				actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y + 2.0f });
			}
			break;
		case MOVEMENT::MOVE_RIGHT:
			if (actor.GetWallCounter() >= 15) {
				actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
			}
			break;
		case MOVEMENT::IDLE:
			return std::make_shared<FallingSubState>();
			break;
		}
	}
	else if (actor.GetWallCollisionRight()) {

		//right Side Wall
		switch (actor.GetNextMovement())
		{
		case MOVEMENT::MOVE_LEFT:
			if (actor.GetWallCounter() >= 15) {
				actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
			}
			break;
		case MOVEMENT::MOVE_RIGHT:
			if (actor.GetWallCounter() >= 15) {
				actor.SetPosition({ actor.GetPosition().x , actor.GetPosition().y + 2.0f });
			}
			break;
		case MOVEMENT::IDLE:
			return std::make_shared<FallingSubState>();
			break;
		}
	}
	else if (!actor.GetWallJumpCommand()) {
		return std::make_shared<FallingSubState>();
	}

	//Jumping Off Wall
	if (actor.GetWallJumpCommand()) {
		actor.SetJumpSpeed(5.0f);
		return std::make_shared<WallJumpingSubState>();
	}
	//reset actor values
	actor.SetTimesJumped(1);
	actor.SetFallingSpeed(2.0f);

	return shared_from_this();
}

void WallSlideSubState::Draw(Actor& actor) {
	switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->textureWallSlide, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->textureWallSlide, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	}
}