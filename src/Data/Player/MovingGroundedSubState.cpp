#include "MovingGroundedSubState.h"
#include "IdleGroundedSubState.h"
#include "../../Global.h"

std::shared_ptr<State> MovingGroundedSubState::Update(Actor& actor) {
	const auto actorLastPos = actor.GetLastPosition(); //func alias
	const auto actorPos = actor.GetPosition(); //func alias


	std::cout << "Moving Grounded\n";
	switch (actor.GetNextMovement())
	{
	case MOVEMENT::MOVE_LEFT:
		if (!actor.GetWallCollisionLeft()) {
			if (actor.GetIsRunning()) {
				actor.SetPosition({ actor.GetPosition().x - 5.0f, actor.GetPosition().y });
			}
			else {
				actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
			}
		}
		return shared_from_this();
	case MOVEMENT::MOVE_RIGHT:
		if (!actor.GetWallCollisionRight()) {
			if (actor.GetIsRunning()) {
				actor.SetPosition({ actor.GetPosition().x + 5.0f, actor.GetPosition().y });
			}
			else {
				actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
			}
		}
		return shared_from_this();
	case MOVEMENT::IDLE:
		return std::make_shared<IdleGroundedSubState>();
	}

}

void MovingGroundedSubState::Draw(Actor& actor) {
	switch (actor.GetDirection()) {
	case LEFT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
		break;
	}
	/*DrawRectangle(playerCharacter->GetPosition().x, playerCharacter->GetPosition().y, 10, 10, RED);*/
}