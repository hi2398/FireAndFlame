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

				return std::make_shared<FallingSubState>();
			    break;
			case MOVEMENT::IDLE:
				return std::make_shared<FallingSubState>();
        }
	}
	else if (actor.GetWallCollisionRight()) {

		switch (actor.GetNextMovement()) {
		//right Side Wall
		    case MOVEMENT::MOVE_LEFT:
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


	//frame handling
	wallFrameCounter++;
	if (wallFrameCounter >= 15) {
		thisFrame++;
		wallFrameCounter = 0;
	}
	activeFrame = { (float)32 * thisFrame, 32, (float)32 * playerCharacter->GetDirection(), 32 };

	

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
	DrawTextureRec(playerCharacter->spriteSheetMagmos,
		activeFrame,
		playerCharacter->GetPosition(),
		WHITE);
	
}