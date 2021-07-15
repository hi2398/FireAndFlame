#include "BackgroundManager.h"
#include "../Global.h"
#include "raymath.h"

void BackgroundManager::Parallax()
{
    if (skipFrame > 0) {
		tmp1 = playerCharacter->GetLastPosition();
		tmp2 = playerCharacter->GetPosition();
		Vector2 scrollDirection = { tmp2.x - tmp1.x, tmp2.y - tmp1.y };

        drawFore = Vector2Add(drawFore, Vector2Multiply(scrollDirection, {0.3f, 0.1f}));
        drawMiddle = Vector2Add(drawMiddle, Vector2Multiply(scrollDirection, { 0.2f, 0.05f }));
        drawBack = Vector2Add(drawBack, Vector2Multiply(scrollDirection, { 0.1f, 0.0f }));
    }
    
    
    skipFrame++;
}

void BackgroundManager::SetBackgrounds(Vector2 vecFore, Vector2 vecMiddle, Vector2 vecBack) {
    

    drawFore = vecFore;
    drawMiddle = vecMiddle;
    drawBack = vecBack;
}

void BackgroundManager::Draw()
{
    DrawTextureEx(textureB, drawBack, 0, 1.0f, WHITE);
    DrawTextureEx(textureM, drawMiddle, 0, 1.0f, WHITE);
    DrawTextureEx(textureF, drawFore, 0, 1.0f, WHITE);
}