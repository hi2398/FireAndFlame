#include "BackgroundManager.h"

BackgroundManager::BackgroundManager()
{
    textureForeground = LoadTexture("assets/graphics/backgrounds/background1.png");
    textureMiddleground = LoadTexture("assets/graphics/backgrounds/background2.png");
    textureBackground = LoadTexture("assets/graphics/backgrounds/background3.png");
}

void BackgroundManager::Parallax(int direction)
{
    scrollingFore -= 0.0f * direction;
    scrollingMiddle += 0.5f * direction;
    scrollingBack += 0.1f * direction;

    if (scrollingBack <= -textureBackground.width) scrollingBack = 0;
    if (scrollingMiddle <= -textureMiddleground.width) scrollingMiddle = 0;
    if (scrollingFore <= -textureForeground.width) scrollingFore = 0;
}

void BackgroundManager::Draw()
{
   /* DrawTextureEx(textureBackground, { scrollingBack, -300 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(textureBackground, { textureBackground.width + scrollingBack , -300 }, 0.0f, 1.0f, WHITE);

    DrawTextureEx(textureMiddleground, { scrollingMiddle, -300 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(textureMiddleground, { textureMiddleground.width + scrollingMiddle , -300 }, 0.0f, 1.0f, WHITE);

    DrawTextureEx(textureForeground, { scrollingFore, -300 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(textureForeground, { textureForeground.width + scrollingFore , -300 }, 0.0f, 1.0f, WHITE);*/
}


