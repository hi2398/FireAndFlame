#include <iostream>
#include "MeleeActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "RangedActionState.h"

std::shared_ptr<State> MeleeActionState::Update(Actor& actor) {
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
		switch (playerCharacter->GetNextMovement())
		{
		case MOVEMENT::MOVE_LEFT:
			spearHitbox.x = playerCharacter->GetPosition().x + 16.0f - 9.0f;

			if (!isSwiping) isSwiping = true, playerCharacter->resetAttack = 0;
			break;
		case MOVEMENT::MOVE_RIGHT:
			spearHitbox.x = playerCharacter->GetPosition().x + 16.0f + 9.0f;

			if (!isSwiping) isSwiping = true, playerCharacter->resetAttack = 0;
			break;
		case MOVEMENT::IDLE:
			break;
		}


		//spear follows player
		spearHitbox.x = playerCharacter->GetPosition().x + 16.0f + (9.0f);
		spearHitbox.y = playerCharacter->GetPosition().y + 11.0f;
		//update attack function
		if (!isSwiping) isSwiping = true, playerCharacter->resetAttack = 0;
		//attack states
		switch (playerCharacter->attackState)
		{
		case 0:
			if (isSwiping) {
				spearRotation += 10.0f ;
				if (spearRotation >= 270 + (140)) {
					spearRotation = 330;
					isSwiping = false;
					playerCharacter->attackState++;
					if constexpr (DEBUG_PLAYER_STATES) {
						std::cout << "new state: idle action" << std::endl;
					}
					return std::make_shared<IdleActionState>();
				}
			}
			break;
		case 1:
			if (isSwiping) {
				spearRotation += 3.0f ;
				if (spearRotation >= 390) {
					spearRotation = 300;
					isSwiping = false;
					playerCharacter->attackState++;
					return std::make_shared<IdleActionState>();
				}
			}
			break;
		case 2:
			//stab
			if (isSwiping) {
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
					isSwiping = false;
					spearRotation = 300;
					playerCharacter->attackState = 0;
					return std::make_shared<IdleActionState>();
				}
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
	if (isSwiping) {
		DrawRectanglePro(spearHitbox, { 10, 0 }, spearRotation, RED);
	}
}