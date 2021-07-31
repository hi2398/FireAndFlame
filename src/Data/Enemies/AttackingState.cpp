#include <cmath>
#include <raymath.h>

#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "IdleState.h"
#include "ApproachingState.h"
#include "RoamingState.h"
#include "AttackingState.h"
#include "StunnedState.h"
#include "ToastCat.h"

AttackingState::AttackingState(Enemy& enemy) : EState(enemy)
{
	if (enemy.GetEnemyType() == EnemyTypes::ToastCat) {
		toastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");

		float yDiff = enemy.GetPosition().y - playerCharacter->GetPosition().y;
		float xDiff = playerCharacter->GetPosition().x - enemy.GetPosition().x;

		if (yDiff < 0) {
			attackDirection = xDiff * pow((1 + (pow(yDiff, 2) / pow(xDiff, 2))), -1) / (32 * 4);
		}
		else if (yDiff > 0) {
			attackDirection = xDiff * pow((1 - (pow(yDiff, 2) / pow(xDiff, 2))), -1) / (32 * 4);
		}
		else {
			attackDirection = xDiff / (32 * 4);
		}
	}
	
}

std::shared_ptr<EState> AttackingState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Attacking\n";
	}
	stateFrameCounter++;

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		toastMissile = {enemy.GetPosition().x + 16 - 5, enemy.GetPosition().y};
		
		toastMissile.y = toastMissile.y - toastSpeed;
		toastSpeed += 5.0f * toastGravity;
		toastGravity -= 0.05f;
		

		toastMissile.x += toastDistance;
		toastDistance += 3.0f * attackDirection;
		
		if (!CheckCollisionPointRec(toastMissile, playerCharacter->visibleScreen) && toastMissile.y > enemy.GetPosition().y) {
			return std::make_shared<ApproachingState>(enemy);
		}

		toastHitbox = { toastMissile.x, toastMissile.y, (float)toastTexture.width, (float)toastTexture.height };
		if (CheckCollisionRecs(toastHitbox, playerCharacter->playerHitbox)) {
			if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - enemy.GetDamageValue());
		}
		break;
	case EnemyTypes::Howler:
		attackCounter++;
		if (enemy.IsGrounded()) {
			activeFrame = {0, 32 * 2, (float) -32 * enemy.GetDirection(), 32};
		}
		else {
			activeFrame = {32, 32 * 2, (float)-32 * enemy.GetDirection(), 32 };
		}

		if (!enemy.GetJumpCommand()) enemy.SetJumpSpeed(3.0f);
		enemy.SetJumpCommand(true);
		enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * 10 * enemy.GetDirection(), enemy.GetPosition().y - enemy.GetJumpSpeed() });
		enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.25f);
		

		//check sight detection in certain radius
		if (attackCounter >= 30) {
			return std::make_shared<ApproachingState>(enemy);
		}
		break;
	default:
		
		
		//exit attacking state when out of range
		if (!CheckCollisionRecs(playerCharacter->playerHitbox, enemy.GetAttackHitbox())) {
			return std::make_shared<ApproachingState>(enemy);
		}
		else {
			if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - enemy.GetDamageValue());
		}
	}

	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}
	return  shared_from_this();
}

void AttackingState::Draw(Enemy& enemy) {
	DrawTextureRec(enemy.GetTexture(),activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);

	DrawTexture(toastTexture, toastMissile.x, toastMissile.y, WHITE);
}