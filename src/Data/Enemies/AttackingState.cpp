#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "StunnedState.h"

std::shared_ptr<EState> AttackingState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Attacking\n";
	}

	switch (enemy.GetEnemyType())
	{
	default:
		attackFrameCounter++;
		
		//exit attacking state when out of range
		if (!CheckCollisionRecs(playerCharacter->playerHitbox, enemy.GetAttackHitbox())) {
			return std::make_shared<ApproachingState>();
		}
		else {
			if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - enemy.GetDamageValue());
		}
	}

	


	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>();
	}
	return  shared_from_this();
}

void AttackingState::Draw(Enemy& enemy) {
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
	DrawRectangle(enemy.GetAttackHitbox().x, enemy.GetAttackHitbox().y, enemy.GetAttackHitbox().width, enemy.GetAttackHitbox().height, RED);
}