#pragma once
#include "raylib.h"

class HUD {
public:
    HUD();
    void UpdateHUD();
    void DrawHUD();
    ~HUD() = default;
protected:

private:
    Rectangle healthBar = {0};
};


