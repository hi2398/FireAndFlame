#pragma once

#include "../../Core/State.h"

class RoamingState : public State {
public:
    std::shared_ptr <State> Update(Actor& actor) override;
    void Draw(Actor& actor)override;

    ~RoamingState() = default;

protected:


private:
    int roamingFrameCounter = 0;
    Rectangle drawRec;
};