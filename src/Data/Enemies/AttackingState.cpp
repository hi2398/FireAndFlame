#include <cmath>
#include <raylib.h>
#include <raymath.h>

#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "IdleState.h"
#include "ApproachingState.h"
#include "RoamingState.h"
#include "AttackingState.h"
#include "StunnedState.h"
#include "ToastCat.h"
#include "Toast.h"
#include "Foam.h"

AttackingState::AttackingState(Enemy& enemy) : EState(enemy)
{
	activeFrame.y = 32 * 5;
	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::SpringHog:
		activeFrame = { 32, 32 * 3, (float)32 * enemy.GetDirection() , 32};
		yDiff = enemy.GetPosition().y - playerCharacter->GetPosition().y;
		xDiff = playerCharacter->GetPosition().x - enemy.GetPosition().x;

		if (yDiff < 0) {
			attackDirection = xDiff * pow((1 + (pow(yDiff, 2) / pow(xDiff, 2))), -1) / (32 * 4);
		}
		else if (yDiff > 0) {
			attackDirection = xDiff * pow((1 - (pow(yDiff, 2) / pow(xDiff, 2))), -1) / (32 * 4);
		}
		else {
			attackDirection = xDiff / (32 * 4);
		}

		break;
	case EnemyTypes::ToastCat:
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		toastInit = { enemy.GetPosition().x + 16, enemy.GetPosition().y};
		sceneManager->AddInteractable(std::make_unique<Toast>(toastInit));
		break;
	case EnemyTypes::SpiderBot:
		foamInit = { enemy.GetPosition().x + 16 + 10 * enemy.GetDirection(), enemy.GetPosition().y + 10 };
		sceneManager->AddInteractable(std::make_unique<Foam>(foamInit));
		thisFrame = 2;
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		
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

		Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		Vector2 movingToPlayer = Vector2Normalize(playerReference);
		if (playerReference.y >= 0) {
			if (spiderBotRotation == 270) {
				enemy.SetDirection(LEFT);
			}
			else if (spiderBotRotation == 90) {
				enemy.SetDirection(RIGHT);
			}
			else if (spiderBotRotation == 180) {
			if (playerReference.x > 0) {
				enemy.SetDirection(LEFT);

			}
			else if (playerReference.x <= 0) {
				enemy.SetDirection(RIGHT);

			}
			}
			else if (playerReference.x > 0) {
				enemy.SetDirection(RIGHT);

			}
			else if (playerReference.x <= 0) {
				enemy.SetDirection(LEFT);

			}
		}
		else if (playerReference.y < 0) {
			if (playerReference.x > 0) {
				enemy.SetDirection(RIGHT);

			}
			else if (playerReference.x < 0) {
				enemy.SetDirection(LEFT);

			}
		}
		break;
	case EnemyTypes::Flyer:
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		
		foamInit = { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 };
		sceneManager->AddInteractable(std::make_unique<Foam>(foamInit));
		break;
	default:
		
		break;
	}
	
}

std::shared_ptr<EState> AttackingState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Attacking\n";
	}
	stateFrameCounter++;

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::SpringHog:
		if (enemy.IsGrounded() && groundedCounter >= 30) return std::make_shared<ApproachingState>(enemy);
		//set variables based on grounded/aerial state
		groundedCounter++;
		thisFrame = 1;
		activeFrame = { (float)32 * thisFrame, 32 * 3 ,(float)32 * enemy.GetDirection(), 32 };

		//jump to player position
		jumpDistance = 3.5f * attackDirection;
		if (!enemy.GetJumpCommand() && !enemy.GetHeadCollision()) enemy.SetJumpSpeed(4.0f);
		enemy.SetJumpCommand(true);
		if (enemy.GetJumpCommand()) {
			enemy.SetPosition({ enemy.GetPosition().x + jumpDistance, enemy.GetPosition().y - enemy.GetJumpSpeed() });
			enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.2f);
			
		}
		
		break;
	case EnemyTypes::SpiderBot:
		if (stateFrameCounter >= 30 && thisFrame > 0) {
			thisFrame--;
			stateFrameCounter = 0;
		}
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };

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

		//exit attack state when too close
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(), { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 }, 32 * 2)) {
			return std::make_shared<ApproachingState>(enemy);
		}
		/*else {
			Vector2 playerReference = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
			Vector2 movingToPlayer = Vector2Normalize(playerReference);
			if (playerReference.y >= 0) {
				if (playerReference.x > 0) {
					enemy.SetDirection(RIGHT);

				}
				else if (playerReference.x <= 0) {
					enemy.SetDirection(LEFT);

				}
			}
			else if (playerReference.y < 0) {
				if (playerReference.x > 0) {
					enemy.SetDirection(RIGHT);

				}
				else if (playerReference.x < 0) {
					enemy.SetDirection(LEFT);

				}
			}
		}*/

		//exit when too far away
		if (!CheckCollisionPointCircle(playerCharacter->GetPosition(), { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 }, 32 * 6)) {
			return std::make_shared<RoamingState>(enemy);
		}

		attackCounter++;

		if (attackCounter >= 150) {
			return std::make_shared<ApproachingState>(enemy);
		}

		break;
	case EnemyTypes::Flyer:
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		if (thisFrame >= 3) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		
		attackCounter++;

		if (attackCounter >= 30) {
			return std::make_shared<ApproachingState>(enemy);
		}
		
		break;
	case EnemyTypes::ToastCat:
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		if (thisFrame >= 3) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };

		attackCounter++;
		
		if (attackCounter >= 150) return std::make_shared<ApproachingState>(enemy);
		
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
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		activeFrame = { (float)32 * thisFrame, 32 * 5, (float)-32 * enemy.GetDirection(), 32 };
		
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
	if (enemy.GetEnemyType() == EnemyTypes::SpiderBot) {
		DrawTexturePro(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16, 32, 32 }, { 16, 16 }, spiderBotRotation, WHITE);
	}
	else {
		DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
	}
}