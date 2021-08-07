#include "EState.h"

EState::EState(Enemy& enemy) {
	
	activeFrame = {0,0,(float) -32 * enemy.GetDirection(), 32 };
	
}