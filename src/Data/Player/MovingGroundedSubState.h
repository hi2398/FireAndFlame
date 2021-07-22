#pragma once

#include "../../Core/State.h"

class MovingGroundedSubState : public State{
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~MovingGroundedSubState() override = default;

protected:


private:


};


