#include "EState.h"

EState::EState(Enemy& enemy) {
	/*if (enemy.GetEnemyType() == EnemyTypes::Howler) {
		activeFrame = {0, 0, (float) 38 * enemy.GetDirection(), 32};
	}
	else {*/
		activeFrame.width = -32 * enemy.GetDirection();
	/*}*/
}