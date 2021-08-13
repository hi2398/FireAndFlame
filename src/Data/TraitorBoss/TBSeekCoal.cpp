#include "TBSeekCoal.h"
#include "TBIdleState.h"
#include "../../Global.h"
#include "raymath.h"

TBSeekCoal::TBSeekCoal(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,32 * 3,(float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { 0,32 * 1,(float)32 * enemy.GetDirection(), 32 };
}

std::shared_ptr<EState> TBSeekCoal::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) std::cout << "TBSeekCoal\n";

	CheckForCoal(enemy);
	if (noCoalFound || enemy.GetHealth() >= 35) return std::make_shared<TBIdleState>(enemy);

	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		stateFrameCounter = 0;
		thisFrame++;
		thisFrame2++;
	}
	activeFrame = { (float)32 * thisFrame, 32 * 3, (float)32 * enemy.GetDirection(), 32 };
	activeFrame2 = { (float)32 * thisFrame2, 32 * 1, (float)32 * enemy.GetDirection(), 32 };

	enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
	return shared_from_this();
}

void TBSeekCoal::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetSecondTexture(), activeFrame2, enemy.GetPosition(), WHITE);
	DrawTextureRec(enemy.GetTexture(), activeFrame, enemy.GetPosition(), WHITE);
}

void TBSeekCoal::CheckForCoal(Enemy& enemy) {
	Rectangle enemySight = {enemy.GetPosition().x - 32 * 25, enemy.GetPosition().y - 10 * 32, 50 * 32, 20 * 32};
	for (const auto& interactable : sceneManager->GetInteractables()) {
		if (interactable->GetInteractableType() == InteractableType::Coal) {
			if (CheckCollisionRecs(interactable->GetInteractionZone(), enemySight)) {
				Vector2 coalReference = Vector2Subtract(enemy.GetPosition(), interactable->GetPosition());
				if (coalReference.x < 0 && coalReference.y == 0) {
					enemy.SetDirection(RIGHT);
				}
				else if (coalReference.x > 0 && coalReference.y == 0) {
					enemy.SetDirection(LEFT);
				}
				return;
			}
		}
	}
	noCoalFound = true;
	return;
}