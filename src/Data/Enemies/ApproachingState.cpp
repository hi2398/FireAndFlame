#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
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
			drawRec = enemySight;
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				aggroCooldown = 0;
			}
			else {
				aggroCooldown++;
			}
			drawRec = enemySight;
			break;
		default:
			break;
		}

		//moving while aggro
		Vector2 movingToPlayer = Vector2Subtract(playerCharacter->GetPosition(), enemy.GetPosition());
		if (movingToPlayer.x > 0) movingDistance = 1.0f;
		else if (movingToPlayer.x < 0) movingDistance = -1.0f;

		enemy.SetPosition({enemy.GetPosition().x + movingDistance, enemy.GetPosition().y});

		//enter idle when losing aggro after 5 secs
		if (aggroCooldown >= 300) {
			return std::make_shared<IdleState>();
		}

		break;
	}

	return shared_from_this();
}

void ApproachingState::Draw(Enemy& enemy)
{
	DrawTexture(enemy.GetTexture(), enemy.GetPosition().x, enemy.GetPosition().y, WHITE);
	DrawRectangle(drawRec.x, drawRec.y, drawRec.width, drawRec.height, RED);
	DrawText(TextFormat("%f", enemy.GetPosition().x), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 50, 30, RED);
}
