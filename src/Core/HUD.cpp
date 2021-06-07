#include "HUD.h"
#include "../Global.h"

HUD::HUD() {
    textureFire = LoadTexture("assets/graphics/Fire.png");
    healthBar = {10,10, 100, 10};
}

void HUD::UpdateHUD() {
    healthBar.width = playerCharacter->GetHealth() * 2;
}

void HUD::DrawHUD() {
    DrawRectangle(healthBar.x, healthBar.y, 200, healthBar.height, GRAY);
    if (healthBar.width > 0) {
		DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, RED);
    }
    DrawRectangleLines(healthBar.x, healthBar.y, 200, healthBar.height, BLACK);
    if (healthBar.width > 0) DrawTexture(textureFire, healthBar.width, healthBar.y - 5, WHITE);
}
