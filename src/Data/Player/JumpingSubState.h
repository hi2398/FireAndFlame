#pragma once

#include "../../Core/PlayerStates.h"

class JumpingSubState : public PlayerStates {
public:
    JumpingSubState(Actor&player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~JumpingSubState() override = default;

protected:


private:
    int jumpState = 0;
    int frameCounterDash = 0;
};


