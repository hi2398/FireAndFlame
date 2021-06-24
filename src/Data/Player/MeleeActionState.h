#pragma once

#include "../../Core/State.h"

class MeleeActionState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;

    ~MeleeActionState() override = default;

protected:


private:
    bool actionDone{false};

};


