#pragma once

#include "../../Core/State.h"

class FallingSubState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~FallingSubState() override = default;

protected:


private:


};


