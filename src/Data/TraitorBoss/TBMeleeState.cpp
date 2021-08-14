#include "TBMeleeState.h"
#include "TBIdleState.h"
#include "TBAfterFightState.h"
#include "../../Global.h"

TBMeleeState::TBMeleeState(Enemy& enemy) : EState(enemy)
{
	randomAttack = GetRandomValue(0, 2);

	activeFrame = { 0,(float)randomAttack * 32,(float)64 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };

	enemy.IncrementActionCounter();
}

std::shared_ptr<EState> TBMeleeState::Update(Enemy& enemy)
{
	if (enemy.GetHealth() <= 0 && enemy.IsGrounded()) return std::make_shared<TBAfterFightState>(enemy);

	stateFrameCounter++;
	attackCounter++;
	if (stateFrameCounter >= 5) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}
	activeFrame = { (float)64 * thisFrame,(float)randomAttack * 32,(float)64 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2,0,(float)32 * enemy.GetDirection(), 32 };
	

	//attack hitbox
	switch (enemy.GetDirection())
	{
	case LEFT:

		if (randomAttack == 2) {
			collisionRec = { enemy.GetPosition().x + 16.0f - 46.0f,enemy.GetPosition().y + 6.0f, 38, 20 };
		}
		else {
			collisionRec = { enemy.GetPosition().x + 16.0f - 43.0f,enemy.GetPosition().y, 35, 32 };
		}
		break;
	case RIGHT:
		if (randomAttack == 2) {
			collisionRec = { enemy.GetPosition().x + 16.0f + 9.0f,enemy.GetPosition().y + 6.0f, 38, 20 };
		}
		else {
			collisionRec = { enemy.GetPosition().x + 16.0f + 9.0f, enemy.GetPosition().y, 35, 30 };
		}
		break;

		break;
	}

	if (CheckCollisionRecs(playerCharacter->playerHitbox, collisionRec)) {
		if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 5);
	}

	if (attackCounter >= 15) return std::make_shared<TBIdleState>(enemy);
	return shared_from_this();
}

void TBMeleeState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);

	if (enemy.GetDirection() == LEFT) {
		DrawTextureRec(enemy.GetThirdTexture(), activeFrame, { enemy.GetPosition().x - 32, enemy.GetPosition().y }, WHITE);
	}
	else {
		DrawTextureRec(enemy.GetThirdTexture(), activeFrame, enemy.GetPosition(), WHITE);
	}
	
}
