#include <iostream>
#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> WallSlideSubState::Update(Actor& actor) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Wall Slide\n";
	}

	//short delay when entering wall slide
	actor.SetWallCounter(actor.GetWallCounter() + 1);
	actor.SetCanDash(true);
	actor.SetActionBlocked(true);

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
			    /*if (actor.GetWallCounter() >= 15) {
				    actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
			        }*/
				return std::make_shared<FallingSubState>();
			    break;
			case MOVEMENT::IDLE:
				return std::make_shared<FallingSubState>();
        }
	}
	else if (actor.GetWallCollisionRight()) {

		//right Side Wall
		switch (actor.GetNextMovement()) {
		    case MOVEMENT::MOVE_LEFT:
		        /*if (actor.GetWallCounter() >= 15) actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });*/
				return std::make_shared<FallingSubState>();
			break;
			case MOVEMENT::MOVE_RIGHT:
			    if (actor.GetWallCounter() >= 15) actor.SetPosition({ actor.GetPosition().x , actor.GetPosition().y + 2.0f });
			break;
			case MOVEMENT::IDLE:
			    return std::make_shared<FallingSubState>();
		}
	}

	else if (!actor.GetWallJumpCommand()) return std::make_shared<FallingSubState>();

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
	/*switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->textureWallSlide, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->textureWallSlide, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	}*/

	if (actor.GetWallCounter() >= 5) {
		DrawTextureRec(playerCharacter->textureWallSlide, { 0, 0, (float)playerCharacter->texturePlayer.width * playerCharacter->GetDirection(), (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width * playerCharacter->GetDirection(), (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	
}