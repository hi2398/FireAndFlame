#include "TBJumpUpStage.h"
#include "TBAfterFightState.h"
#include "TBIdleState.h"
#include "TBApproachingState.h"
#include "raymath.h"
#include <iostream>
#include "../../Global.h"

TBJumpUpStage::TBJumpUpStage(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,0,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBJumpUpStage::Update(Enemy& enemy)
{
	if (enemy.GetHealth() <= 0 && enemy.IsGrounded()) return std::make_shared<TBAfterFightState>(enemy);
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBJumpUpStage\n";

	if (jumpSecondTime && enemy.IsGrounded()) return std::make_shared<TBIdleState>(enemy);

	if (!enemy.GetJumpCommand()) {
		enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		PrepareJump(enemy);
	}
	if (enemy.GetJumpCommand()) {
		enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - enemy.GetJumpSpeed() });
		enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.1f * enemy.GetGravityMultiplier());

		if (!jumpSecondTime && enemy.GetJumpSpeed() <= -1.5) {
			jumpSecondTime = true;
			enemy.SetJumpSpeed(5.0f);
		}
			
		if (jumpSecondTime && enemy.GetJumpSpeed() <= 2)
			enemy.SetPosition({enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y});
	}

	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}
	activeFrame = { (float)32 * thisFrame, 32 * 3, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 32 * 1, (float)32 * enemy.GetDirection(), 32 };

	if (!enemy.IsGrounded() && enemy.GetJumpCommand()) {
		activeFrame.y = (float)32 * 6;
		activeFrame2.y = (float)32 * 3;
	}
	else if (!enemy.IsGrounded() && !enemy.GetJumpCommand()) {
		activeFrame.y = (float)32 * 5;
		activeFrame2.y = (float)32 * 2;
	}
	else {
		activeFrame.y = (float)32 * 3;
		activeFrame2.y = (float)32 * 1;
	}
	return shared_from_this();
}

void TBJumpUpStage::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}

void TBJumpUpStage::PrepareJump(Enemy& enemy)
{
	Vector2 tmp = { 58*32, 88*32 };
	playerReference = Vector2Subtract(tmp, playerCharacter->GetPosition());
	if (playerReference.x >= 0) {
		tmp = { 51 * 32, 88 * 32 };
		reference = Vector2Subtract(enemy.GetPosition(), tmp);
		if (reference.x < 5 && reference.x > -5) {
			playerReference = Vector2Subtract(enemy.GetPosition(), playerCharacter->GetPosition());
			if (playerReference.x >= 0) {
				enemy.SetDirection(LEFT);
			}
			else {
				enemy.SetDirection(RIGHT);
			}
			enemy.SetPosition(tmp);
			enemy.SetJumpCommand(true);
			return;
		}
		else if (reference.x >= 0) {
			enemy.SetDirection(LEFT);
			return;
		}
		else {
			enemy.SetDirection(RIGHT);
			return;
		}
	}
	else {
		tmp = { 65 * 32, 88 * 32 };
		reference = Vector2Subtract(enemy.GetPosition(), tmp);
		if (reference.x < 5 && reference.x > -5) {
			playerReference = Vector2Subtract(enemy.GetPosition(), playerCharacter->GetPosition());
			if (playerReference.x >= 0) {
				enemy.SetDirection(LEFT);
			}
			else {
				enemy.SetDirection(RIGHT);
			}
			enemy.SetPosition(tmp);
			enemy.SetJumpCommand(true);
			return;
		}
		else if (reference.x >= 0) {
			enemy.SetDirection(LEFT);
			return;
		}
		else {
			enemy.SetDirection(RIGHT);
			return;
		}
	}

	return;
}
