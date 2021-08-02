#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "StunnedState.h"

RoamingState::RoamingState(Enemy& enemy) : EState(enemy)
{

}

std::shared_ptr<EState> RoamingState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Roaming\n";
	}
	//frameCounter for animation
	stateFrameCounter++;
	//frame handling
	if (stateFrameCounter >= 15) {
		thisFrame++;
		stateFrameCounter = 0;
	}
	activeFrame = { (float)32 * thisFrame, 32 * 1 ,(float)-32 * enemy.GetDirection(), 32 };

	Rectangle enemySight;
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::SpringHog:
		//set variables based on grounded/aerial state
		if (enemy.IsGrounded()) {
			thisFrame = 0;
			groundedCounter++;
			horizontalJumpCheck = 0;
		}
		else {
			thisFrame = 1;
			groundedCounter = 0;
		}
		activeFrame = { (float)32 * thisFrame, 32 * 1 ,(float)-32 * enemy.GetDirection(), 32 };

		//springhog sight
		enemySight = { enemy.GetPosition().x - 4 * 32 + 16, enemy.GetPosition().y + 6, 32 * 8, 20 };
		if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
			return std::make_shared<AttackingState>(enemy);
		}

		rightJumpCheck = {enemy.GetPosition().x + 16 + 3*32, enemy.GetPosition().y + 33, 1, 1};
		leftJumpCheck = { enemy.GetPosition().x + 15 - 3 * 32, enemy.GetPosition().y + 33, 1, 1 };

		//let springhog jump sideways if it has some tile to land on
		//else jump on spot
		if (enemy.IsGrounded()) {
			for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
			{
				tileRec.x = collTile.x;
				tileRec.y = collTile.y;
				if (CheckCollisionRecs(leftJumpCheck, tileRec) && enemy.GetDirection() == LEFT) {
					horizontalJumpCheck++;
				}
				if (CheckCollisionRecs(rightJumpCheck, tileRec) && enemy.GetDirection() == RIGHT) {
					horizontalJumpCheck++;
				}

			}
		}
		if (horizontalJumpCheck > 0) horizontalJumpCheck = 1;

		if (groundedCounter >= 45) enemy.SetJumpCommand(true);

		if (enemy.GetJumpCommand()) {
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection() * horizontalJumpCheck, enemy.GetPosition().y - enemy.GetJumpSpeed() });
			enemy.SetJumpSpeed(enemy.GetJumpSpeed() - 0.2f);
		}

		break;
	case EnemyTypes::SpiderBot:
		if (thisFrame >= 2) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 1 ,(float)-32 * enemy.GetDirection(), 32 };

		//check sight detection in certain radius minus triangle
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			5 * 32)) {
			return std::make_shared<ApproachingState>(enemy);
		}

		//normal walking
		if (enemy.IsGrounded() && !enemy.GetHeadCollision() && !enemy.GetWallCollisionLeft() && !enemy.GetWallCollisionRight()) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		}
		//walk on ceiling
		else if (enemy.GetHeadCollision()) {
			spiderBotRotation = 180;
			enemy.SetPosition({ enemy.GetPosition().x - enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionLeft() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 90;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + enemy.GetEnemyMovementSpeed() * enemy.GetDirection() });
		}
		if (enemy.GetHeadCollision() && enemy.GetWallCollisionRight() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 270;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - enemy.GetEnemyMovementSpeed() * enemy.GetDirection() });
		}

		
		//walk up/down left wall
		if (enemy.GetWallCollisionLeft()) {
			spiderBotRotation = 90;			
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + enemy.GetEnemyMovementSpeed() * enemy.GetDirection() });
			
		}
		if (enemy.GetWallCollisionLeft() && enemy.IsGrounded() && enemy.GetDirection() == RIGHT) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		}
		
		//walk up/down left wall
		if (enemy.GetWallCollisionRight()) {
			spiderBotRotation = 270;
			enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y - enemy.GetEnemyMovementSpeed() * enemy.GetDirection() });

		}
		if (enemy.GetWallCollisionRight() && enemy.IsGrounded() && enemy.GetDirection() == LEFT) {
			spiderBotRotation = 0;
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y });
		}
		
		

		break;
	case EnemyTypes::Flyer:
		flyRoamingCounter++;
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		if (thisFrame >= 2) thisFrame = 0;
		activeFrame = { (float)32 * thisFrame, 32 * 1 ,(float)-32 * enemy.GetDirection(), 32 };
		//check sight detection in certain radius minus triangle
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			5 * 32)) {
			return std::make_shared<ApproachingState>(enemy);
		}

		//enter idle when on ground & after set time
		if (flyRoamingCounter >= 300 && enemy.IsGrounded()) {
			return std::make_shared<IdleState>(enemy);
		}

		
		if (GetRandomValue(0, 100) == 0) {
			verticalDirection *= -1;
		}
		if (flyRoamingCounter <= 10 && enemy.IsGrounded() || enemy.GetHeadCollision()) {
			verticalDirection *= -1;
		}


		enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * enemy.GetDirection(), enemy.GetPosition().y - enemy.GetEnemyMovementSpeed() * verticalDirection});
		
		
		

		break;
	case EnemyTypes::ToastCat:
		//check line of sight while roaming
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			trianglePoint1,
			trianglePoint2)) {
			return std::make_shared<AttackingState>(enemy);
		}
		break;
	case EnemyTypes::Howler:
		
		//check sight detection in certain radius
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + 16, enemy.GetPosition().y + 16 },
			5 * 32)) {
			return std::make_shared<ApproachingState>(enemy);
		}
		break;
	default:
		

		//check line of sight while roaming
		switch (enemy.GetDirection())
		{
		case LEFT:
			enemySight = { enemy.GetPosition().x + 16 - 160, enemy.GetPosition().y + 16, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				//enter approaching state on player sight left
				return std::make_shared<ApproachingState>(enemy);
			}
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + 16, enemy.GetPosition().y + 16, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				//enter approaching state on player sight right
				return std::make_shared<ApproachingState>(enemy);
			}
			break;
		default:
			break;
		}
		break;
	}

	//change direction while roaming
	decisionTimer++;
	if (decisionTimer >= 180) {
		int decideDirection = GetRandomValue(1, 100);
		if (decideDirection < 2) {
			decisionTimer = 0;
			switch (enemy.GetDirection())
			{
			case LEFT:
				enemy.SetDirection(RIGHT);
				break;
			case RIGHT:
				enemy.SetDirection(LEFT);
				break;
			default:
				break;
			}
		}
	}


	if (enemy.GetWallCollisionLeft() && enemy.IsGrounded() && enemy.GetDirection() == LEFT && enemy.GetEnemyType() != EnemyTypes::SpiderBot) {
		enemy.SetDirection(RIGHT);
	}
	if (enemy.GetWallCollisionRight() && enemy.IsGrounded() && enemy.GetDirection() == RIGHT && enemy.GetEnemyType() != EnemyTypes::SpiderBot) {
		enemy.SetDirection(LEFT);
	}

	if (enemy.GetEnemyType() != EnemyTypes::Flyer && enemy.GetEnemyType() != EnemyTypes::SpiderBot && enemy.GetEnemyType() != EnemyTypes::SpringHog) {

		//check for ledges
		Rectangle edgeSeekerLeft = { enemy.GetPosition().x - 2, enemy.GetPosition().y + 32, 1, 1 };
		Rectangle edgeSeekerRight = { enemy.GetPosition().x + 32 + 1, enemy.GetPosition().y + 32, 1, 1 };
		tileRec = { 0,0,32,32 };
		for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
		{
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;
			if ((CheckCollisionRecs(edgeSeekerLeft, tileRec) && enemy.GetDirection() == LEFT) || (CheckCollisionRecs(edgeSeekerRight, tileRec) && enemy.GetDirection() == RIGHT)) {
				collisionCounter++;
				//moving while roaming
				switch (enemy.GetDirection())
				{
				case LEFT:
					enemy.SetPosition({ enemy.GetPosition().x - enemy.GetEnemyMovementSpeed(), enemy.GetPosition().y });
					break;
				case RIGHT:
					enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed(), enemy.GetPosition().y });
					break;
				default:
					break;
				}
			}
		}
		if (collisionCounter == 0) {
			if (enemy.GetDirection() == LEFT) {
				enemy.SetDirection(RIGHT);
			}
			else if (enemy.GetDirection() == RIGHT) {
				enemy.SetDirection(LEFT);
			}
		}

	}

	//enter idle state randomly every few seconds (0.5% chance per tick)
	int decideAction = GetRandomValue(1, 400);
	if (decideAction < 2 && enemy.GetEnemyType() != EnemyTypes::Flyer && enemy.GetEnemyType() != EnemyTypes::SpringHog) {
		return std::make_shared<IdleState>(enemy);
	}



	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}

	

	return shared_from_this();
}

void RoamingState::Draw(Enemy& enemy)
{
	if (enemy.GetEnemyType() == EnemyTypes::SpiderBot) {
		DrawTexturePro(enemy.GetTexture(), activeFrame, {enemy.GetPosition().x + 16, enemy.GetPosition().y +16, 32, 32}, { 16, 16 }, spiderBotRotation, WHITE);
	}
	else {
		DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
	}
}