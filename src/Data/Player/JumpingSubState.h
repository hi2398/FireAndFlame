#pragma once

#include "../../Core/State.h"

class JumpingSubState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~JumpingSubState() override = default;

protected:


private:



};


