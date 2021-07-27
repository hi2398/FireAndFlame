#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "IdleState.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "StunnedState.h"
#include "ToastCat.h"

AttackingState::AttackingState(Enemy& enemy) : EState(enemy)
{
	toastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");

	attackDirection = (playerCharacter->GetPosition().x - enemy.GetPosition().x) / (32 * 4);
}

std::shared_ptr<EState> AttackingState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Attacking\n";
	}
	attackFrameCounter++;

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		toastMissile = {enemy.GetPosition().x + enemy.GetTexture().width/2 - 5, enemy.GetPosition().y};
		
		toastMissile.y = toastMissile.y - toastSpeed;
		toastSpeed += 5.0f * toastGravity;
		toastGravity -= 0.05f;
		

		toastMissile.x += toastDistance;
		toastDistance += 3.0f * attackDirection;
		
		if (!CheckCollisionPointRec(toastMissile, playerCharacter->visibleScreen)) {
			return std::make_shared<ApproachingState>(enemy);
		}

		toastHitbox = { toastMissile.x, toastMissile.y, (float)toastTexture.width, (float)toastTexture.height };
		if (CheckCollisionRecs(toastHitbox, playerCharacter->playerHitbox)) {
			if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - enemy.GetDamageValue());
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
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
	/*DrawRectangle(enemy.GetAttackHitbox().x, enemy.GetAttackHitbox().y, enemy.GetAttackHitbox().width, enemy.GetAttackHitbox().height, RED);*/

	DrawTexture(toastTexture, toastMissile.x, toastMissile.y, WHITE);
}