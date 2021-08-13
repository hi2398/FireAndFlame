#include "HUD.h"
#include "../Global.h"
#include "../Scenes/Endscreen.h"

HUD::HUD() {
    textureFire = LoadTexture("assets/graphics/Fire.png");
    healthBar = {10,10, 100, 20};
    bossHealthBar = { 1000, 10, 100, 20 };
}

void HUD::UpdateHUD() {
    healthBar.width = static_cast<float>(playerCharacter->GetHealth() * 2);
    
    if(isEndscreenActive){
        if(endscreenCounter <= 0){
            sceneManager->SetNextScene(std::make_unique<Endscreen>());
            isEndscreenActive = false;
        }
        --endscreenCounter;
        ++endscreenColor.a;
    }

    bossHealthBar.width = static_cast<float>(bossHealth * 2);
}

void HUD::DrawHUD() {
    DrawRectangle(healthBar.x, healthBar.y, 200, healthBar.height, GRAY);
    if (healthBar.width > 0) {
		DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, RED);
    }
    if(isInteractable){
        DrawText("PRESS E",600,500,30,WHITE);
        isInteractable = false;
    }
    DrawRectangleLines(healthBar.x, healthBar.y, 200, healthBar.height, BLACK);
    if (healthBar.width > 0) DrawTextureEx(textureFire, { healthBar.width - textureFire.width/2, healthBar.y - 10 }, 0.0f, 2.0f, WHITE);
    if(isEndscreenActive){ DrawRectangle(0,0,20000,20000,endscreenColor);}

    if (bossHealth > 0) {
        DrawRectangle(bossHealthBar.x, bossHealthBar.y, bossHealthBar.width, bossHealthBar.height, RED);
    }
}

void HUD::changeInteractable(bool interactable) {
    isInteractable = interactable;
}

void HUD::executeEndscreenSwap() {
    isEndscreenActive = true;
}

void HUD::SetBossEnemyHealth(int bossHealth)
{
    this->bossHealth = bossHealth;
}
