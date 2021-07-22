#pragma once

#include "../../Core/State.h"

class FallingSubState : public State {
public:
    FallingSubState();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~FallingSubState() override = default;

protected:


private:
    float gravity = 1.0f;

    Rectangle activeFrame = {0,0,32,32};
    int frameCounterDash = 0;

};


