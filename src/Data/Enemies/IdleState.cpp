#include "IdleState.h"
#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "StunnedState.h"

IdleState::IdleState(Enemy& enemy) : EState(enemy)
{
}

std::shared_ptr<EState> IdleState::Update(Enemy& enemy)
{
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Idle\n";
	}
	//frameCounter for animation
	idleFrameCounter++;
	
	Rectangle enemySight;
	int decision;

	//Vector points for triangle sight
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };
	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		//check line of sight in idle
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(), 
			{ enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2 },
			trianglePoint1, 
			trianglePoint2)) {
			return std::make_shared<AttackingState>(enemy);
		}
		decision = GetRandomValue(1, 100);
		if (decision < 2) {
			return std::make_shared<RoamingState>(enemy);
		}
		break;
	default:
		
		
		//check line of sight in idle
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
		decision = GetRandomValue(1, 100);
		if (decision < 2) {
			return std::make_shared<RoamingState>(enemy);
		}
		break;
	}

	if (enemy.IsInvulnerable()) {
		return std::make_shared<StunnedState>(enemy);
	}
	
	return shared_from_this();
}

void IdleState::Draw(Enemy& enemy)
{

	if constexpr (DEBUG_ENEMY_STATES) {
		DrawLine(trianglePoint1.x, trianglePoint1.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint2.x, trianglePoint2.y, enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2, GREEN);
		DrawLine(trianglePoint1.x, trianglePoint1.y, trianglePoint2.x, trianglePoint2.y, GREEN);
	}
	


	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
