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
	roamingFrameCounter++;


	Rectangle enemySight;
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		//check line of sight while roaming
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(), 
			{ enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2 }, 
			trianglePoint1, 
			trianglePoint2)) {
			return std::make_shared<AttackingState>(enemy);
		}


		break;
	default:
		

		//check line of sight while roaming
		switch (enemy.GetDirection())
		{
		case LEFT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2 - 160, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				//enter approaching state on player sight left
				return std::make_shared<ApproachingState>(enemy);
			}
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
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
		if (decideDirection < 2 && !enemy.GetWallCollisionLeft() && !enemy.GetWallCollisionRight()) {
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


	if (enemy.GetWallCollisionLeft() && enemy.GetDirection() == LEFT) {
		enemy.SetDirection(RIGHT);
	}
	if (enemy.GetWallCollisionRight() && enemy.GetDirection() == RIGHT) {
		enemy.SetDirection(LEFT);
	}

	//check for ledges
	Rectangle edgeSeekerLeft = { enemy.GetPosition().x - 2, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
	Rectangle edgeSeekerRight = { enemy.GetPosition().x + enemy.GetTexture().width + 1, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
	Rectangle tileRec = { 0,0,32,32 };
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

	//enter idle state randomly every few seconds (0.5% chance per tick)
	int decideAction = GetRandomValue(1, 400);
	if (decideAction < 2) {
		return std::make_shared<IdleState>(enemy);
	}



	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}

	return shared_from_this();
}

void RoamingState::Draw(Enemy& enemy)
{

	if constexpr (DEBUG_ENEMY_STATES) {
		DrawLine(trianglePoint1.x, trianglePoint1.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint2.x, trianglePoint2.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint1.x, trianglePoint1.y, trianglePoint2.x, trianglePoint2.y, GREEN);
	}
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
