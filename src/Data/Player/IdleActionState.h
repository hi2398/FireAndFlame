#pragma once

#include "../../Core/State.h"

class IdleActionState : public State{
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~IdleActionState() override = default;

protected:

private:

};


