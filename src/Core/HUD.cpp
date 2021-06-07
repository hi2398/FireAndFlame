#include "HUD.h"
#include "../Global.h"

HUD::HUD() {
    healthBar = {10,10, 100, 10};
}

void HUD::UpdateHUD() {
    healthBar.width = playerCharacter->GetHealth() * 2;
}

void HUD::DrawHUD() {
    if (healthBar.width > 0) {
		DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, RED);
    }
    
}
