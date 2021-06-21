#pragma once

#include "../../Core/State.h"

class IdleSubState : State {
public:
private:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~IdleSubState() override = default;

protected:


private:


};


