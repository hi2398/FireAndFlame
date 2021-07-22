#pragma once

#include "../../Core/State.h"

class JumpingSubState : public State {
public:
    JumpingSubState();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~JumpingSubState() override = default;

protected:


private:
    int jumpState = 0;
    Rectangle activeFrame = { 0,0,32,32 };
    int frameCounterDash = 0;
};


