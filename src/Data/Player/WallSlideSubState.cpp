#include <iostream>
#include "WallSlideSubState.h"
#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "WallJumpingSubState.h"
#include "../../Global.h"

WallSlideSubState::WallSlideSubState(Actor& player) : PlayerStates(player) {
	
}

std::shared_ptr<State> WallSlideSubState::Update(Actor& player) {

	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Wall Slide\n";
	}

	//short delay when entering wall slide
	player.SetWallCounter(player.GetWallCounter() + 1);
	player.SetCanDash(true);
	player.SetActionBlocked(true);

	//Sliding Down Wall
	if (player.GetWallCollisionLeft()) {
		//left side Wall
		switch (player.GetNextMovement())
		{
		    case MOVEMENT::MOVE_LEFT:
		        if (player.GetWallCounter() >= 15) {
					player.SetPosition({ player.GetPosition().x, player.GetPosition().y + 2.0f });
			    }
			    break;
			case MOVEMENT::MOVE_RIGHT:

				return std::make_shared<FallingSubState>(player);
			    break;
			case MOVEMENT::IDLE:
				return std::make_shared<FallingSubState>(player);
        }
	}
	else if (player.GetWallCollisionRight()) {

		switch (player.GetNextMovement()) {
		//right Side Wall
		    case MOVEMENT::MOVE_LEFT:
				return std::make_shared<FallingSubState>(player);
			break;
			case MOVEMENT::MOVE_RIGHT:
			    if (player.GetWallCounter() >= 15) player.SetPosition({ player.GetPosition().x , player.GetPosition().y + 2.0f });
			break;
			case MOVEMENT::IDLE:
			    return std::make_shared<FallingSubState>(player);
		}
	}
	else if (!player.GetWallJumpCommand()) return std::make_shared<FallingSubState>(player);


	//frame handling
	activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 32, (float)32 * playerCharacter->GetDirection(), 32 };

	

	//Jumping Off Wall
	if (player.GetWallJumpCommand()) {
		player.SetJumpSpeed(5.0f);
		return std::make_shared<WallJumpingSubState>(player);
	}
	//reset actor values
	player.SetTimesJumped(1);
	player.SetFallingSpeed(2.0f);

	return shared_from_this();
}

void WallSlideSubState::Draw(Actor& player) {
	DrawTextureRec(playerCharacter->upperBody,
		activeFrame,
		player.GetPosition(),
		WHITE);
	
}