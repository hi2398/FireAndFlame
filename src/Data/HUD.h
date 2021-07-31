#pragma once
#include "raylib.h"

class HUD {
public:
    HUD();
    void UpdateHUD();
    void DrawHUD();
    void changeInteractable(bool interactable);
    void executeEndscreenSwap();
    ~HUD() = default;
protected:

private:
    bool isInteractable = false; // Sets true if player is in reach of Dialogue Object
    Texture2D textureFire;
    Rectangle healthBar = {0};
    int endscreenCounter = 255;
    bool isEndscreenActive = false;
    Color endscreenColor = {0,0,0,255};
};


