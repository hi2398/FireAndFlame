#pragma once

#include "../../Core/State.h"

class IdleGroundedSubState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~IdleGroundedSubState() override = default;

protected:


private:


};


