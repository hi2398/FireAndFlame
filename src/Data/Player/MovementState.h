#pragma once

#include "../../Core/State.h"

class MovementState : public State{
public:
    std::shared_ptr<State> Update(Actor &actor) override;


    ~MovementState() override = default;

protected:


private:


};


