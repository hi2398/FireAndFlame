
#include "DeathScreen.h"
#include "NeutralArea.h"
#include "../Global.h"

DeathScreen::DeathScreen(SceneEnums lastScene) : Scene(SceneEnums::Default) {
    this->lastScene = lastScene;
    tilemap=std::make_unique<Tilemap>();
    background = LoadTexture("assets/graphics/GUI/deathScreen.png");
    playerCharacter->active = false; // Disables Player
}

void DeathScreen::Update() {
    if(IsKeyPressed(KEY_E) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
        sceneManager->SetNextScene(std::make_unique<NeutralArea>(sceneName)); // TODO Load Save :Adrian:
    }
    if (FADEOUT.a > 0)FADEOUT.a -= 3;
    if (FADEOUT.a < 0) FADEOUT.a = 0;
    if (FADEOUT.a == 105) soundManager->PlaySfx(SFX::DEATHSCREEN);
}

void DeathScreen::Draw() {
    DrawTexture(background,0,0,WHITE);
    DrawText("You Died",485,100,60,WHITE);
    DrawText("Press E or Gamepad A to continue", 410,250,25,WHITE);
    DrawRectangle(-100,-100, 10000, 10000, FADEOUT);
}
