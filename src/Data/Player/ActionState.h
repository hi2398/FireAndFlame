#pragma once

#include "../../Core/State.h"

class ActionState : public State {
public:
    std::shared_ptr<State> Update(Actor &actor) override;

    ~ActionState() override = default;

protected:


private:


};


