#pragma once

#include "../../Core/EState.h"

class RoamingState : public EState {
public:
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~RoamingState() = default;

protected:


private:
    int roamingFrameCounter = 0;
    int collisionCounter = 0;
    int decisionTimer = 0;
    Rectangle drawRec;
};