#pragma once

#include "../../Core/PlayerStates.h"

class MovementState : public PlayerStates {
public:
    MovementState(Actor&player);

    std::shared_ptr<State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~MovementState() override = default;

protected:
    

private:
    std::shared_ptr<State> groundedSubState;
    std::shared_ptr<State> aerialSubState;
};


