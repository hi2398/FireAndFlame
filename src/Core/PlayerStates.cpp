#include "PlayerStates.h"

PlayerStates::PlayerStates(Actor& player) {
	activeFrame = { 0,0, (float)32 * player.GetDirection(), 32 };
}