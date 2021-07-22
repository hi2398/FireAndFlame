#pragma once

#include "../../Core/EState.h"

class ApproachingState : public EState {
public:
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~ApproachingState() = default;

protected:


private:
    int aggroCooldown = 0;
    int approachingFrameCounter = 0;
    Rectangle drawRec;
    float movingDistance = 0;
   
};