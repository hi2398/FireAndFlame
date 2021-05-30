#pragma once

class HUD {
public:
    HUD();
    virtual void UpdateHUD() = 0;
    virtual void DrawHUD() = 0;
    virtual ~HUD() = default;
protected:

private:

};


