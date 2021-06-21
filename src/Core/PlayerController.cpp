#include "PlayerController.h"
#include "../Global.h"
#include "raylib.h"

void PlayerController::HandleInput() {
    //player movement
	if (IsKeyDown(KEY_D)) Notify(Event::MOVE_RIGHT), sceneManager->SceneParallax(right);
	if (IsKeyDown(KEY_A)) Notify(Event::MOVE_LEFT), sceneManager->SceneParallax(left);
    if (IsKeyPressed(KEY_SPACE)) Notify(Event::JUMP);

    //player actions
	if (IsKeyPressed(KEY_ENTER)) playerCharacter->Attack();
	if (IsKeyDown(KEY_ENTER)) playerCharacter->ChargingAttack();
	if (IsKeyReleased(KEY_ENTER)) playerCharacter->ChargedAttack();
	if (IsKeyPressed(KEY_F)) playerCharacter->Fireball();


    if(DEBUG_BUILD) {
        if (IsKeyDown(KEY_UP)) playerCharacter->camera.zoom += 0.1f;
        if (IsKeyDown(KEY_DOWN)) playerCharacter->camera.zoom -= 0.1f;
    }
}

PlayerController::PlayerController() {
    AddObserver(playerCharacter->GetObserver());
}

PlayerController::~PlayerController() {
    RemoveObserver(playerCharacter->GetObserver());

}
