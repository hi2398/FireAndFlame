#pragma once
#include "../Core/Scene.h"
#include "../Data/FinalBoss/SpearAttack.h"
#include "vector"

class FinalBoss : public Scene{
public:
    FinalBoss();

    void Update() override;

    void Draw() override;

    void UpdatePlatformSequence();

    void UpdateBossFightSequence();

    void ActivateBorder();

    ~FinalBoss() override = default;

private:
    std::vector<Rectangle> debugRecs;
    Vector2 playerStart = {17*32,84*32};
    Rectangle platformerSequenceCollider = {14*32,78*32,32*5,32};
    Rectangle disablePlatformerSequenceCollider = {80*32,46*32, 32, 360};
    Rectangle bossFightSequenceCollider = {86*32,61*32, 576, 32};
    Rectangle bossFightBorder[18];
    bool isPlatformSequenceActive = false;
    int timerForSpearRespawn = 0;
    bool isBossFightSequenceActive = false;
protected:

};