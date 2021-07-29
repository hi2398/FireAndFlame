#include "HUD.h"
#include "../Global.h"
#include "../Scenes/Endscreen.h"

HUD::HUD() {
    textureFire = LoadTexture("assets/graphics/Fire.png");
    healthBar = {10,10, 100, 20};
}

void HUD::UpdateHUD() {
    healthBar.width = static_cast<float>(playerCharacter->GetHealth() * 2);
    if(isEndscreenActive){
        if(endscreenCounter <= 0){
            sceneManager->SetNextScene(std::make_unique<Endscreen>());
        }
        --endscreenCounter;
        ++endscreenColor.a;
    }
}

void HUD::DrawHUD() {
    DrawRectangle(healthBar.x, healthBar.y, 200, healthBar.height, GRAY);
    if (healthBar.width > 0) {
		DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, RED);
    }
    if(isInteractable){
        DrawText("PRESS F",600,500,30,WHITE); //TODO Change after controls are fixed
        isInteractable = false;
    }
    DrawRectangleLines(healthBar.x, healthBar.y, 200, healthBar.height, BLACK);
    if (healthBar.width > 0) DrawTextureEx(textureFire, { healthBar.width - textureFire.width/2, healthBar.y - 10 }, 0.0f, 2.0f, WHITE);
    if(isEndscreenActive){ DrawRectangle(0,0,20000,20000,endscreenColor);}
}

void HUD::changeInteractable(bool interactable) {
    isInteractable = interactable;
}

void HUD::executeEndscreenSwap() {
    isEndscreenActive = true;
}
