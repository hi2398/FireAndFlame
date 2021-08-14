#include "TBRangedState.h"
#include "TBIdleState.h"
#include "TBAfterFightState.h"
#include "../Player/Fireball.h"
#include "../../Global.h"
#include "raymath.h"

TBRangedState::TBRangedState(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,32 * 4,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,0,(float)32 * enemy.GetDirection(), 32 };

	//fireball initialisation
	Vector2 fireballSpawn = {enemy.GetPosition()};
	fireballSpawn.x += enemy.GetDirection() * 20.0f;
	Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
	Vector2 fireballDirection = Vector2Normalize(playerReference);
	sceneManager->AddInteractable(std::make_unique<Fireball>(fireballSpawn, fireballDirection, enemy.GetType()));

	//reduce health when casting
	enemy.SetHealth(enemy.GetHealth() - 10);

	//actioncounter ++
	enemy.IncrementActionCounter();
}

std::shared_ptr<EState> TBRangedState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBRangedState\n";
	if (enemy.GetHealth() <= 0 && enemy.IsGrounded()) return std::make_shared<TBAfterFightState>(enemy);

	stateFrameCounter++;
	stateExeCounter++;
	if (stateFrameCounter >= 4 && thisFrame < 2) {
		stateFrameCounter = 0;
		thisFrame++;
	}

	activeFrame = { (float)32 * thisFrame, 32 * 4, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 0, (float)32 * enemy.GetDirection(), 32 };

	if (stateExeCounter >= 20) return std::make_shared<TBIdleState>(enemy);
	return shared_from_this();
}

void TBRangedState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}
