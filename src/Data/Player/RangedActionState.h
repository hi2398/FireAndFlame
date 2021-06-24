#pragma once

#include "../../Core/State.h"

class RangedActionState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~RangedActionState() override = default;

protected:


private:
    bool actionDone{false};

};


