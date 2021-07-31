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
	if (player.GetActionBlocked()) return std::make_shared<IdleActionState>(player);
	// set spear rotation before attacking
	if (!player.GetIsSwiping()) {
		switch (player.GetAttackDirection())
		{
		case ATT_LEFT:
			switch (playerCharacter->attackState)
			{
			case 0:
				spearRotation = 240;
				break;
			case 1:
				spearRotation = 130;
				break;
			case 2:
				spearRotation = 0;
				break;
			default:
				break;
			}
			break;
		case ATT_RIGHT:
			switch (playerCharacter->attackState)
			{
			case 0:
				spearRotation = 300;
				break;
			case 1:
				spearRotation = 410;
				break;
			case 2:
				spearRotation = 0;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

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
		/*switch (player.GetAttackDirection())
		{
		case ATT_LEFT:
			if (playerCharacter->attackState == 2) {
				spearHitbox.x = player.GetPosition().x + 16.0f - (32.0f);
				spearHitbox.y = player.GetPosition().y + 11.0f;
			}
			else {
				spearHitbox.x = player.GetPosition().x + 16.0f - (9.0f);
				spearHitbox.y = player.GetPosition().y + 11.0f;
			}
			break;
		case ATT_RIGHT:
			spearHitbox.x = player.GetPosition().x + 16.0f + 9.0f;
			spearHitbox.y = player.GetPosition().y + 11.0f;
			break;
		}*/

		//update attack function
		if (!player.GetIsSwiping()) player.SetIsSwiping(true), playerCharacter->resetAttack = 0;
		
		stateFrameCounter++;
		if (stateFrameCounter >= 5) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		activeFrame = { (float)64 * thisFrame, (float)32 * playerCharacter->attackState,(float) 64 * player.GetDirection(), 32 };
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
		
		break;
	}



	//check if an enemy gets hit
	for (auto& enemies : sceneManager->GetEnemies()) {

			switch (playerCharacter->attackState)
			{
			case 0:
			case 1://same function for first two attack states
				if (!enemies->IsInvulnerable() && player.GetIsSwiping() && (CheckCollisionRecs(collisionRec, enemies->GetCollider()))) {
					enemies->ReceiveDamage(1);
					enemies->SetInvulnerable(true);
				}
				break;
			case 2:
				if (!enemies->IsInvulnerable() && player.GetIsSwiping() && CheckCollisionRecs(collisionRec, enemies->GetCollider())) {
					enemies->ReceiveDamage(3);
					enemies->SetInvulnerable(true);
				}
				break;
			default:
				break;
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