#include <iostream>
#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"
#include "raymath.h"

MeleeActionState::MeleeActionState(Actor& player) : PlayerStates(player) {

}

std::shared_ptr<State> MeleeActionState::Update(Actor& player) {
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
		switch (player.GetAttackDirection())
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
		}

		//update attack function
		if (!player.GetIsSwiping()) player.SetIsSwiping(true), playerCharacter->resetAttack = 0;
		//attack states
		switch (player.GetAttackDirection())
		{
		case ATT_LEFT:
			switch (playerCharacter->attackState)
			{
			case 0:
				if (player.GetIsSwiping()) {
					spearRotation -= 20.0f;
					if (spearRotation <= 130) {
						player.SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			case 1:
				if (player.GetIsSwiping()) {
					spearRotation += 20.0f;
					if (spearRotation >= 240) {
						player.SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			case 2:
				//stab
				if (player.GetIsSwiping()) {
					spearRotation = 0;
					stabbingDistance += 5.0f;

					if (stabbingDistance <= 45) {
						spearHitbox.x -= 15.0f * stabbingDistance / 45;
					}

					if (stabbingDistance > 45) {
						spearHitbox.x -= 15.0f * (float)((90 - stabbingDistance) / 45);
					}

					if (stabbingDistance >= 90) {
						stabbingDistance = 0;
						player.SetIsSwiping(false);
						playerCharacter->attackState = 0;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			default:
				break;
			}
			break;
		case ATT_RIGHT:
			switch (playerCharacter->attackState)
			{
			case 0:
				if (player.GetIsSwiping()) {
					spearRotation += 20.0f;
					if (spearRotation >= 410) {
						player.SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			case 1:
				if (player.GetIsSwiping()) {
					spearRotation -= 20.0f;
					if (spearRotation <= 300) {
						player.SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			case 2:
				//stab
				if (player.GetIsSwiping()) {
					spearRotation = 0;
					stabbingDistance += 5.0f;

					if (stabbingDistance <= 45) {
						spearHitbox.x += 15.0f * stabbingDistance / 45;
					}

					if (stabbingDistance > 45) {
						spearHitbox.x += 15.0f * (float)((90 - stabbingDistance) / 45);
					}

					if (stabbingDistance >= 90) {
						stabbingDistance = 0;
						player.SetIsSwiping(false);
						playerCharacter->attackState = 0;
						return std::make_shared<IdleActionState>(player);
					}
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	//the hit collision is not working for rotated rectangles
	//thats why I use a combination of different rectangles for collision, which mimic the swiping motion of the actual spear/rectangle
	
	switch (player.GetDirection())
	{
	case LEFT:
		collisionRec = { player.GetPosition().x + 16.0f - 31.0f,player.GetPosition().y - 6.0f, 30, 32 };
		break;
	case RIGHT:
		collisionRec = { player.GetPosition().x + 16.0f + 9.0f, player.GetPosition().y - 6.0f, 30, 30 };
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
				if (!enemies->IsInvulnerable() && player.GetIsSwiping() && CheckCollisionRecs(spearHitbox, enemies->GetCollider())) {
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
	if (player.GetIsSwiping()) {
		//actual hitbox
		/*DrawRectangle(collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height, GREEN);*/

		//pseudo hitbox
		DrawRectanglePro(spearHitbox, { 10,3 }, spearRotation, RED);
	}


}