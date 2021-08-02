#pragma once

#include "../../Core/EState.h"

class RoamingState : public EState {
public:
    RoamingState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~RoamingState() = default;

protected:


private:
    Rectangle tileRec = { 0,0,32,32 };

    int roamingFrameCounter = 0;
    int flyRoamingCounter = 0;
    float verticalDirection = 1;
    int collisionCounter = 0;
    int decisionTimer = 0;
    Rectangle drawRec;

    //SpiderBot variables
    float spiderBotRotation = 0;

    //springhog variables
    Rectangle rightJumpCheck = {};
    Rectangle leftJumpCheck = {};
    float horizontalJumpCheck = 1;
    int groundedCounter = 0;
    bool decided{ false };

    Rectangle leftFoot{};
    Rectangle rightFoot{};
};