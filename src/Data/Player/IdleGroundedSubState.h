#pragma once

#include "../../Core/PlayerStates.h"

class IdleGroundedSubState : public PlayerStates {
public:
    IdleGroundedSubState(Actor&player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~IdleGroundedSubState() override = default;

protected:


private:
    

};


