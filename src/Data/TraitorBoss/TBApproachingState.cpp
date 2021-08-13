#include "TBApproachingState.h"
#include "TBMeleeState.h"
#include "TBJumpUpStage.h"
#include "raymath.h"
#include "../../Global.h"

TBApproachingState::TBApproachingState(Enemy& enemy) : EState (enemy)
{
	playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
	if (playerReference.y > 0) {
		if (playerReference.x < 0) {
			enemy.SetDirection(RIGHT);
		}
		else {
			enemy.SetDirection(LEFT);
		}
	}
	else {
		if (playerReference.x < 0) {
			enemy.SetDirection(LEFT);
		}
		else {
			enemy.SetDirection(RIGHT);
		}
	}

	activeFrame = { 0,32 * 3,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,32 * 1,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBApproachingState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBApproachingState\n";

	enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}
	activeFrame = { (float)32 * thisFrame, 32 * 3, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 32 * 1, (float)32 * enemy.GetDirection(), 32 };
	
	if (enemy.IsGrounded()) {
		//keep moving to player
		playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (playerReference.y > 0) {
			if (playerReference.x < 0) {
				enemy.SetDirection(RIGHT);
			}
			else {
				enemy.SetDirection(LEFT);
			}
		}
		else if (playerReference.y < - 100) {
			return std::make_shared<TBJumpUpStage>(enemy);
		}
		else {
			if (playerReference.x < 0) {
				enemy.SetDirection(LEFT);
			}
			else {
				enemy.SetDirection(RIGHT);
			}
		}

		//exit state
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(), enemy.GetPosition(), 32)) {
			return std::make_shared<TBMeleeState>(enemy);
		}
	}

	return shared_from_this();
}

void TBApproachingState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}
