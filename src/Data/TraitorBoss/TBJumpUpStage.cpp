#include "TBJumpUpStage.h"
#include "raymath.h"
#include <iostream>

TBJumpUpStage::TBJumpUpStage(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,0,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBJumpUpStage::Update(Enemy& enemy)
{
	if (!enemy.GetJumpCommand()) {
		enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		PrepareJump(enemy);
	}
	else {
		enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - enemy.GetJumpSpeed() });
		enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.1f * enemy.GetGravityMultiplier());
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
	Vector2 tmp = { 58 * 32, 88 * 32 };
	reference = Vector2Subtract(enemy.GetPosition(), tmp);
	if (reference.x >= 0) {
		tmp = { 65 * 32, 88 * 32 };
		reference = Vector2Subtract(enemy.GetPosition(), tmp);
		if (reference.x < 5 && reference.x > -5) {
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
		tmp = { 51 * 32, 88 * 32 };
		reference = Vector2Subtract(enemy.GetPosition(), tmp);
		if (reference.x < 5 && reference.x > -5) {
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
