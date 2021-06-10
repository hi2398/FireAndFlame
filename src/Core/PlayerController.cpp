#include "PlayerController.h"
#include "../Global.h"
#include "raylib.h"

void PlayerController::HandleInput() {
	if (IsKeyDown(KEY_D)) playerCharacter->Move(right), sceneManager->SceneParallax(right);
	if (IsKeyDown(KEY_A)) playerCharacter->Move(left), sceneManager->SceneParallax(left);
	if (IsKeyDown(KEY_UP)) playerCharacter->camera.zoom += 0.1f;
	if (IsKeyDown(KEY_DOWN)) playerCharacter->camera.zoom -= 0.1f;
	if (IsKeyPressed(KEY_ENTER)) playerCharacter->Attack();
	if (IsKeyDown(KEY_ENTER)) playerCharacter->ChargingAttack();
	if (IsKeyReleased(KEY_ENTER)) playerCharacter->ChargedAttack();
	if (IsKeyPressed(KEY_F)) playerCharacter->Fireball();
	if (IsKeyPressed(KEY_SPACE)) playerCharacter->Jump();
}
