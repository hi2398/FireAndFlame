#pragma once
#include "raylib.h"
class BackgroundManager {
public:
	BackgroundManager();
	void Parallax(int direction);
	void Draw();
	~BackgroundManager() = default;
protected:

private:
    //Test background
    Texture2D textureForeground;
    Texture2D textureMiddleground;
    Texture2D textureBackground;

    float scrollingFore = 0.0f;
    float scrollingMiddle = 0.0f;
    float scrollingBack = 0.0f;
};