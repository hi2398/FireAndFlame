#include <iostream>
#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"
#include "raymath.h"

std::shared_ptr<State> MeleeActionState::Update(Actor& actor) {
	// set spear rotation before attacking
	if (!playerCharacter->GetIsSwiping()) {
		switch (playerCharacter->GetAttackDirection())
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
			return std::make_shared<RangedActionState>();
		}
	case ACTION::NONE:
		if (actionDone) {
			if constexpr (DEBUG_PLAYER_STATES) {
				std::cout << "new state: idle action" << std::endl;
			}
			return std::make_shared<IdleActionState>();
		}
	case ACTION::MELEE_ATTACK:
		switch (playerCharacter->GetAttackDirection())
		{
		case ATT_LEFT:
			if (playerCharacter->attackState == 2) {
				spearHitbox.x = playerCharacter->GetPosition().x + 16.0f - (32.0f);
				spearHitbox.y = playerCharacter->GetPosition().y + 11.0f;
			}
			else {
				spearHitbox.x = playerCharacter->GetPosition().x + 16.0f - (9.0f);
				spearHitbox.y = playerCharacter->GetPosition().y + 11.0f;
			}
			break;
		case ATT_RIGHT:
			spearHitbox.x = playerCharacter->GetPosition().x + 16.0f + 9.0f;
			spearHitbox.y = playerCharacter->GetPosition().y + 11.0f;
			break;
		}

		//update attack function
		if (!playerCharacter->GetIsSwiping()) playerCharacter->SetIsSwiping(true), playerCharacter->resetAttack = 0;
		//attack states
		switch (playerCharacter->GetAttackDirection())
		{
		case ATT_LEFT:
			switch (playerCharacter->attackState)
			{
			case 0:
				if (playerCharacter->GetIsSwiping()) {
					spearRotation -= 20.0f;
					if (spearRotation <= 130) {
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>();
					}
				}
				break;
			case 1:
				if (playerCharacter->GetIsSwiping()) {
					spearRotation += 20.0f;
					if (spearRotation >= 240) {
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>();
					}
				}
				break;
			case 2:
				//stab
				if (playerCharacter->GetIsSwiping()) {
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
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState = 0;
						return std::make_shared<IdleActionState>();
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
				if (playerCharacter->GetIsSwiping()) {
					spearRotation += 20.0f;
					if (spearRotation >= 410) {
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>();
					}
				}
				break;
			case 1:
				if (playerCharacter->GetIsSwiping()) {
					spearRotation -= 20.0f;
					if (spearRotation <= 300) {
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState++;
						return std::make_shared<IdleActionState>();
					}
				}
				break;
			case 2:
				//stab
				if (playerCharacter->GetIsSwiping()) {
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
						playerCharacter->SetIsSwiping(false);
						playerCharacter->attackState = 0;
						return std::make_shared<IdleActionState>();
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
	//thats why I use a combination of different rectangles for collision, which mimics the swiping motion of the actual spear/rectangle
	
	switch (playerCharacter->GetDirection())
	{
	case LEFT:
		collisionRec = { playerCharacter->GetPosition().x + 16.0f - 31.0f, playerCharacter->GetPosition().y - 6.0f, 30, 32 };
		break;
	case RIGHT:
		collisionRec = { playerCharacter->GetPosition().x + 16.0f + 9.0f, playerCharacter->GetPosition().y - 6.0f, 30, 30 };
		break;
	}



	//check if an enemy gets hit
	for (auto& enemies : sceneManager->GetEnemies()) {

			switch (playerCharacter->attackState)
			{
			case 0:
			case 1://same function for first two attack states
				if (!enemies->IsInvulnerable() && playerCharacter->GetIsSwiping() && (CheckCollisionRecs(collisionRec, enemies->GetCollider()))) {
					enemies->ReceiveDamage(1);
					enemies->SetInvulnerable(true);
				}
				break;
			case 2:
				if (!enemies->IsInvulnerable() && playerCharacter->GetIsSwiping() && CheckCollisionRecs(spearHitbox, enemies->GetCollider())) {
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

void MeleeActionState::Draw(Actor& actor) {
	if (playerCharacter->GetIsSwiping()) {
		//actual hitbox
		/*DrawRectangle(collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height, GREEN);*/

		//pseudo hitbox
		DrawRectanglePro(spearHitbox, { 10,3 }, spearRotation, RED);
	}


}