#pragma once

#include "../../Core/State.h"

class JumpingSubState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~JumpingSubState() override = default;

protected:


private:
    float jumpSpeed = 5.0f;
    int jumpState = 0;


};


