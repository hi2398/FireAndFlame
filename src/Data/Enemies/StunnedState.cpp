#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "StunnedState.h"


StunnedState::StunnedState(Enemy& enemy) : EState(enemy)
{
	activeFrame = { 0,32 * 3, (float)-32 * enemy.GetDirection(), 32 };
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
	return  shared_from_this();
}

void StunnedState::Draw(Enemy& enemy) {
	DrawTextureRec(enemy.GetTexture(),activeFrame, { enemy.GetPosition().x + stunnedOffset, enemy.GetPosition().y }, WHITE);
}