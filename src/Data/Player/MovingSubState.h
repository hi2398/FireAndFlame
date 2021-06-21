#pragma once

#include "../../Core/State.h"

class MovingSubState : public State{
public:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~MovingSubState() override = default;

protected:


private:


};


