#pragma once

#include "../../Core/PlayerStates.h"


class WallJumpingSubState : public PlayerStates {
public:
    WallJumpingSubState(Actor& player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~WallJumpingSubState() override = default;

protected:


private:
    int wallJumpDirection;
};