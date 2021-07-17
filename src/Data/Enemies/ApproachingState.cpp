#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "StunnedState.h"

#include "raymath.h"

std::shared_ptr<EState> ApproachingState::Update(Enemy& enemy)
{

	if constexpr (DEBUG_BUILD) {
		std::cout << "Enemy State: Approaching\n";
	}


	switch (enemy.GetEnemyType())
	{
	default:
		//frameCounter for animation
		approachingFrameCounter++;

		//check line of sight in idle
		Rectangle enemySight;
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
		Rectangle edgeSeekerLeft = { enemy.GetPosition().x - 1, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		Rectangle edgeSeekerRight = { enemy.GetPosition().x + enemy.GetTexture().width, enemy.GetPosition().y + enemy.GetTexture().height, 1, 1 };
		Rectangle tileRec = { 0,0,32,32 };
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
			return std::make_shared<RoamingState>();
		}

		//enter attacking state when in range
		if (CheckCollisionRecs(playerCharacter->playerHitbox, enemy.GetAttackHitbox())) {
			return std::make_shared<AttackingState>();
		}

		break;
	}

	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>();
	}


	return shared_from_this();
}

void ApproachingState::Draw(Enemy& enemy)
{
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
