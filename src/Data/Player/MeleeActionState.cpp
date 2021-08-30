#include <iostream>
#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"
#include "raymath.h"

MeleeActionState::MeleeActionState(Actor& player) : PlayerStates(player) {
	activeFrame = { (float)64 * thisFrame, (float)32 * playerCharacter->attackState,(float)64 * player.GetDirection(), 32 };
}

std::shared_ptr<State> MeleeActionState::Update(Actor& player) {
	if (player.GetActionBlocked() || player.GetIsDashing()) return std::make_shared<IdleActionState>(player);
	

	switch (playerCharacter->GetNextAction()) {

	case ACTION::RANGED_ATTACK:
		if (actionDone) {
			if constexpr (DEBUG_PLAYER_STATES) {
				std::cout << "new state: ranged" << std::endl;
			}
			return std::make_shared<RangedActionState>(player);
		}
	case ACTION::NONE:
		if (actionDone) {
			if constexpr (DEBUG_PLAYER_STATES) {
				std::cout << "new state: idle action" << std::endl;
			}
			return std::make_shared<IdleActionState>(player);
		}
	case ACTION::MELEE_ATTACK:

		//update attack function
		if (!player.GetIsSwiping()) player.SetIsSwiping(true), playerCharacter->resetAttack = 0, soundManager->PlaySfx(SFX::PLAYER_MELEE);

		stateFrameCounter++;
		if (stateFrameCounter >= 5) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		activeFrame = { (float)64 * thisFrame, (float)32 * playerCharacter->attackState,(float)64 * player.GetDirection(), 32 };
		if (thisFrame >= 3 && playerCharacter->attackState < 2) {
			player.SetIsSwiping(false);
			playerCharacter->attackState++;
			return std::make_shared<IdleActionState>(player);
		}
		else if (thisFrame >= 3 && playerCharacter->attackState == 2) {
			playerCharacter->attackState = 0;
			player.SetIsSwiping(false);
			return std::make_shared<IdleActionState>(player);
		}

	}


	//the hit collision is not working for rotated rectangles
	//thats why I use a combination of different rectangles for collision, which mimic the swiping motion of the actual spear/rectangle

	switch (player.GetDirection())
	{
	case LEFT:

		if (playerCharacter->attackState == 2) {
			collisionRec = { player.GetPosition().x + 16.0f - 46.0f,player.GetPosition().y + 6.0f, 38, 20 };
		}
		else {
			collisionRec = { player.GetPosition().x + 16.0f - 43.0f,player.GetPosition().y, 35, 32 };
		}
		break;
	case RIGHT:
		if (playerCharacter->attackState == 2) {
			collisionRec = { player.GetPosition().x + 16.0f + 9.0f,player.GetPosition().y + 6.0f, 38, 20 };
		}
		else {
			collisionRec = { player.GetPosition().x + 16.0f + 9.0f, player.GetPosition().y, 35, 30 };
		}
		break;
	}



	//check if an enemy gets hit
	for (auto& enemies : sceneManager->GetEnemies()) {
		if (!enemies->IsInvulnerable() && player.GetIsSwiping() && (CheckCollisionRecs(collisionRec, enemies->GetCollider()))) {
			switch (playerCharacter->attackState)
			{
			case 0:
			case 1://same function for first two attack states
				enemies->ReceiveDamage(1);
				break;
			case 2:
				enemies->ReceiveDamage(3);
				break;
			default:
				break;
			}
			enemies->SetInvulnerable(true);
			Vector2 tmp = { enemies->GetPosition().x + GetRandomValue(0, 16), enemies->GetPosition().y + GetRandomValue(0,16) };
			sceneManager->AddInteractable(std::make_unique<HitMarker>(tmp));
		}
	}


	return shared_from_this();
}

void MeleeActionState::Draw(Actor& player) {

	switch (player.GetDirection())
	{
	case LEFT:
		DrawTextureRec(playerCharacter->attackSprite, activeFrame, { player.GetPosition().x - 32, player.GetPosition().y }, WHITE);
		break;
	case RIGHT:
		DrawTextureRec(playerCharacter->attackSprite, activeFrame, player.GetPosition(), WHITE);
		break;
	}



}