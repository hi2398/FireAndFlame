#pragma once

#include "../../Core/State.h"

class MovementState : public State{
public:

    MovementState();

    std::shared_ptr<State> Update(Actor &actor) override;

    ~MovementState() override = default;

protected:


private:
    std::shared_ptr<State> groundedSubState;
    std::shared_ptr<State> aerialSubState;

};


