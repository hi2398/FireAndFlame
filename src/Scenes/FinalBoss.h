#pragma once
#include "../Core/Scene.h"
#include "../Data/FinalBoss/SpearAttack.h"
#include "../Data/FinalBoss/EnergyAttack.h"
#include "../Data/FinalBoss/ChasingBoss.h"
#include "../Data/FinalBoss/BossSword.h"
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
    std::shared_ptr<ChasingBoss> chasingBoss;
    std::shared_ptr<BossSword> sword;
    Vector2 playerStart = {17*32,84*32};

    Rectangle platformerSequenceCollider = {14*32,78*32,32*5,32};
    Rectangle disablePlatformerSequenceCollider = {80*32,46*32, 32, 360};
    Rectangle bossFightSequenceCollider = {86*32,61*32, 576, 32};
    Rectangle chasingBossPositions[10];
    Rectangle playerCollidersForBossMovement[9];
    Rectangle bossFightBorder[18];

    bool isPlatformSequenceActive = false;
    int timerForSpearRespawn = 0;
    bool isBossFightSequenceActive = false;
protected:

};