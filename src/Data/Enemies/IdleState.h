#pragma once

#include "../../Core/State.h"

class IdleState : public State {
public:
    std::shared_ptr <State> Update(Actor& actor) override;
    void Draw(Actor& actor)override;

    ~IdleState() = default;

protected:


private:


};