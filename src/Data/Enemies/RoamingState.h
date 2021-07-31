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
    int roamingFrameCounter = 0;
    int flyRoamingCounter = 0;
    float verticalDirection = 1;
    int collisionCounter = 0;
    int decisionTimer = 0;
    Rectangle drawRec;
};