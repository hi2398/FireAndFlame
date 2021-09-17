
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
    Scene::Update();
    if(IsGamepadAvailable(0)){
        isControllerActive = true;
    }else {isControllerActive = false;}
    if(IsKeyPressed(KEY_E) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
        sceneManager->LoadGame("./Saves/", sceneManager->GetSaveSlot());
    }
    
    if (FADEOUT.a == 105) soundManager->PlaySfx(SFX::DEATHSCREEN);
}

void DeathScreen::Draw() {
    Scene::Draw();
    DrawTexture(background,0,0,WHITE);
    DrawText("You Died",485,100,60,WHITE);
    if(isControllerActive){
        DrawText("Press Gamepad A to continue", 440,250,25,WHITE);
    }else{DrawText("Press E to continue", 490,250,25,WHITE);}
}

DeathScreen::~DeathScreen() {
    UnloadTexture(background);
}