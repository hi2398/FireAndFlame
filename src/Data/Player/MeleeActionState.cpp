#include <iostream>
#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"

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
		

	default:
		return shared_from_this();
	}
}

void MeleeActionState::Draw(Actor& actor) {
	if (playerCharacter->GetIsSwiping()) {
		DrawRectanglePro(spearHitbox, { 10, 3 }, spearRotation, RED);		
	}
}