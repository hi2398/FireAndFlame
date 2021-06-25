#include "PlayerController.h"
#include "../Global.h"
#include "raylib.h"

void PlayerController::HandleInput() {
    //player movement
	if (IsKeyDown(KEY_D)) Notify(EVENT::MOVE_RIGHT), sceneManager->SceneParallax(right);
	if (IsKeyDown(KEY_A)) Notify(EVENT::MOVE_LEFT), sceneManager->SceneParallax(left);
    if (!playerCharacter->GetHeadCollision()) if (IsKeyPressed(KEY_SPACE)) Notify(EVENT::JUMP);

    //player actions
	if (IsKeyPressed(KEY_ENTER)) Notify(EVENT::MELEE_ATTACK);
	//TODO: Charged attacks not working
	if (IsKeyPressed(KEY_F)) Notify(EVENT::RANGED_ATTACK);


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
