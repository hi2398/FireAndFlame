#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "RoamingState.h"

std::shared_ptr<EState> RoamingState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_BUILD) {
		std::cout << "Enemy State: Roaming\n";
	}

	switch (enemy.GetEnemyType())
	{
	default:
		//frameCounter for animation
		roamingFrameCounter++;

		//check line of sight in idle
		Rectangle enemySight;
		switch (enemy.GetDirection())
		{
		case LEFT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2 - 160, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				//enter approaching state on player sight left
				return std::make_shared<ApproachingState>();
			}
			drawRec = enemySight;
			break;
		case RIGHT:
			enemySight = { enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, 160, 5 };
			if (CheckCollisionRecs(playerCharacter->playerHitbox, enemySight)) {
				//enter approaching state on player sight right
				return std::make_shared<ApproachingState>();
			}
			drawRec = enemySight;
			break;
		default:
			break;
		}
		int decision = GetRandomValue(1, 200);
		if (decision < 2) {
			return std::make_shared<IdleState>();
		}
		break;
	}

	return shared_from_this();
}

void RoamingState::Draw(Enemy& enemy)
{
	DrawTexture(enemy.GetTexture(), enemy.GetPosition().x, enemy.GetPosition().y, WHITE);
	DrawRectangle(drawRec.x, drawRec.y, drawRec.width, drawRec.height, RED);
}
