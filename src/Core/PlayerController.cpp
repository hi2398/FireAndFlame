#include "PlayerController.h"
#include "../Global.h"
#include "raylib.h"

void PlayerController::HandleInput() {
    //player movement
	if (IsKeyDown(KEY_D)) Notify(EVENT::MOVE_RIGHT), sceneManager->SceneParallax(right);
	if (IsKeyDown(KEY_A)) Notify(EVENT::MOVE_LEFT), sceneManager->SceneParallax(left);
    if ((IsKeyDown(KEY_D) && IsKeyPressed(KEY_LEFT_CONTROL) ||
        playerCharacter->GetIsDashing() && playerCharacter->GetDirection() == RIGHT) && playerCharacter->GetCanDash()) Notify(EVENT::DASH_RIGHT);

    if ((IsKeyDown(KEY_A) && IsKeyPressed(KEY_LEFT_CONTROL) ||
        playerCharacter->GetIsDashing() && playerCharacter->GetDirection() == LEFT) && playerCharacter->GetCanDash()) Notify(EVENT::DASH_LEFT);

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        playerCharacter->SetIsRunning(true);
    }
    else {
        playerCharacter->SetIsRunning(false);
    }
    //jump commands
    if ((!playerCharacter->GetHeadCollision() && playerCharacter->IsGrounded()) ||
        (!playerCharacter->GetHeadCollision() && playerCharacter->GetCanDoubleJump() == true && playerCharacter->GetTimesJumped() < 2)
        ) {
        if (IsKeyPressed(KEY_SPACE)) Notify(EVENT::JUMP);
    }
    if (playerCharacter->GetWallCollisionLeft() && !playerCharacter->IsGrounded() ||
        playerCharacter->GetWallCollisionRight() && !playerCharacter->IsGrounded()) {
        if (IsKeyPressed(KEY_SPACE)) Notify(EVENT::WALL_JUMP);
    }

    //player actions
	if (IsKeyPressed(KEY_ENTER)) Notify(EVENT::MELEE_ATTACK);
	//TODO: Charged attacks not working
	if (IsKeyPressed(KEY_F)) Notify(EVENT::RANGED_ATTACK);


    if(DEBUG_BUILD) {
        if (IsKeyDown(KEY_UP)) playerCharacter->camera.zoom += 0.1f;
        if (IsKeyDown(KEY_DOWN)) playerCharacter->camera.zoom -= 0.1f;

        //toggle Double Jump
        if (playerCharacter->GetCanDoubleJump() == true) {
            if (IsKeyReleased(KEY_J)) playerCharacter->SetCanDoubleJump(false);
        }
        else if (playerCharacter->GetCanDoubleJump() == false) {
            if (IsKeyReleased(KEY_J)) playerCharacter->SetCanDoubleJump(true);
        }
    }
}

PlayerController::PlayerController() {
    AddObserver(playerCharacter->GetObserver());
}

PlayerController::~PlayerController() {
    RemoveObserver(playerCharacter->GetObserver());

}
