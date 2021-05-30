#pragma once
#include "../Core/HUD.h"

class IgniteHUD : public HUD{
public:
    IgniteHUD();
    void UpdateHUD() override;
    void DrawHUD() override;
    ~IgniteHUD() override = default;

protected:

private:

};


