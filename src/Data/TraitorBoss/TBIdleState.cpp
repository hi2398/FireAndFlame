#include "TBIdleState.h"
#include "TBRangedState.h"
#include "TBSeekCoal.h"
#include "TBMeleeState.h"
#include "TBDashState.h"
#include "TBApproachingState.h"
#include "../../Global.h"
#include <raymath.h>

TBIdleState::TBIdleState(Enemy& enemy) : EState(enemy)
{
	if (enemy.GetHealth() == 100) enemy.SetHealth(99);
	activeFrame = { 0,0,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBIdleState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBIdleState\n";

	decisionCounter++;
	if (decisionCounter >= 60) {
		CheckForCoal(enemy);
		//seek coal when on low health
		if (enemy.GetHealth() <= 30 && !noCoalFound) return std::make_shared<TBSeekCoal>(enemy);

		if (!CheckCollisionPointCircle(playerCharacter->GetPosition(), enemy.GetPosition(), 5 * 32) && enemy.GetHealth() >= 40 && enemy.GetActionCounter() < 2) return std::make_shared<TBRangedState>(enemy); //check if player is far enough away
		else if (CheckCollisionPointCircle(playerCharacter->GetPosition(), enemy.GetPosition(), 1 * 32)) { // in melee range
			return std::make_shared<TBMeleeState>(enemy);
		}
		else{
			return std::make_shared<TBApproachingState>(enemy);
		}
	}

	Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
	if (playerReference.x < 0) {
		enemy.SetDirection(LEFT);
	}
	else {
		enemy.SetDirection(RIGHT);
	}

	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}

	activeFrame = { (float)32 * thisFrame, 0, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 0, (float)32 * enemy.GetDirection(), 32 };

	return shared_from_this();
}

void TBIdleState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}

void TBIdleState::CheckForCoal(Enemy& enemy) {
	Rectangle enemySight = { enemy.GetPosition().x - 32 * 25, enemy.GetPosition().y - 10 * 32, 50 * 32, 20 * 32 };
	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (interactable->GetInteractableType() == InteractableType::Coal) {
			if (CheckCollisionRecs(interactable->GetInteractionZone(), enemySight)) {
				noCoalFound = false;
				return;
			}
		}
	}
	noCoalFound = true;
	return;
}