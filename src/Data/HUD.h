#pragma once
#include "raylib.h"

class HUD {
public:
    HUD();
    void UpdateHUD();
    void DrawHUD();
    void changeInteractable(bool interactable);
    void executeEndscreenSwap();
    void SetBossEnemyHealth(int bossHealth);
    void ShowSaveNotification();

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
    Rectangle bossHealthBar{};

    //Save Notification
    bool showNotification{false};
    const int notificationTimer{60*3}; //show for 3 secs
    int currentNotificationTimer{0};
};


