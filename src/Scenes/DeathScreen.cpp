
#include "DeathScreen.h"
#include "NeutralArea.h"
#include "../Global.h"

DeathScreen::DeathScreen() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->active = false; // Disables Player
}

void DeathScreen::Update() {
    if(IsKeyPressed(KEY_F) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
        sceneManager->SetNextScene(std::make_unique<NeutralArea>());
    }
}

void DeathScreen::Draw() { // TODO Rework Death Screen looks
    DrawText("YU DED",570,200,40,WHITE);
    DrawText("Press F or Gamepad A to continue", 440,500,25,WHITE);
}
