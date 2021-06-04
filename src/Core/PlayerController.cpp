
#include "PlayerController.h"

void PlayerController::HandleInput() {
	if (IsKeyDown(KEY_D)) playerCharacter->Move(right);
	if (IsKeyDown(KEY_A)) playerCharacter->Move(left);
	if (IsKeyPressed(KEY_ENTER)) playerCharacter->Attack();
	if (IsKeyDown(KEY_ENTER)) playerCharacter->ChargingAttack();
	if (IsKeyReleased(KEY_ENTER)) playerCharacter->ChargedAttack();
	if (IsKeyPressed(KEY_F)) playerCharacter->Fireball();
	if (IsKeyPressed(KEY_SPACE)) playerCharacter->Jump();
}
