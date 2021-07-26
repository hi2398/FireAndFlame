#pragma once

#include "../../Core/PlayerStates.h"

class IdleActionState : public PlayerStates{
public:
    IdleActionState(Actor& player);
    std::shared_ptr <State> Update(Actor&player) override;
    void Draw(Actor& player) override;

    ~IdleActionState() override = default;

protected:

private:

};


