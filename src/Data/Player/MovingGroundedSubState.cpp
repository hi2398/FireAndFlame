#include <iostream>
#include "MovingGroundedSubState.h"
#include "IdleGroundedSubState.h"
#include "../../Global.h"

std::shared_ptr<State> MovingGroundedSubState::Update(Actor& actor) {
	const auto actorLastPos = actor.GetLastPosition(); //func alias
	const auto actorPos = actor.GetPosition(); //func alias


	if constexpr (DEBUG_PLAYER_STATES) {
		std::cout << "New State: Moving Grounded\n";
	}


	switch (actor.GetNextMovement())
	{
	case MOVEMENT::MOVE_LEFT:
		
			if (actor.GetIsRunning()) {
				actor.SetPosition({ actor.GetPosition().x - 5.0f, actor.GetPosition().y });
			}
			else {
				actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
			}

			activeFrame = {0,0, -32, 32};
			break;
	case MOVEMENT::MOVE_RIGHT:
		
			if (actor.GetIsRunning()) {
				actor.SetPosition({ actor.GetPosition().x + 5.0f, actor.GetPosition().y });
			}
			else {
				actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
			}

			activeFrame = { 0,0, 32, 32 };
			break;
	case MOVEMENT::IDLE:
		return std::make_shared<IdleGroundedSubState>();
	case MOVEMENT::DASH_LEFT:
		actor.Dash(LEFT);
		frameCounterDash++;
		activeFrame = { (float)-32 * frameCounterDash, 32* 2, -32, 32 };
		break;
	case MOVEMENT::DASH_RIGHT:
		actor.Dash(RIGHT);
		frameCounterDash++;
		activeFrame = { (float)32 * frameCounterDash, 32* 2, 32, 32};
		break;
	}
	return shared_from_this();
}

void MovingGroundedSubState::Draw(Actor& actor) {
	/*if (actor.GetIsSwiping()) {
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width * actor.GetDirection(), (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width * actor.GetDirection(), (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}*/
	
	
	if (actor.GetIsSwiping()) {
		DrawTextureRec(playerCharacter->spriteSheetMagmos, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(playerCharacter->spriteSheetMagmos, activeFrame, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
	}
}