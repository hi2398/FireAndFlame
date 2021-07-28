#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "StunnedState.h"

#include "raymath.h"

ApproachingState::ApproachingState(Enemy& enemy) : EState(enemy)
{
}

std::shared_ptr<EState> ApproachingState::Update(Enemy& enemy)
{

	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Approaching\n";
	}
	//frameCounter for animation
	approachingFrameCounter++;


	Rectangle enemySight;
	//Vector points for triangle sight
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };

	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		//check line of sight in approaching
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + enemy.GetTexture().width/2, enemy.GetPosition().y + enemy.GetTexture().height/2}, 
			trianglePoint1, 
			trianglePoint2)) {
			return std::make_shared<AttackingState>(enemy);
		}
		return std::make_shared<RoamingState>(enemy);
		break;
	case EnemyTypes::Howler:


		//chase Player & stop on ledge
		edgeSeekerLeft = { enemy.GetPosition().x - 1, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		edgeSeekerRight = { enemy.GetPosition().x + enemy.GetTexture().width, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		Vector2 movingToPlayer;
		movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (movingToPlayer.x > 0) movingDistance = enemy.GetEnemyMovementSpeed() * 1.5, enemy.SetDirection(RIGHT);
		else if (movingToPlayer.x < 0) movingDistance = -enemy.GetEnemyMovementSpeed() * 1.5, enemy.SetDirection(LEFT);

		for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
		{
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			
			if (CheckCollisionRecs(edgeSeekerLeft, tileRec)) {
				collCheckLeft++;
			}
			if (CheckCollisionRecs(edgeSeekerRight, tileRec)) {
				collCheckRight++;
			}
			


		}

		if ((collCheckLeft == 0 || collCheckRight == 0) && enemy.IsGrounded()) {
			enemy.SetPosition({ enemy.GetPosition().x + enemy.GetEnemyMovementSpeed() * 3 * enemy.GetDirection(), enemy.GetPosition().y - howlerJumpSpeed});
			howlerJumpSpeed -= 0.1f;
		}
		else {
			enemy.SetPosition({ enemy.GetPosition().x + movingDistance, enemy.GetPosition().y });
		}


		

		break;
	default:
			

		//check line of sight in approaching
		switch (enemy.GetDirection())
		{
		case LEFT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2 - 160, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			break;
		default:
			break;
		}
		
		//chase Player & stop on ledge
		edgeSeekerLeft = { enemy.GetPosition().x - 1, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		edgeSeekerRight = { enemy.GetPosition().x + enemy.GetTexture().width, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		for (const auto& collTile : sceneManager->GetTilemap()->GetTileColliders())
		{
			tileRec.x = collTile.x;
			tileRec.y = collTile.y;

			Vector2 movingToPlayer;
			movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
			if (movingToPlayer.x > 0) movingDistance = enemy.GetEnemyMovementSpeed()*1.5, enemy.SetDirection(RIGHT);
			else if (movingToPlayer.x < 0) movingDistance = -enemy.GetEnemyMovementSpeed()*1.5, enemy.SetDirection(LEFT);

			//stop follow player over ledge
			if ((CheckCollisionRecs(edgeSeekerLeft, tileRec) && enemy.GetDirection() == LEFT) || (CheckCollisionRecs(edgeSeekerRight, tileRec) && enemy.GetDirection() == RIGHT)) {
				enemy.SetPosition({ enemy.GetPosition().x + movingDistance, enemy.GetPosition().y });
			}
			
		}


		//enter idle when losing aggro after 5 secs
		if (aggroCooldown >= 300) {
			return std::make_shared<RoamingState>(enemy);
		}

		//enter attacking state when in range
		if (CheckCollisionRecs(playerCharacter->playerHitbox, enemy.GetAttackHitbox())) {
			return std::make_shared<AttackingState>(enemy);
		}

		break;
	}

	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}


	return shared_from_this();
}

void ApproachingState::Draw(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) {
		DrawLine(trianglePoint1.x, trianglePoint1.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint2.x, trianglePoint2.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint1.x, trianglePoint1.y, trianglePoint2.x, trianglePoint2.y, GREEN);
	}
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
