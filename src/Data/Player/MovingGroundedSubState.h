#pragma once

#include "../../Core/PlayerStates.h"

class MovingGroundedSubState : public PlayerStates {
public:
    MovingGroundedSubState(Actor& player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~MovingGroundedSubState() override = default;

protected:


private:
    int frameCounterDash = 0;
    bool stepped{ false };
    int stepCounter = 0;
    int stepInit = 0;
};


