#include "HUD.h"
#include "../Global.h"
#include "../Scenes/Endscreen.h"

HUD::HUD() {
    textureFire = LoadTexture("assets/graphics/HUD/fire_sprites.png");
    healthBar = {30,20, 100, 20};
    bossHealthBar = { 930, 20, 300, 20 };
    bossHealthPos = bossHealthBar.x;
    playerHealthBar = LoadTexture("assets/graphics/HUD/PlayerHealthbar.png");
    skull = LoadTexture("assets/graphics/HUD/skull.png");
}

void HUD::UpdateHUD() {
    if(IsGamepadAvailable(0)){
        isGameadActive = true;
    }else{
        isGameadActive = false;
    }
    healthBar.width = static_cast<float>(playerCharacter->GetHealth() * 3);
    
    frameCounter++;
    if (frameCounter >= 15) {
        frameCounter = 0;
        thisFrame++;
    }
    fireFrame = { (float)16 * thisFrame, 0, 16, 16 };
    skullFrame = { (float)16 * thisFrame, 0, 16, 16 };

    if(isEndscreenActive){
        if(endscreenCounter <= 0){
            sceneManager->SetNextScene(std::make_unique<Endscreen>(SceneEnums::Default));
            isEndscreenActive = false;
        }
        --endscreenCounter;
        ++endscreenColor.a;
    }

    bossHealthBar.width = static_cast<float>(bossHealth * bossBarMultiplier);
	bossHealthPos = bossHealthBar.x + 300 - bossHealthBar.width;

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
        if(!isGameadActive){
            DrawText("PRESS E",560,500,30,WHITE);
        } else DrawText("PRESS GAMEPAD Y",520,500,30,WHITE);
        isInteractable = false;
    }
    
    if(isEndscreenActive){ DrawRectangle(0,0,20000,20000,endscreenColor);}

    if (bossHealth > 0 && isBossFightActive) {
        DrawRectangle(bossHealthBar.x, bossHealthBar.y, 300, bossHealthBar.height, DARKBROWN);
        DrawRectangle(bossHealthPos, bossHealthBar.y, bossHealthBar.width, bossHealthBar.height, DARKPURPLE);
        DrawTextureRec(playerHealthBar, {0,0, -323, 22}, { bossHealthBar.x - 11, bossHealthBar.y - 1 }, WHITE);
        DrawTexturePro(skull, skullFrame, { bossHealthPos - 16, healthBar.y - 7, 32, 32 }, {}, 0.0f, WHITE);
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

void HUD::SetBossEnemyHealth(int bossHealth, float multiplier)
{
    this->bossHealth = bossHealth;
    this->bossBarMultiplier = multiplier;
}

void HUD::ShowSaveNotification() {
    showNotification=true;
    currentNotificationTimer=notificationTimer;

}

void HUD::IsBossFightActive(bool isActive)
{
    isBossFightActive = isActive;
}

HUD::~HUD()
{
    UnloadTexture(textureFire);
    UnloadTexture(skull);
    UnloadTexture(playerHealthBar);
}
