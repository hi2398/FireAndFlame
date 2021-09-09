#pragma once
#include "raylib.h"

class HUD {
public:
    HUD();
    void UpdateHUD();
    void DrawHUD();
    void changeInteractable(bool interactable);
    void executeEndscreenSwap();
    void SetBossEnemyHealth(int bossHealth, float multiplier);
    void ShowSaveNotification();
    void IsBossFightActive(bool isActive);

    ~HUD() = default;
protected:

private:
    bool isInteractable = false; // Sets true if player is in reach of Dialogue Object
    Texture2D textureFire;
    Rectangle healthBar = {0};
    int endscreenCounter = 255;
    bool isEndscreenActive = false;
    Color endscreenColor = {0,0,0,255};
    int bossHealth = 0;
    float bossHealthPos;
    Rectangle bossHealthBar{};
    Texture2D skull;
    Rectangle skullFrame{ 0,0,16,16 };
    Rectangle fireFrame{0,0,16,16};
    int frameCounter = 0;
    int thisFrame = 0;
    Texture2D playerHealthBar;
    float bossBarMultiplier;
    bool isBossFightActive{ false };

    //Save Notification
    bool showNotification{false};
    const int notificationTimer{60*3}; //show for 3 secs
    int currentNotificationTimer{0};
};


