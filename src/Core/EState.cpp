#include "EState.h"

EState::EState(Enemy& enemy) {
	activeFrame.width = 32 * enemy.GetDirection();

}