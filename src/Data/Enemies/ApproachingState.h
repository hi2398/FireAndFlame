#pragma once

#include "../../Core/State.h"

class ApproachingState : public State {
public:
    std::shared_ptr <State> Update(Actor& actor) override;
    void Draw(Actor& actor)override;

    ~ApproachingState() = default;

protected:


private:
    int aggroCooldown = 0;
    int approachingFrameCounter = 0;
    Rectangle drawRec;
    float movingDistance = 0;
};