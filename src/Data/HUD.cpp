#include "HUD.h"
#include "../Global.h"
#include "../Scenes/Endscreen.h"

HUD::HUD() {
    textureFire = LoadTexture("assets/graphics/HUD/fire_sprites.png");
    healthBar = {30,20, 100, 20};
    bossHealthBar = { 1000, 10, 100, 20 };
    playerHealthBar = LoadTexture("assets/graphics/HUD/PlayerHealthbar.png");
}

void HUD::UpdateHUD() {
    healthBar.width = static_cast<float>(playerCharacter->GetHealth() * 3);
    
    frameCounter++;
    if (frameCounter >= 15) {
        frameCounter = 0;
        thisFrame++;
    }
    fireFrame = { (float)16 * thisFrame, 0, 16, 16 };

    if(isEndscreenActive){
        if(endscreenCounter <= 0){
            sceneManager->SetNextScene(std::make_unique<Endscreen>(SceneEnums::Default));
            isEndscreenActive = false;
        }
        --endscreenCounter;
        ++endscreenColor.a;
    }

    bossHealthBar.width = static_cast<float>(bossHealth * 2);

    if (showNotification){
        --currentNotificationTimer;
        if (currentNotificationTimer==0){
            showNotification=false;
        }
    }
}

void HUD::DrawHUD() {
	DrawRectangle(healthBar.x, healthBar.y, 300, healthBar.height, DARKBROWN); //Draw player healthbar layers
	if (healthBar.width > 0) {
		DrawRectangleGradientH(healthBar.x, healthBar.y, healthBar.width, healthBar.height, RED, ORANGE);
	}
	DrawTexture(playerHealthBar, healthBar.x - 11, healthBar.y - 1, WHITE);
	if (healthBar.width > 0) DrawTexturePro(textureFire, fireFrame, { healthBar.width + 14, healthBar.y - 10, 32, 32 }, {}, 0.0f, WHITE);

    if(isInteractable && !sceneManager->GetActiveScene()->GetDialogueManager().GetDialogueActive()){
        DrawText("PRESS E",560,500,30,WHITE);
        isInteractable = false;
    }
    
    if(isEndscreenActive){ DrawRectangle(0,0,20000,20000,endscreenColor);}

    if (bossHealth > 0) {
        DrawRectangle(bossHealthBar.x, bossHealthBar.y, bossHealthBar.width, bossHealthBar.height, RED);
    }

    if (showNotification) {
        DrawTextEx(GetFontDefault(), "Game Saved", {1280.f/2.f-(2.5f*45.f), 200.f}, 45.f, 1.f, WHITE);
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

void HUD::ShowSaveNotification() {
    showNotification=true;
    currentNotificationTimer=notificationTimer;

}
