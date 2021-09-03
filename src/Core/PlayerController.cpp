#include "PlayerController.h"
#include "../Global.h"
#include "raylib.h"


void PlayerController::HandleInput() {
    if (!playerCharacter->InputDisabled()) {
        //player walking
        if (IsKeyDown(KEY_D) || (float)GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0) Notify(EVENT::MOVE_RIGHT);
        if (IsKeyDown(KEY_A) || (float)GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < 0) Notify(EVENT::MOVE_LEFT);


        //player dashing
        if (playerCharacter->DashReady() && playerCharacter->IsDashUnlocked()) {
			if ((IsKeyDown(KEY_D) && IsKeyPressed(KEY_LEFT_CONTROL) && playerCharacter->GetCanDash() ||
				((int)GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0 && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) && playerCharacter->GetCanDash() ||
				playerCharacter->GetIsDashing() && playerCharacter->GetDirection() == RIGHT)) Notify(EVENT::DASH_RIGHT);

			if ((IsKeyDown(KEY_A) && IsKeyPressed(KEY_LEFT_CONTROL) && playerCharacter->GetCanDash() ||
				((int)GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < 0 && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) && playerCharacter->GetCanDash() ||
				playerCharacter->GetIsDashing() && playerCharacter->GetDirection() == LEFT)) Notify(EVENT::DASH_LEFT);
        }

       



        //player jumping
        if (playerCharacter->GetWallCollisionLeft() && !playerCharacter->IsGrounded() ||
            playerCharacter->GetWallCollisionRight() && !playerCharacter->IsGrounded()) {
            if (IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) Notify(EVENT::WALL_JUMP);
        }
        else if ((!playerCharacter->GetHeadCollision() && playerCharacter->IsGrounded()) ||
            (!playerCharacter->GetHeadCollision() && playerCharacter->GetCanDoubleJump() && playerCharacter->GetTimesJumped() < 2)
            ) {
            if (IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) Notify(EVENT::JUMP);
        }



        //player actions
        if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) Notify(EVENT::MELEE_ATTACK);
        //TODO: Charged attacks not working
        if (IsKeyPressed(KEY_F) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) Notify(EVENT::RANGED_ATTACK);

        //debug controls
        if (DEBUG_BUILD) {
            if (IsKeyDown(KEY_UP)) playerCharacter->camera.zoom += 0.1f;
            if (IsKeyDown(KEY_DOWN)) playerCharacter->camera.zoom -= 0.1f;

            //toggle Double Jump
            if (playerCharacter->GetCanDoubleJump()) {
                if (IsKeyReleased(KEY_J)) playerCharacter->SetCanDoubleJump(false);
            }
            else if (!playerCharacter->GetCanDoubleJump()) {
                if (IsKeyReleased(KEY_J)) playerCharacter->SetCanDoubleJump(true);
            }

            //running

            if (IsKeyDown(KEY_LEFT_SHIFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) {
                playerCharacter->SetIsRunning(true);
            }
            else {
                playerCharacter->SetIsRunning(false);
            }
        }
    }
}

PlayerController::PlayerController() {

    AddObserver(playerCharacter->GetObserver());
}

PlayerController::~PlayerController() {
    RemoveObserver(playerCharacter->GetObserver());
}
