#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "RoamingState.h"
#include "AttackingState.h"
#include "StunnedState.h"

#include <raymath.h>


StunnedState::StunnedState(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,32 * 3, (float)-32 * enemy.GetDirection(), 32 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::SpiderBot:
		//normal walking
		if (enemy.IsGrounded() && !enemy.GetHeadCollision() && !enemy.GetWallCollisionLeft() && !enemy.GetWallCollisionRight()) {
			spiderBotRotation = 0;
		}
		//walk on ceiling
		else if (enemy.GetHeadCollision()) {
			spiderBotRotation = 180;
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionLeft() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 90;
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionRight() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 270;
		}

		//walk up/down left wall
		if (enemy.GetWallCollisionLeft()) {
			spiderBotRotation = 90;
		}
		if (enemy.GetWallCollisionLeft() && enemy.IsGrounded() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 0;
		}

		//walk up/down left wall
		if (enemy.GetWallCollisionRight()) {
			spiderBotRotation = 270;
		}
		if (enemy.GetWallCollisionRight() && enemy.IsGrounded() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 0;
		}
		break;
	case EnemyTypes::SpringHog:
		activeFrame = { 0,32 * 3, (float)32 * enemy.GetDirection(), 32 };
		break;
	case EnemyTypes::Saugi:
		heart = std::make_unique<HeartObject>(enemy.GetPosition(), HeartState::Bad, 2);
		break;
	default:
		break;
	}
}

std::shared_ptr<EState> StunnedState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Stunned\n";
	}
	stateFrameCounter++;
	if (stateFrameCounter >= 15) {
		thisFrame++;
		stateFrameCounter = 0;
	}
	if (thisFrame >= 2) thisFrame = 0;
	activeFrame = { (float)32 * thisFrame, 32 * 3, (float)-32 * enemy.GetDirection(), 32 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::Saugi:
		heart->Update();
		heart->UpdatePos(enemy.GetPosition());
		stunnedFrameCounter++;
		if (stunnedFrameCounter % 16) {
			if (stunnedOffset == 0) stunnedOffset = 2;
			else if (stunnedOffset == 2) stunnedOffset = 0;
		}
		enemySight = { enemy.GetPosition().x + 16 - 16 * 32, enemy.GetPosition().y + 16, 32 * 32, 5 };
		for (const auto& coal : sceneManager->GetInteractables()) {
			if (CheckCollisionRecs(coal->GetInteractionZone(), enemySight) && coal->GetInteractableType() == InteractableType::Coal) {
				//enter approaching state on player sight right
				return std::make_shared<ApproachingState>(enemy);
			}
		}
		if (stunnedFrameCounter >= 120) {
			stunnedOffset = 0;
			return std::make_shared<RoamingState>(enemy);
		}
		break;
	case EnemyTypes::SpringHog:
		enemy.SetJumpCommand(false);
		stunnedFrameCounter++;
		if (stunnedFrameCounter % 16) {
			if (stunnedOffset == 0) stunnedOffset = 2;
			else if (stunnedOffset == 2) stunnedOffset = 0;
		}
		if (stunnedFrameCounter >= 60) {
			stunnedOffset = 0;
			return std::make_shared<AttackingState>(enemy);
		}
		break;
	case EnemyTypes::Flyer:
		stunnedFrameCounter++;
		if (stunnedFrameCounter % 16) {
			if (stunnedOffset == 0) stunnedOffset = 2;
			else if (stunnedOffset == 2) stunnedOffset = 0;
		}
		if (stunnedFrameCounter >= 60) {
			stunnedOffset = 0;
			return std::make_shared<AttackingState>(enemy);
		}
		break;
	case EnemyTypes::Howler:
		enemy.SetJumpCommand(false);
	default:
		stunnedFrameCounter++;
		if (stunnedFrameCounter % 16) {
			if (stunnedOffset == 0) stunnedOffset = 2;
			else if (stunnedOffset == 2) stunnedOffset = 0;
		}
		if (stunnedFrameCounter >= 60) {
			stunnedOffset = 0;
			return std::make_shared<ApproachingState>(enemy);
		}
		break;
	}
	//set direction before exiting Stunned State
	if (stunnedFrameCounter == 59) {
		Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (playerReference.x > 0) {

			enemy.SetDirection(RIGHT);
		}
		else {

			enemy.SetDirection(LEFT);
		}
	}
	return  shared_from_this();
}

void StunnedState::Draw(Enemy& enemy) {
	if (enemy.GetEnemyType() == EnemyTypes::SpiderBot) {
		DrawTexturePro(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x + 16 + stunnedOffset, enemy.GetPosition().y + 16, 32, 32 }, { 16, 16 }, spiderBotRotation, WHITE);
	}
	else {
		DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x + stunnedOffset, enemy.GetPosition().y }, WHITE);
	}

	if (enemy.GetEnemyType() == EnemyTypes::Saugi) {
		heart->Draw();
	}
}