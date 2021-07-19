#pragma once
#include "raylib.h"

class HUD {
public:
    HUD();
    void UpdateHUD();
    void DrawHUD();
    void changeInteractable(bool interactable);
    ~HUD() = default;
protected:

private:
    bool isInteractable = false; // Sets true if player is in reach of Dialogue Object
    Texture2D textureFire;
    Rectangle healthBar = {0};
};


