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
	stateFrameCounter++;
	
	Rectangle enemySight;

	//Vector points for triangle sight
	trianglePoint1 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y - 32 * 3 };
	trianglePoint2 = { enemy.GetPosition().x + (32 * 5 * enemy.GetDirection()), enemy.GetPosition().y + 32 * 4 };
	switch (enemy.GetEnemyType())
	{
	case EnemyTypes::ToastCat:
		//frame handling
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		activeFrame = {};

		//check line of sight in idle
		if (CheckCollisionPointTriangle(playerCharacter->GetPosition(), 
			{ enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2 },
			trianglePoint1, 
			trianglePoint2)) {
			return std::make_shared<AttackingState>(enemy);
		}
		break;
	case EnemyTypes::Howler:
		//check sight detection in certain radius
		if (CheckCollisionPointCircle(playerCharacter->GetPosition(),
			{ enemy.GetPosition().x + enemy.GetTexture().width / 2, enemy.GetPosition().y + enemy.GetTexture().height / 2 },
			5 * 32)) {
			return std::make_shared<ApproachingState>(enemy);
		}
		if (stateFrameCounter >= 15) {
			thisFrame++;
			stateFrameCounter = 0;
		}
		if (thisFrame == 2) thisFrame = 0;
		activeFrame = {(float) 32 * thisFrame, 32 * 0 ,(float)- 32 * enemy.GetDirection(), 32};
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
		break;
	}

	//every enemy enters this part
	int decision = GetRandomValue(1, 100);
	if (decision < 2) {
		return std::make_shared<RoamingState>(enemy);
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
	


	DrawTextureRec(enemy.GetTexture(), activeFrame, { enemy.GetPosition().x, enemy.GetPosition().y }, WHITE);
}
