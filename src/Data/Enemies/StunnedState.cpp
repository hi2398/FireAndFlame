#include "../../Core/Enemy.h"
#include "../../../src/Global.h"
#include "ApproachingState.h"
#include "StunnedState.h"


StunnedState::StunnedState(Enemy& enemy) : EState(enemy)
{
}

std::shared_ptr<EState> StunnedState::Update(Enemy& enemy) {
	if constexpr (DEBUG_ENEMY_STATES) {
		std::cout << "Enemy State: Stunned\n";
	}

	switch (enemy.GetEnemyType())
	{
	default:
		stunnedFrameCounter++;

		if (stunnedFrameCounter >= 30) {
			return std::make_shared<ApproachingState>(enemy);
		}
	}
	return  shared_from_this();
}

void StunnedState::Draw(Enemy& enemy) {
	if (stunnedFrameCounter % 16) {
		if (stunnedOffset == 0) stunnedOffset = 2;
		else if (stunnedOffset == 2) stunnedOffset = 0;
	}
	DrawTextureRec(enemy.GetTexture(), { 0,0, (float)enemy.GetTexture().width * -enemy.GetDirection(), (float)enemy.GetTexture().height }, { enemy.GetPosition().x + stunnedOffset, enemy.GetPosition().y }, WHITE);
}